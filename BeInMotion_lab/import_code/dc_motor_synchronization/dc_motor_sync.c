#include <stdio.h>
#include "system.h"
#include "io.h"
#include "simple_graphics.h"
#include "priv/alt_legacy_irq.h"
#include "sys/alt_irq.h"
#include "unistd.h"

#define LCD_INTERFACE_0_BASE LCD_INTF_BASE

#define TABLE_EDGE  1
#define WALL_DETECT 0
#define OutMax 0xFFFF
#define OutMin 0x0000
#define DC_M1_COUNT_REF 100
#define DC_M2_COUNT_REF 100

#define PID_MODE_SEL 0    // "1" for HW  "0" for SW

//dc motor 1 PID constant parameters
#define dc_m1_Kp 6
#define dc_m1_Ki 0.5
#define dc_m1_Kd 0

//dc motor 2 PID constant parameters
#define dc_m2_Kp 6
#define dc_m2_Ki 0.5
#define dc_m2_Kd 0

extern char cour10_font_array[95][11];
unsigned int  edge;
unsigned int  dc_m1,dc_m2;
unsigned int  dc_m1_pwm_freq = ALT_CPU_FREQ/10000;
unsigned int  dc_m2_pwm_freq = ALT_CPU_FREQ/10000;
unsigned int  dc1_cmp,dc2_cmp;
unsigned char table_edge,wall_detect;

int OutPreSat_m1[2]={0,0},OutPreSat_m2[2]={0,0};
int Up_m1,Ui_m1=0,Ud_m1,Up1_m1;
int Up_m2,Ui_m2=0,Ud_m2,Up1_m2;
int Err_m1,Err_m2;
int dc_m1_pwm_duty;
int dc_m2_pwm_duty;
int Out_pwm1,Out_pwm2;
int i,j;

//------------------------------- PID Hardware-Software Functions -----------------------//
void pid_controller_hw()
{
    IOWR(PID_CON_M1_BASE,0x04,dc_m1);        //Feedback
	IOWR(PID_CON_M2_BASE,0x04,dc_m2);

	IOWR(PID_CON_M1_BASE,0x05,1);           // PID enable
	IOWR(PID_CON_M2_BASE,0x05,1);

	while(IORD(PID_CON_M1_BASE,0x07) != 1);

	OutPreSat_m1[0]=OutPreSat_m1[1];
	OutPreSat_m1[1]=IORD(PID_CON_M1_BASE,0x06);

	OutPreSat_m2[0]=OutPreSat_m2[1];
	OutPreSat_m2[1]=IORD(PID_CON_M2_BASE,0x06);

	Out_pwm1 = Out_pwm1 - (OutPreSat_m1[1] - OutPreSat_m1[0]);
	Out_pwm2 = Out_pwm2 - (OutPreSat_m2[1] - OutPreSat_m2[0]);

    if(Out_pwm1 > OutMax)
		Out_pwm1 = OutMax;
	else if(Out_pwm1 < OutMin)
		Out_pwm1 = OutMin;

	if(Out_pwm2 > OutMax)
		Out_pwm2 = OutMax;
	else if(Out_pwm2 < OutMin)
		Out_pwm2 = OutMin;

    IOWR(DC1_PWM1_BASE+0x04,0,Out_pwm1);
    IOWR(DC2_PWM1_BASE+0x04,0,Out_pwm2);
}

void pid_controller_sw()
{
	Err_m1 = DC_M1_COUNT_REF - dc_m1;
    Err_m2 = DC_M2_COUNT_REF - dc_m2;

    Up_m1 = dc_m1_Kp * Err_m1;            //P Controller
    Up_m2 = dc_m2_Kp * Err_m2;

    Ui_m1 = Ui_m1 + dc_m1_Ki * Up_m1;     //I Controller
    Ui_m2 = Ui_m2 + dc_m2_Ki * Up_m2;

    Ud_m1 = dc_m1_Kd * (Up_m1 - Up1_m1);  //D Controller
    Ud_m2 = dc_m2_Kd * (Up_m2 - Up1_m2);

    Up1_m1 =Up_m1;
    Up1_m2 =Up_m2;

    OutPreSat_m1[0] = OutPreSat_m1[1];
    OutPreSat_m1[1] = Up_m1 + Ui_m1 + Ud_m1;

    OutPreSat_m2[0] = OutPreSat_m2[1];
    OutPreSat_m2[1] = Up_m2 + Ui_m2 + Ud_m2;

    Out_pwm1 = Out_pwm1 - ( OutPreSat_m1[1] - OutPreSat_m1[0]);
    Out_pwm2 = Out_pwm2 - ( OutPreSat_m2[1] - OutPreSat_m2[0]);

    if (Out_pwm1 > OutMax)
         Out_pwm1 =  OutMax;
    else if (Out_pwm1 < OutMin)
         Out_pwm1 =  OutMin;

    if (Out_pwm2 > OutMax)
         Out_pwm2 =  OutMax;
    else if (Out_pwm2 <OutMin)
         Out_pwm2 =  OutMin;

    IOWR(DC1_PWM1_BASE+0x04,0,Out_pwm1);
    IOWR(DC2_PWM1_BASE+0x04,0,Out_pwm2);
}
//-------------------------- ISRs for the motors -----------------------------------------//
void isr_dc_m2(void *context, alt_u32 id)
{
  IOWR(DC2_PWM2_BASE+0x08,0,0);
  IOWR(DC2_PWM1_BASE+0x08,0,0);
  IOWR(IR_RX2_BASE,0,0x0);
  dc2_cmp = 0;
 }
void isr_dc_m1(void *context, alt_u32 id)
{
  IOWR(DC1_PWM2_BASE+0x08,0,0);
  IOWR(DC1_PWM1_BASE+0x08,0,0);
  IOWR(IR_RX1_BASE,0,0x0);
  dc1_cmp = 0;
}
//------------------------ Direction (left,right,forward,backward) Functions ---------------------------//
int turn_left()
{
    int dc_m1_pwm_duty = dc_m1_pwm_freq/4;
    int dc_m2_pwm_duty = dc_m2_pwm_freq/4;

    dc1_cmp = 1;
    dc2_cmp = 1;

    IOWR(IR_RX2_BASE,0x00,0);
    IOWR(IR_RX1_BASE,0x00,0);
    IOWR(DC2_PWM2_BASE+0x08,0,0);
    IOWR(DC1_PWM1_BASE+0x08,0,0);

    IOWR(DC2_PWM1_BASE,0,dc_m2_pwm_freq);
    IOWR(DC2_PWM1_BASE+0x04,0,dc_m2_pwm_duty);
    IOWR(DC1_PWM2_BASE,0,dc_m1_pwm_freq);
    IOWR(DC1_PWM2_BASE+0x04,0,dc_m1_pwm_duty);

    IOWR(IR_RX2_BASE,1,722);
    IOWR(IR_RX1_BASE,1,722);
    IOWR(IR_RX2_BASE,0x00,1);
    IOWR(IR_RX1_BASE,0x00,1);

    IOWR(DC1_PWM2_BASE+0x08,0,1);
    IOWR(DC2_PWM1_BASE+0x08,0,1);

    while(1)
    {
        if(( dc1_cmp ==0 ) && (dc2_cmp ==0 ))
          return 0;
        else
        {
        usleep(90000);
        dc_m1 = IORD(IR_RX1_BASE,1);
        dc_m2 = IORD(IR_RX2_BASE,1);
        i = dc_m1-dc_m2;
        j = dc_m2-dc_m1;
        if(i > 5) {
            if(dc_m2_pwm_duty >= 100)
                dc_m2_pwm_duty-=50;
            if(dc_m1_pwm_duty < 1700)
                dc_m1_pwm_duty+=50;
            IOWR(DC2_PWM1_BASE+0x04,0,dc_m2_pwm_duty);
            IOWR(DC1_PWM2_BASE+0x04,0,dc_m1_pwm_duty);
        }
        else
        if(j > 5) {
            if(dc_m1_pwm_duty >= 100);
            dc_m1_pwm_duty-=50;
            if(dc_m2_pwm_duty < 1700)
            dc_m2_pwm_duty+=50;
            IOWR(DC2_PWM1_BASE+0x04,0,dc_m2_pwm_duty);
            IOWR(DC1_PWM2_BASE+0x04,0,dc_m1_pwm_duty);
        }
      }
    }
}

int turn_right()
{
    int dc_m1_pwm_duty = dc_m1_pwm_freq/4;
    int dc_m2_pwm_duty = dc_m2_pwm_freq/4;

    dc1_cmp = 1;
    dc2_cmp = 1;
    IOWR(IR_RX2_BASE,0x00,0);
    IOWR(IR_RX1_BASE,0x00,0);
    IOWR(DC2_PWM1_BASE+0x08,0,0);
    IOWR(DC1_PWM2_BASE+0x08,0,0);

    IOWR(DC2_PWM2_BASE,0,dc_m2_pwm_freq);
    IOWR(DC2_PWM2_BASE+0x04,0,dc_m2_pwm_duty);
    IOWR(DC1_PWM1_BASE,0,dc_m1_pwm_freq);
    IOWR(DC1_PWM1_BASE+0x04,0,dc_m1_pwm_duty);

    IOWR(IR_RX2_BASE,1,722);
    IOWR(IR_RX1_BASE,1,722);
    IOWR(IR_RX2_BASE,0x00,1);
    IOWR(IR_RX1_BASE,0x00,1);

    IOWR(DC1_PWM1_BASE+0x08,0,1);
    IOWR(DC2_PWM2_BASE+0x08,0,1);

    while(1)
    {
        if(( dc1_cmp ==0 ) && (dc2_cmp ==0 ))
        return 0;
        else
        {
        usleep(90000);
        dc_m1 = IORD(IR_RX1_BASE,1);
        dc_m2 = IORD(IR_RX2_BASE,1);
        i = dc_m1-dc_m2;
        j = dc_m2-dc_m1;
        if(i > 5) {
            if(dc_m2_pwm_duty >= 100)
                dc_m2_pwm_duty-=50;
            if(dc_m1_pwm_duty < 1700)
                dc_m1_pwm_duty+=50;
            IOWR(DC2_PWM2_BASE+0x04,0,dc_m2_pwm_duty);
            IOWR(DC1_PWM1_BASE+0x04,0,dc_m1_pwm_duty);
        }
        else
        if(j > 5) {
            if(dc_m1_pwm_duty >= 100);
                dc_m1_pwm_duty-=50;
            if(dc_m2_pwm_duty < 1700)
                dc_m2_pwm_duty+=50;
            IOWR(DC2_PWM2_BASE+0x04,0,dc_m2_pwm_duty);
            IOWR(DC1_PWM1_BASE+0x04,0,dc_m1_pwm_duty);
        }
      }
    }
}

void move_fwd()
{
    int dc_m1_pwm_duty = dc_m1_pwm_freq/8;
    int dc_m2_pwm_duty = dc_m2_pwm_freq/8;

    dc1_cmp = 1;
    dc2_cmp = 1;
    IOWR(IR_RX2_BASE,0x00,0);
    IOWR(IR_RX1_BASE,0x00,0);
    IOWR(DC2_PWM2_BASE+0x08,0,0);
    IOWR(DC1_PWM2_BASE+0x08,0,0);

    IOWR(DC2_PWM1_BASE,0,dc_m2_pwm_freq);
    IOWR(DC2_PWM1_BASE+0x04,0,dc_m2_pwm_duty);
    IOWR(DC1_PWM1_BASE,0,dc_m1_pwm_freq);
    IOWR(DC1_PWM1_BASE+0x04,0,dc_m1_pwm_duty);

    IOWR(IR_RX2_BASE,1,2500);
    IOWR(IR_RX1_BASE,1,2500);
    IOWR(IR_RX2_BASE,0x00,1);
    IOWR(IR_RX1_BASE,0x00,1);

    IOWR(DC1_PWM1_BASE+0x08,0,1);
    IOWR(DC2_PWM1_BASE+0x08,0,1);

    while(1)
    {
        edge = IORD(PS_DIN_BASE,0);
        if((( dc1_cmp ==0 ) && (dc2_cmp ==0 )) || ((table_edge==1) && (edge == 1)) || ((wall_detect==1) && (edge == 0)) )
        {
            IOWR(DC1_PWM1_BASE+0x08,0,0);
            IOWR(DC2_PWM1_BASE+0x08,0,0);
            IOWR(IR_RX1_BASE,0,0x0);
            IOWR(IR_RX2_BASE,0,0x0);
            dc1_cmp =0;
            dc1_cmp =0;
            return;
        }
        else
        {
        usleep(100000);
        dc_m1 = IORD(IR_RX1_BASE,1);
        dc_m2 = IORD(IR_RX2_BASE,1);
        IOWR(IR_RX1_BASE,0,0);
        IOWR(IR_RX2_BASE,0,0);
        IOWR(IR_RX1_BASE,0,1);
        IOWR(IR_RX2_BASE,0,1);
        PID_MODE_SEL ? pid_controller_hw() : pid_controller_sw();   //  HW/SW mode selects based on "PID_MODE_SEL" value.
        }
    }
}

void move_bwd()
{
    int dc_m1_pwm_duty = dc_m1_pwm_freq/4;
    int dc_m2_pwm_duty = dc_m2_pwm_freq/4;

    dc1_cmp = 1;
    dc2_cmp = 1;
    IOWR(IR_RX2_BASE,0x00,0);
    IOWR(IR_RX1_BASE,0x00,0);
    IOWR(DC2_PWM1_BASE+0x08,0,0);
    IOWR(DC1_PWM1_BASE+0x08,0,0);

    IOWR(DC2_PWM2_BASE,0,dc_m2_pwm_freq);
    IOWR(DC2_PWM2_BASE+0x04,0,dc_m2_pwm_duty);
    IOWR(DC1_PWM2_BASE,0,dc_m1_pwm_freq);
    IOWR(DC1_PWM2_BASE+0x04,0,dc_m1_pwm_duty);

    IOWR(IR_RX2_BASE,1,500);
    IOWR(IR_RX1_BASE,1,500);
    IOWR(IR_RX2_BASE,0x00,1);
    IOWR(IR_RX1_BASE,0x00,1);

    IOWR(DC1_PWM2_BASE+0x08,0,1);
    IOWR(DC2_PWM2_BASE+0x08,0,1);


    while(1){
        edge = IORD(PS_DIN_BASE,0);
            if(( dc1_cmp ==0 ) && (dc2_cmp ==0 ))  {
            IOWR(DC1_PWM2_BASE+0x08,0,0);
            IOWR(DC2_PWM2_BASE+0x08,0,0);
            break;
        }
        else {
        usleep(100000);
        dc_m1 = IORD(IR_RX1_BASE,1);
        dc_m2 = IORD(IR_RX2_BASE,1);
        i = dc_m1-dc_m2;
        j = dc_m2-dc_m1;
        if(i > 25) {
            if(dc_m2_pwm_duty >= 100)
                dc_m2_pwm_duty-=75;
            if(dc_m1_pwm_duty < 1700)
                dc_m1_pwm_duty+=75;
            IOWR(DC2_PWM2_BASE+0x04,0,dc_m2_pwm_duty);
            IOWR(DC1_PWM2_BASE+0x04,0,dc_m1_pwm_duty);
        }
        else
        if(j > 25) {
            if(dc_m1_pwm_duty >= 100);
                dc_m1_pwm_duty-=75;
            if(dc_m2_pwm_duty < 1700)
                dc_m2_pwm_duty+=75;
            IOWR(DC2_PWM2_BASE+0x04,0,dc_m2_pwm_duty);
            IOWR(DC1_PWM2_BASE+0x04,0,dc_m1_pwm_duty);
        }
      }
    }
}


int main()
{
  //Stop all motors
  IOWR(DC2_PWM2_BASE+0x08,0,0);
  IOWR(DC2_PWM1_BASE+0x08,0,0);
  IOWR(DC1_PWM2_BASE+0x08,0,0);
  IOWR(DC1_PWM1_BASE+0x08,0,0);

  //all LEDs off
  IOWR(USER_LED_BASE,0,7);
  LCD_init(LCD_INTF_BASE);

  //---------------Hardware PID Initialization------------//
  IOWR(PID_CON_M1_BASE,0x00,(unsigned int)dc_m1_Kp);          //Kp
  IOWR(PID_CON_M2_BASE,0x00,(unsigned int)dc_m2_Kp);

  IOWR(PID_CON_M1_BASE,0x01,(unsigned int)dc_m1_Ki);          //Ki
  IOWR(PID_CON_M2_BASE,0x01,(unsigned int)dc_m2_Ki);

  IOWR(PID_CON_M1_BASE,0x02,(unsigned int)dc_m1_Kd);          //Kd
  IOWR(PID_CON_M2_BASE,0x02,(unsigned int)dc_m2_Kd);

  IOWR(PID_CON_M1_BASE,0x03,DC_M1_COUNT_REF);           //Reference
  IOWR(PID_CON_M2_BASE,0x03,DC_M2_COUNT_REF);
  //---------------------------------------------------------//

  // Mode Selection LCD Display
  LCD_draw_box (0, 0 ,160,128, RGB16(255,0,0),1);
  LCD_draw_round_corner_box(5,5,155,123,10,RGB16(25,27,126),1);
  LCD_print_string(22,12,RGB16(255,255,255),(char *)cour10_font_array,"Mode Selection");
  LCD_draw_line(22, 24,135, 24,5, RGB16(255,255,255));
  LCD_print_string(8,40,RGB16(255,255,255),(char*)cour10_font_array,"SW7 : Table Edge");
  LCD_print_string(8,55,RGB16(255,255,255),(char *)cour10_font_array,"SW8 : Wall Detect");

  while(1)
  {
    while( (IORD(PB_BASE,0) & 0x7F) == 0x7F ) {}
    if((IORD(PB_BASE,0) == 0x5F))  //SW7
    {
        table_edge = 1;
        wall_detect = 0;
        while( (IORD(PB_BASE,0) & 0x7F) != 0x7F ) {}
        usleep(100000);
        break;
    }
    else if((IORD(PB_BASE,0) == 0x3F)) //SW8
    {
    	table_edge = 0;
        wall_detect = 1;
        while( (IORD(PB_BASE,0) & 0x7F) != 0x7F ) {}
        usleep(100000);
        break;
    }
    if((IORD(PB_BASE,0) == 0x77)) //SW5
    {
        table_edge = 0;
        wall_detect = 0;
        while( (IORD(PB_BASE,0) & 0x7F) != 0x7F ) {}
        usleep(100000);
        LCD_draw_box (0, 0 ,160,128, RGB16(255,0,0),1);
        LCD_draw_round_corner_box(5,5,155,123,10,RGB16(25,27,126),1);
        break;
    }
    while( (IORD(PB_BASE,0) & 0x7F) != 0x7F ){}
  } // End of mode selection

  alt_irq_register(IR_RX2_IRQ,(void* )0,(alt_isr_func)isr_dc_m2);
  alt_irq_register(IR_RX1_IRQ,(void* )0,(alt_isr_func)isr_dc_m1);

 //Enable IR LED
  IOWR(IR_LED1_BASE,0,1);
  IOWR(IR_LED2_BASE,0,1);

  i = 0;
  while(1)
  {
    if(table_edge == 1)
    {
    	if(i >= 4) i = 0;
        else       i++;
        move_fwd();

            while ( IORD(PS_DIN_BASE,0) != 0)
            {
                IOWR(USER_LED_BASE,0,0);
                if(i>=4) i = 0;
                else    i++;
                usleep(300000);
                move_bwd();
                usleep(300000);
                IOWR(USER_LED_BASE,0,7);
                turn_left();
                usleep(300000);
            }
    }
    else if(wall_detect == 1)
    {
    	if(i >= 4)
        	i = 0;
        else
        	i++;
        move_fwd();
        if(IORD(PS_DIN_BASE,0) == 1)
        {
           for(j=0;j<4;j++)
             {
                usleep(1000);
                turn_left();
             }
        }
        else
        {
            while ( IORD(PS_DIN_BASE,0) == 0)
            {
                 IOWR(USER_LED_BASE,0,0);
                 if(i >= 4) i = 0;
                 else    i++;
                 usleep(300000);
                 move_bwd();
                 IOWR(USER_LED_BASE,0,7);
                 usleep(300000);
                 turn_left();
                 usleep(300000);
            }
        }

    }
  }
  return 0;
}
