/*
 * battery_status.c
 *
 *  Created on: 09-Jun-2011
 *      Author: Hardik Sheth
 */

#include "io.h"
#include "stdio.h"
#include "system.h"
#include "unistd.h"
#include "simple_graphics.h"

#define BattGasGuageI2C_SPEED  400000   // 400KHz
#define BattGasGuageI2C_CLK    50000000 // I2C Core clock in Qsys
#define MaxCount  10800                 // Maximum value for the coulomb counter
#define MinCount  58                    // Minimum value for the coulomb counter

extern char         cour10_font_array[95][11];
extern unsigned int bat_data[59][3];

//-------------------   Function Declarations  -------------------------------------//

void          BattGasGaugeI2C_TIP();
void          set_clmb_cnt();
void          bat_soc_check();
void          pb_check();
void          bat_con_check();
void          clmb_counter_I2C();
void          BattInfoDisplay(float,float,unsigned int);
void          empty_full_display();
void          bat_display();
unsigned int  ReadBattCharge();
unsigned int  ReadBattTemp();
unsigned int  BattGasGaugeI2C_ACK();
float 		  ReadBattVolt();

//-----------------------  Global Variables   ---------------------------//

unsigned int batt_conn_dis_status, run_once=0;
volatile int *BattGasGaugeI2C_PreLow, *BattGasGaugeI2C_PreHigh,
	         *BattGasGaugeI2C_Cntrl,  *BattGasGaugeI2C_Tx,
	         *BattGasGaugeI2C_Rx,     *BattGasGaugeI2C_Cmd,
	         *BattGasGaugeI2C_Status;

unsigned int  temp,clmb_counter=0,new_bat_charge,i,bat_temp,temp_clmb_cnt=0,bat_SOC;
unsigned int  clmb_counter_MSB,clmb_counter_LSB;
unsigned int  clmb_cnt_underflw_flag = 0;
unsigned int  SOC_prev;
unsigned char k[2];
float         batt_volt,batt_temp,bat_per, battery_voltage;

//---------------------------------    Main  ------------------------------------------------------
int main()
{
 	BattGasGaugeI2C_PreLow   =(int*)(BAT_GAS_GAUGE_BASE );
	BattGasGaugeI2C_PreHigh  =(int*)(BAT_GAS_GAUGE_BASE + 0x04 );
	BattGasGaugeI2C_Cntrl    =(int*)(BAT_GAS_GAUGE_BASE + 0x08 );
	BattGasGaugeI2C_Tx       =(int*)(BAT_GAS_GAUGE_BASE + 0x0C );
	BattGasGaugeI2C_Cmd      =(int*)(BAT_GAS_GAUGE_BASE + 0x10 );
	BattGasGaugeI2C_Rx       =(int*)(BAT_GAS_GAUGE_BASE + 0x0C );
	BattGasGaugeI2C_Status   =(int*)(BAT_GAS_GAUGE_BASE + 0x10 );


	  IOWR(USER_LED_BASE,0,7);  //CEB turn off LEDs
	  LCD_init(LCD_INTF_BASE);
    //LCD_draw_box(0,0,160,129,RGB16(89,0,179),1);
    //LCD_draw_round_corner_box (1,2,160,20,2.8,RGB16(255,255,255),0);
	//LCD_draw_round_corner_box (2,2,159,19,2.8,RGB16(94,47,0),1);
    LCD_draw_box(0,0,160,128,RGB16(89,0,179),1);
    LCD_draw_round_corner_box (0,0,159,20,2.8,RGB16(255,255,255),0);
	LCD_draw_round_corner_box (1,1,158,20,2.8,RGB16(94,47,0),1);
	LCD_print_string(4,6,RGB16(255,255,255),(char *)cour10_font_array,"Reset Battery Gauge");
//    LCD_draw_round_corner_box (7,45,152,110,2.8,RGB16(42,42,42),1);
//	LCD_draw_round_corner_box (8,45,151,109,2.8,RGB16(255,255,255),0);
//	LCD_print_string(50,45,RGB16(255,255,255),(char *)cour10_font_array,":Note:");
//	LCD_draw_line(63,53,95,53,5, RGB16(255,255,255));
    LCD_print_string(3,30,RGB16(255,255,255),(char *)cour10_font_array,"SW5: Reset ");
    LCD_print_string(3,45,RGB16(255,255,255),(char *)cour10_font_array,"battery status");
    LCD_print_string(3,65,RGB16(255,255,255),(char *)cour10_font_array,"SW7: Set battery");
    LCD_print_string(3,80,RGB16(255,255,255),(char *)cour10_font_array,"level MINIMUM");
    LCD_print_string(3,100,RGB16(255,255,255),(char *)cour10_font_array,"SW8: Set battery");
    LCD_print_string(3,115,RGB16(255,255,255),(char *)cour10_font_array,"level MAXIMUM");

    usleep(4000000);

    LCD_draw_box(0,0,160,128,RGB16(89,0,179),1);
    LCD_draw_round_corner_box (0,0,159,20,2.8,RGB16(255,255,255),0);
	LCD_draw_round_corner_box (1,1,158,20,2.8,RGB16(94,47,0),1);
	LCD_print_string(35,6,RGB16(255,255,255),(char *)cour10_font_array,"Battery Info");

    LCD_draw_box(0,21,160,129,RGB16(89,0,179),1);
	LCD_draw_box(31,36,41,40,0x0000,1);
	LCD_print_string(65,50,RGB16(255,255,255),(char *)cour10_font_array,"Volt:");
    LCD_print_char(147,52,RGB16(255,255,255),'V',(char *)cour10_font_array);
	LCD_print_string(65,75,RGB16(255,255,255),(char *)cour10_font_array,"Temp:");
	LCD_draw_circle(147,75, 1, RGB16(255,255,255),0 );
	LCD_print_char(149,75,RGB16(255,255,255),'C',(char *)cour10_font_array);

	LCD_draw_round_corner_box ( 107,47,141,62,0,RGB16(255,255,255),1); //White box for the voltage
	LCD_draw_round_corner_box ( 107,73,141,88,0,RGB16(255,255,255),1); //white box for the temperature

	LCD_draw_box(22,40,50,90,RGB16(0,0,0),0);    //Black outline for the battery symbol
	LCD_draw_box(23,41,48,88,RGB16(255,255,255),1); //white color filled in battery

    //*********************************************
    //  I2C Master IP core Initialization
    //*********************************************
    temp  = (BattGasGuageI2C_CLK / (5*BattGasGuageI2C_SPEED)) - 1;
	*BattGasGaugeI2C_PreLow  = (temp & 0x00FF);
	*BattGasGaugeI2C_PreHigh = (temp & 0xFF00)>> 8;
	*BattGasGaugeI2C_Cntrl   = 0x80;                        //Enable the core

	bat_SOC = ReadBattVolt();
	bat_SOC = ReadBattVolt();

    while(1) {
        bat_con_check();                    //check battery connection
        batt_temp = ReadBattTemp();         //Read batt temperature
        bat_soc_check();
        pb_check();            			    //push buttons check
        usleep(1000000);
	}
    return 0;
}

//---------------------------------    Function Definitions  ------------------------------------//
//***************************************************************************************
// Name    : Battery Connection Checker
//
// Purpose : This function checks whether the battery is connected to the board or not.
//****************************************************************************************/
void bat_con_check()
{

   ReadBattVolt();
   if(batt_conn_dis_status != 0)        // if NACK received
   {
      LCD_draw_round_corner_box ( 107,47,141,62,0,RGB16(255,255,255),1); //White box for the voltage
      LCD_draw_round_corner_box ( 107,73,141,88,0,RGB16(255,255,255),1); //white box for the temperature

	  LCD_draw_box(22,40,50,90,RGB16(0,0,0),0);    //Black outline for the battery symbol
	  LCD_draw_box(23,41,48,88,RGB16(255,255,255),1); //white color filled in battery

	  LCD_draw_box(22,105,159,115,RGB16(89,0,179),1);      //blue color in percentage area
	  LCD_print_string(22,105,RGB16(255,255,255),(char *)cour10_font_array,"Disconnected");
      while(1) {
      	ReadBattVolt();
		if(batt_conn_dis_status == 0)
		break;
	   }
   }
}

//*********************************************************************************************
// Name    : Push button Checker
//
// Purpose : This function checks which push button is pressed and takes an action accordingly
//***********************************************************************************************/
void pb_check()
{
	unsigned int i=0;
	usleep(5000);
    i = IORD(PB_BASE,0);
    switch( i )
		{
    	case 0x5F:  clmb_counter = MinCount;        // SW7-empty
    		        clmb_counter_I2C();
                    //CEB display initialization complete message and then redraw screen
               	    usleep(200);

               	    LCD_draw_box(0,21,160,129,RGB16(89,0,179),1);
           		    LCD_draw_round_corner_box (12,45,131,80,2.8,RGB16(42,42,42),1);
           			LCD_draw_round_corner_box (12,45,131,80,2.8,RGB16(255,255,255),0);
           		    LCD_print_string(18,50,RGB16(255,255,255),(char *)cour10_font_array,"Reset");
           		    LCD_print_string(18,65,RGB16(255,255,255),(char *)cour10_font_array,"Complete!");

           		    usleep(2000000);

                    LCD_draw_box(0,21,160,129,RGB16(89,0,179),1);
                    LCD_draw_box(31,36,41,40,0x0000,1);
                    LCD_print_string(65,50,RGB16(255,255,255),(char *)cour10_font_array,"Volt:");
                    LCD_print_char(147,52,RGB16(255,255,255),'V',(char *)cour10_font_array);
                    LCD_print_string(65,75,RGB16(255,255,255),(char *)cour10_font_array,"Temp:");
                    LCD_draw_circle(147,75, 1, RGB16(255,255,255),0 );
                    LCD_print_char(149,75,RGB16(255,255,255),'C',(char *)cour10_font_array);

                    LCD_draw_round_corner_box ( 107,47,141,62,0,RGB16(255,255,255),1); //White box for the voltage
                   	LCD_draw_round_corner_box ( 107,73,141,88,0,RGB16(255,255,255),1); //white box for the temperature

                    LCD_draw_box(22,40,50,90,RGB16(0,0,0),0);    //Black outline for the battery symbol
                    LCD_draw_box(23,41,48,88,RGB16(255,255,255),1); //white color filled in battery
           			run_once = 1;  //CEB force the battery gauge to redraw
           			SOC_prev = 101;  //CEB force the battery gauge to redraw
           			BattInfoDisplay( battery_voltage,bat_per,batt_temp);
 					break;

        case 0x3F:  clmb_counter = MaxCount;       // SW8-full
        	   	    clmb_counter_I2C();
                    //CEB display "initialization complete" message and then redraw screen
               	    usleep(200);

               	    LCD_draw_box(0,21,160,129,RGB16(89,0,179),1);
           		    LCD_draw_round_corner_box (12,45,131,80,2.8,RGB16(42,42,42),1);
           			LCD_draw_round_corner_box (12,45,131,80,2.8,RGB16(255,255,255),0);
           		    LCD_print_string(18,50,RGB16(255,255,255),(char *)cour10_font_array,"Reset");
           		    LCD_print_string(18,65,RGB16(255,255,255),(char *)cour10_font_array,"Complete!");

           		    usleep(2000000);

                    LCD_draw_box(0,21,160,129,RGB16(89,0,179),1);
                    LCD_draw_box(31,36,41,40,0x0000,1);
                    LCD_print_string(65,50,RGB16(255,255,255),(char *)cour10_font_array,"Volt:");
                    LCD_print_char(147,52,RGB16(255,255,255),'V',(char *)cour10_font_array);
                    LCD_print_string(65,75,RGB16(255,255,255),(char *)cour10_font_array,"Temp:");
                    LCD_draw_circle(147,75, 1, RGB16(255,255,255),0 );
                    LCD_print_char(149,75,RGB16(255,255,255),'C',(char *)cour10_font_array);

                    LCD_draw_round_corner_box ( 107,47,141,62,0,RGB16(255,255,255),1); //White box for the voltage
                   	LCD_draw_round_corner_box ( 107,73,141,88,0,RGB16(255,255,255),1); //white box for the temperature

                    LCD_draw_box(22,40,50,90,RGB16(0,0,0),0);    //Black outline for the battery symbol
                    LCD_draw_box(23,41,48,88,RGB16(255,255,255),1); //white color filled in battery
           			run_once = 1;  //CEB force the battery gauge to redraw
           			SOC_prev = 101;  //CEB force the battery gauge to redraw
           			BattInfoDisplay( battery_voltage,bat_per,batt_temp);
         	   	 	break;

        case 0x77 : set_clmb_cnt();                // SW5-calibration
               	    clmb_counter_I2C();
                    //CEB display initialization complete message and then redraw screen
               	    usleep(200);

               	    LCD_draw_box(0,21,160,129,RGB16(89,0,179),1);
           		    LCD_draw_round_corner_box (12,45,131,80,2.8,RGB16(42,42,42),1);
           			LCD_draw_round_corner_box (12,45,131,80,2.8,RGB16(255,255,255),0);
           		    LCD_print_string(18,50,RGB16(255,255,255),(char *)cour10_font_array,"Reset");
           		    LCD_print_string(18,65,RGB16(255,255,255),(char *)cour10_font_array,"Complete!");

           		    usleep(2000000);

                    LCD_draw_box(0,21,160,129,RGB16(89,0,179),1);
                    LCD_draw_box(31,36,41,40,0x0000,1);
                    LCD_print_string(65,50,RGB16(255,255,255),(char *)cour10_font_array,"Volt:");
                    LCD_print_char(147,52,RGB16(255,255,255),'V',(char *)cour10_font_array);
                    LCD_print_string(65,75,RGB16(255,255,255),(char *)cour10_font_array,"Temp:");
                    LCD_draw_circle(147,75, 1, RGB16(255,255,255),0 );
                    LCD_print_char(149,75,RGB16(255,255,255),'C',(char *)cour10_font_array);

                    LCD_draw_round_corner_box ( 107,47,141,62,0,RGB16(255,255,255),1); //White box for the voltage
                   	LCD_draw_round_corner_box ( 107,73,141,88,0,RGB16(255,255,255),1); //white box for the temperature

                    LCD_draw_box(22,40,50,90,RGB16(0,0,0),0);    //Black outline for the battery symbol
                    LCD_draw_box(23,41,48,88,RGB16(255,255,255),1); //white color filled in battery
           			run_once = 1;  //CEB force the battery gauge to redraw
           			SOC_prev = 101;  //CEB force the battery gauge to redraw
           			BattInfoDisplay( battery_voltage,bat_per,batt_temp);
               	    break;

		}
    while( (IORD(PB_BASE,0) & 0x7F) != 0x7F ) { }
}

//****************************************************************************************
// Name    : Battery SOC Checker and Percentage(%) Calculator
//
// Purpose : This function measure the state of charge or percentage of the battery
//*****************************************************************************************/
void bat_soc_check()
{
    temp_clmb_cnt = ReadBattCharge();

	if(temp_clmb_cnt <= 58)
     	clmb_cnt_underflw_flag = 1;
	else
		clmb_cnt_underflw_flag = 0;

	bat_SOC = ReadBattVolt();
    batt_volt = (float)((bat_SOC * 6.0)/0xFFFF);
	temp = (unsigned int )batt_volt;
	battery_voltage = batt_volt;
	batt_volt = (batt_volt - temp  ) * 100;
	temp = (unsigned int )batt_volt;
	bat_per = (((float)(temp_clmb_cnt) - MinCount)/(MaxCount - MinCount))*100;
	if(bat_per >= 100.0)
		bat_per = 100.0;
	BattInfoDisplay( battery_voltage,bat_per,batt_temp);
}

//***********************************************************************************
// Name    : I2C for the Coulomb Counter
//
// Purpose : This function writes the LSB-MSB of the coulomb counter to the I2C bus
//**************************************************************************************/
void clmb_counter_I2C()
{
    clmb_counter_MSB = (clmb_counter & 0xFF00)>>8;  // MSB
   	clmb_counter_LSB = (clmb_counter & 0x00FF);     // LSB
	//---------------Write manually Accumulated Charge register---------------//
	//C Reg,ACR MSB

	*BattGasGaugeI2C_Tx  = 0xc8;
	*BattGasGaugeI2C_Cmd   = 0x90;
	BattGasGaugeI2C_TIP();

	*BattGasGaugeI2C_Tx  = 0x02;
	*BattGasGaugeI2C_Cmd   = 0x10;
	BattGasGaugeI2C_TIP();

	*BattGasGaugeI2C_Tx  = clmb_counter_MSB;
	*BattGasGaugeI2C_Cmd   = 0x50;
	BattGasGaugeI2C_TIP();

    // D reg , ACR LSB
	*BattGasGaugeI2C_Tx  = 0xc8;
	*BattGasGaugeI2C_Cmd   = 0x90;
	BattGasGaugeI2C_TIP();

	*BattGasGaugeI2C_Tx  = 0x03;
	*BattGasGaugeI2C_Cmd   = 0x10;
	BattGasGaugeI2C_TIP();

	*BattGasGaugeI2C_Tx  = clmb_counter_LSB;
	*BattGasGaugeI2C_Cmd   = 0x50;
	BattGasGaugeI2C_TIP();
}

//*************************************************************************************************
// Name    : Set Coulomb Counter
//
// Purpose : This function checks the battery current voltage and sets coulomb counter accordingly
//***************************************************************************************************/
void set_clmb_cnt()
{
	unsigned int i=0,j=0,avg_bat_volt=0,bat_volt_rd,sum=0;
	usleep(50000);
	while(j<10)
	{
		bat_volt_rd = ReadBattVolt();
		sum = sum + bat_volt_rd;
		j++;
		usleep(1000);
	}
	avg_bat_volt = (unsigned int)(sum / 10);
    for(i=4;i<59;i++)
    {
		if((bat_data[i][1] >= avg_bat_volt) && (bat_data[i][0] <= avg_bat_volt))
	    {
           clmb_counter = bat_data [i][2];
		   break;

	    }
	    else if(avg_bat_volt <= 36152)
	    {
		   clmb_counter = MinCount;
    	   break;

	    }
	    else if(avg_bat_volt >= 44704)
	    {
		   clmb_counter = MaxCount;
		   break;
        }
    }
}

//***************************************************************************************************************
// Name    : Battery Display Information
//
// Purpose : This function takes three arguments ( Voltage,Percentage,Temperature) and display them in the LCD
//****************************************************************************************************************/
void BattInfoDisplay(float voltage,float SOC,unsigned int temp)
{
    unsigned int i;
    unsigned char j[2];
    unsigned int temp_data[2];
    unsigned int SOC_int;

    i = (unsigned int )voltage;
    LCD_draw_round_corner_box ( 107,47,141,62,0,RGB16(255,255,255),1); // white box for the voltage
    LCD_draw_round_corner_box ( 107,73,141,88,0,RGB16(255,255,255),1); // white box for the temperature
    LCD_print_char(112,50,0x0000,i+0x30,(char *)cour10_font_array);    // integer value of the voltage in white box
    LCD_print_char(118,50,RGB16(0,0,0),'.',(char *)cour10_font_array); // dot after the integer value of voltage
    voltage = ( voltage - i) * 100;
    i = (unsigned int )voltage;

    //---------------------- Voltage Display -------------------------------------//
    j[0] =  i/10 + 0x30;
    i = (i % 10) ;
    j[1] = i + 0x30;
    LCD_print_char(122,50,0x0000,j[0],(char *)cour10_font_array);        //values of the fractional voltage (after dot)
    LCD_print_char(129,50,0x0000,j[1],(char *)cour10_font_array);

    //---------------------  Temperature Display  ----------------------------------//

    temp_data[0] = (temp /10) + 0x30;
    temp_data[1] = (temp % 10) + 0x30 ;
    LCD_print_char(117,77,0x0000,temp_data[0],(char *)cour10_font_array);  //Values of the temperature
    LCD_print_char(125,77,0x0000,temp_data[1],(char *)cour10_font_array);

    //------------------------  LCD symbol and outline ---------------------------------------------------//

   // LCD_draw_box(22,40,50,90,RGB16(0,0,0),0);       //Black outline for the battery symbol
   // LCD_draw_box(23,41,48,88,RGB16(255,255,255),1); //white color filled in battery

    //---------------------------  Battery Status colors  -----------------------------------------------//

    SOC_int =(unsigned int)SOC;
    if (clmb_cnt_underflw_flag != 1 && SOC_int != 0 && SOC_int != 100)
      {
      	j[0] = SOC_int/10 + 0x30;
      	SOC_int = (SOC_int % 10) ;
      	j[1] = SOC_int + 0x30;

      if(k[0] != j[0] || k[1] != j[1] || run_once == 1)
       {
    	LCD_draw_box(22,104,159,150,RGB16(89,0,179),1);   //Blue background
      	if(j[0] != 0x30)
        LCD_print_char(25,105,RGB16(255,255,255),j[0],(char *)cour10_font_array);
      	LCD_print_char(34,105,RGB16(255,255,255),j[1],(char *)cour10_font_array);
      	LCD_print_char(43,105,RGB16(255,255,255),'%',(char *)cour10_font_array);
      	LCD_draw_box(50,105,159,115,RGB16(89,0,179),1);

      	k[0]=j[0];
      	k[1]=j[1];
      	run_once = 0;  //CEB
       }
     }
    SOC_int =(unsigned int)SOC;
    if(SOC_int != SOC_prev)
    {
        //------------------------  LCD symbol and outline ---------------------------------------------------//

        LCD_draw_box(22,40,50,90,RGB16(0,0,0),0);       //Black outline for the battery symbol
        LCD_draw_box(23,41,48,88,RGB16(255,255,255),1); //white color filled in battery

    if(clmb_cnt_underflw_flag == 1 || SOC_int == 0)
       {
       	LCD_draw_round_corner_box (22,104,159,150,1,RGB16(89,0,179),1);
       	LCD_draw_box(23,87,48,88,RGB16(255,0,0),1);
       	LCD_print_string(22,105,RGB16(255,255,255),(char *)cour10_font_array,"< 1%");
       }
    else if(SOC >= 1.0 && SOC < 20.0)
      LCD_draw_box(23,90-((SOC_int/2)+3),48,88,RGB16(255,0,0),1);     //Red

    else if ( SOC >= 20.0 && SOC <= 40.0)
      LCD_draw_box(23,90-((SOC_int/2)+1),48,88,RGB16(255,100,0),1);   //Orange

    else if(SOC > 40.0 && SOC < 100.0)
      LCD_draw_box(23,90-((SOC_int/2)+1),48,88,RGB16(0,255,0),1);     //Green

    else if(SOC == 100.0)
      {
    	LCD_draw_round_corner_box (5,104,159,150,1,RGB16(89,0,179),1);
    	LCD_draw_box(23,41,48,88,RGB16(255,255,255),1); //white color filled in battery
    	LCD_draw_box(23,41,48,88,RGB16(0,255,0),1); //white color filled in battery
    	LCD_print_string(15,105,RGB16(255,255,255),(char *)cour10_font_array," Full");
      }
    SOC_prev = SOC_int;
    }
}

//*************************************************************************************************************************
// Name    : Read the battery voltage
//
// Purpose : This function reads the battery voltage via I2c and return it as well as assign ACK to bat connection variable
//***************************************************************************************************************************/
float ReadBattVolt()
{
    unsigned int i=0,rcv_value[2]={0,0};
    int ret_value;

    *BattGasGaugeI2C_Tx  = 0xc8;
    *BattGasGaugeI2C_Cmd   = 0x90;
    BattGasGaugeI2C_TIP();
    usleep(200);
    ret_value = BattGasGaugeI2C_ACK();
    batt_conn_dis_status = ret_value;

    *BattGasGaugeI2C_Tx  = 0x01;
    *BattGasGaugeI2C_Cmd   = 0x10;
    BattGasGaugeI2C_TIP();

    *BattGasGaugeI2C_Tx  = 0xFC;
    *BattGasGaugeI2C_Cmd   = 0x50;
    BattGasGaugeI2C_TIP();
    usleep(100);

    *BattGasGaugeI2C_Tx  = 0xc8;
    *BattGasGaugeI2C_Cmd   = 0x90;
    BattGasGaugeI2C_TIP();

    *BattGasGaugeI2C_Tx  = 0x08;
    *BattGasGaugeI2C_Cmd   = 0x10;
    BattGasGaugeI2C_TIP();

    *BattGasGaugeI2C_Tx  = 0xc9;
    *BattGasGaugeI2C_Cmd   = 0x90;
    BattGasGaugeI2C_TIP();

    *BattGasGaugeI2C_Cmd   = 0x28;    //command for read and NAK
    BattGasGaugeI2C_TIP();
    usleep(10000);
    rcv_value[0] = *BattGasGaugeI2C_Rx;

    *BattGasGaugeI2C_Cmd   = 0x40;

     usleep(100);

    *BattGasGaugeI2C_Tx  = 0xc8;
    *BattGasGaugeI2C_Cmd   = 0x90;
    BattGasGaugeI2C_TIP();

    *BattGasGaugeI2C_Tx  = 0x09;
    *BattGasGaugeI2C_Cmd   = 0x10;
    BattGasGaugeI2C_TIP();

    *BattGasGaugeI2C_Tx  = 0xc9;
    *BattGasGaugeI2C_Cmd   = 0x90;
    BattGasGaugeI2C_TIP();

    *BattGasGaugeI2C_Cmd   = 0x28;    //command for read and NAK
    BattGasGaugeI2C_TIP();
    usleep(100);

    rcv_value[1] = *BattGasGaugeI2C_Rx;
    *BattGasGaugeI2C_Cmd   = 0x40;

    i = (rcv_value[0] << 8 ) | rcv_value[1];
    return i;
}

//**************************************************************************************
// Name    : Read the battery charge
//
// Purpose : This function reads the charge stored in the battery via I2C and return it
//****************************************************************************************/
unsigned int ReadBattCharge()
{
    unsigned int i=0,rcv_value[2]={0,0};
    int ret_value;

    *BattGasGaugeI2C_Tx  = 0xc8;
    *BattGasGaugeI2C_Cmd   = 0x90;
    BattGasGaugeI2C_TIP();
    ret_value = BattGasGaugeI2C_ACK();
    batt_conn_dis_status = ret_value;

    *BattGasGaugeI2C_Tx  = 0x01;
    *BattGasGaugeI2C_Cmd   = 0x10;
    BattGasGaugeI2C_TIP();

    *BattGasGaugeI2C_Tx  = 0x2c;
    *BattGasGaugeI2C_Cmd   = 0x50;
    BattGasGaugeI2C_TIP();


    *BattGasGaugeI2C_Tx  = 0xc8;
    *BattGasGaugeI2C_Cmd   = 0x90;
    BattGasGaugeI2C_TIP();

    *BattGasGaugeI2C_Tx  = 0x02; //C (ACR=MSB)register address
    *BattGasGaugeI2C_Cmd   = 0x10;
    BattGasGaugeI2C_TIP();

    *BattGasGaugeI2C_Tx  = 0xc9;
    *BattGasGaugeI2C_Cmd   = 0x90;
    BattGasGaugeI2C_TIP();

    *BattGasGaugeI2C_Cmd   = 0x20;    //command for read and ACK  for C register (MSB)
    BattGasGaugeI2C_TIP();
    rcv_value[0] = *BattGasGaugeI2C_Rx;

    usleep(100);

    *BattGasGaugeI2C_Cmd   = 0x28;        //command for read and NACK  for D register (LSB)
    BattGasGaugeI2C_TIP();
    rcv_value[1] = *BattGasGaugeI2C_Rx;
    usleep(100);
    *BattGasGaugeI2C_Cmd   = 0x40; //STOP condition

    i = (rcv_value[0] << 8 ) | rcv_value[1];
    return i;
}

//*********************************************************************
// Name    : Read the battery temperature
//
// Purpose : This function reads the temperature via I2C and return it
//***********************************************************************/
unsigned int ReadBattTemp()
{
    float batt_temp;
    unsigned int i=0,rcv_value[2]={0,0};
    int ret_value;

    *BattGasGaugeI2C_Tx  = 0xc8;
    *BattGasGaugeI2C_Cmd   = 0x90;
    BattGasGaugeI2C_TIP();
    ret_value = BattGasGaugeI2C_ACK();
    batt_conn_dis_status = ret_value;

    *BattGasGaugeI2C_Tx  = 0x0C;
    *BattGasGaugeI2C_Cmd   = 0x10;
    BattGasGaugeI2C_TIP();

    *BattGasGaugeI2C_Tx  = 0xc9;
    *BattGasGaugeI2C_Cmd   = 0x90;
    BattGasGaugeI2C_TIP();

    *BattGasGaugeI2C_Cmd   = 0x28;    //command for read and NAK
    BattGasGaugeI2C_TIP();
    usleep(10000);
    rcv_value[0] = *BattGasGaugeI2C_Rx;

    *BattGasGaugeI2C_Cmd   = 0x40;

     usleep(100);

    *BattGasGaugeI2C_Tx  = 0xc8;
    *BattGasGaugeI2C_Cmd   = 0x90;
    BattGasGaugeI2C_TIP();

    *BattGasGaugeI2C_Tx  = 0x0D;
    *BattGasGaugeI2C_Cmd   = 0x10;
    BattGasGaugeI2C_TIP();

    *BattGasGaugeI2C_Tx  = 0xc9;
    *BattGasGaugeI2C_Cmd   = 0x90;
    BattGasGaugeI2C_TIP();

    *BattGasGaugeI2C_Cmd   = 0x28;    //command for read and NAK
    BattGasGaugeI2C_TIP();
    usleep(100);

    rcv_value[1] = *BattGasGaugeI2C_Rx;
    *BattGasGaugeI2C_Cmd   = 0x40;

    i = (rcv_value[0] << 8 ) | rcv_value[1];
    batt_temp = (float)((i * 600)/0xFFFF);
    batt_temp = batt_temp - 273.0;
    i = batt_temp;
    return i;
}

//********************************************************************************************************************
// Name    : I2C Acknowledgment Checker
//
// Purpose : This function checks whether the ACK is received from the slave or not and accordingly return the values
//*********************************************************************************************************************/
unsigned int  BattGasGaugeI2C_ACK()
{
	int t=0;
	t= *BattGasGaugeI2C_Status & 0x80 ;
	if(t == 0x80)
       return 1;
    else
	   return 0;
}

//********************************************************************************
// Name    : I2C Transfer Completion Checker
//
//Purpose : This function checks whether the transfer is in progress or completed
//********************************************************************************/
void BattGasGaugeI2C_TIP()
{
    int t;
    t= *BattGasGaugeI2C_Status & 0x2;
    while(t== 0x2)
    {
        t= *BattGasGaugeI2C_Status & 0x2;
        if(t == 0x0)
        break;
    }
}
/*********************************************************************************/

