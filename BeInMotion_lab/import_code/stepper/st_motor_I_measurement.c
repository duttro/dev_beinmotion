/********************************************************
 volt_diff = v(out) - v(ref)
 V(sense)  = volt_diff
            -----------    where gain=20
               gain
Current    = V(sense)
            ------------       where R(sense) = 0.025 ohm
             R(sense)
**********************************************************/


#include "stdio.h"
#include "system.h"
#include "unistd.h"


#define WAVE_STEP_FWD  0x00
#define WAVE_STEP_BWD  0x01
#define HALF_STEP_FWD  0x02
#define HALF_STEP_BWD  0x03
#define FULL_STEP_FWD  0x04
#define FULL_STEP_BWD  0x05
#define MICRO_STEP_FWD 0x06
#define MICRO_STEP_BWD 0x07



#define CPU_FREQ               50000000
#define ST_MOTOR_FREQ_HZ       350
#define STEP_TO_ROTATE         20000
#define ST_MOTOR_MODE          FULL_STEP_FWD
#define ST_MOTOR_CONTOL_REG   (((CPU_FREQ/ST_MOTOR_FREQ_HZ) << 4 ) | ST_MOTOR_MODE)

int *recieve_reg,*transmit_reg,*status_reg,*control_reg,*slave_sel;
int *step_control_reg,*step_command_reg,*step_cnt_reg;

int main()
{
	  float i,j,sum=0;
	  float avg_cur=0;
	  unsigned int count =0,avg_cur_i,avg_cur_j,volt_diff;
      recieve_reg    =(int*)(ST_CURRENT_SENSOR_BASE);
      transmit_reg   =(int*)(ST_CURRENT_SENSOR_BASE + 0x04);
      status_reg     =(int*)(ST_CURRENT_SENSOR_BASE + 0x08);
      control_reg    =(int*)(ST_CURRENT_SENSOR_BASE + 0x0C);
      slave_sel      =(int*)(ST_CURRENT_SENSOR_BASE + 0x14);

      step_control_reg  =  (int*) (STPR_MOTOR_CNTRL_BASE);
      step_command_reg  =  (int*) (STPR_MOTOR_CNTRL_BASE+0x04);
      step_cnt_reg      =  (int*) (STPR_MOTOR_CNTRL_BASE+0x08);

       usleep(10000);
      *slave_sel = 0x01;



      //------------------------------------------------------------------------------------//
       	    *step_cnt_reg = STEP_TO_ROTATE;
       		*step_control_reg = ST_MOTOR_CONTOL_REG;
       		*step_command_reg = 0x01;
     //---------------------------------------------------------------------------------------//

      while(1)
      {
        *control_reg = 0xC0;
        while((*status_reg & 0x40) != 0x40);
        *transmit_reg = 0x0000; //differential ended mode
        usleep(1000);

        while((*status_reg & 0x80) != 0x80);
        if((*status_reg & 0x80) == 0x80)
        {
          volt_diff = *recieve_reg;  //read rx reg

          usleep(700000);
        }

       i = (volt_diff * 3.3) / 65536;
       volt_diff = (unsigned int) i;

       j = (i-volt_diff) *100;
       volt_diff = (unsigned int) j;

       j = (i/20)/0.025;
       sum = sum + j;
       volt_diff = (unsigned int) j;
       printf(" Current = %d.",(unsigned int) volt_diff);
       i = j-volt_diff; i = i*100;
       volt_diff = (unsigned int) i;
       printf("%02d Amp ",volt_diff);
       count++;

       if(count==10)
       {
    	   count= 0;
    	   avg_cur = (sum / 10.0);
    	   avg_cur_i = (unsigned int)(avg_cur);
    	   printf("  avg_current = %d. ",avg_cur_i);
    	   avg_cur_j = (avg_cur - avg_cur_i)*100;
    	   printf("%02d Amp\n",(unsigned int)(avg_cur_j));
    	   sum=0;
    	   printf("---------------------------------------------------------------");
       }


       printf("\n");
      }
      return 0;
}
