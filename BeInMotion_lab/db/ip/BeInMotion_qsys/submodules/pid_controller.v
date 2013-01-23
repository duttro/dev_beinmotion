`timescale 1ns/100ps
module pid_controller (  
       input wire         clk,
       input wire         reset_n,
       input wire [31:0]  Ref,
       input wire [31:0]  Fdb,
       input wire [31:0]  kp,      
       input wire [31:0]  ki,
       input wire [31:0]  kd,
       input wire [31:0]  Max,
       input wire [31:0]  Min,
       input wire         pid_en,
       output reg         pid_cmp,
       output reg [31:0]  pid_out
);
 
 reg  [31:0] Err,Up,Ui,Ud,Up_prev;
 reg         pid_en_f1,pid_en_f2,pid_en_f3,pid_en_f4,pid_en_f5;  
 reg         temp_pid_cmp;
 
always @(posedge clk or negedge reset_n)
   if(~reset_n)
       pid_en_f1 <= #1 1'b0;
   else 
       pid_en_f1 <= #1 pid_en;
       
always @(posedge clk)
   pid_en_f2 <= #1 pid_en_f1;
always @(posedge clk)
   pid_en_f3 <= #1 pid_en_f2;
always @(posedge clk)
   pid_en_f4 <= #1 pid_en_f3;
always @(posedge clk)
   pid_en_f5 <= #1 pid_en_f4;
   
//-------------- Compute the error ------------------// 
 always @(posedge clk or negedge reset_n)   
   if(~reset_n)
	   Err <= #1 32'h0;
	else if( pid_en_f1 && ( Ref > Fdb ))
		Err <= #1 Ref - Fdb;
	else if( pid_en_f1 && ( Fdb >= Ref ))  
     Err <= #1 Fdb - Ref;
     
//------------- Compute the proportional output -------------//   
 always @(posedge clk or negedge reset_n)
   if( ~reset_n )
     Up <= #1 32'h0;
   else if( pid_en_f2 )                                    // P Controller
     Up <= #1 ((kp * Err));
     
//--------------- Compute the integral output -------------------//
 always @(posedge clk or negedge reset_n)
    if( ~reset_n )
      Ui <= 32'h0;
    else if(( pid_en_f3 ) && ( Ref > Fdb ))                   // I Controller
      Ui <= #1 (Ui + (ki*Up)) ;
    else if(( pid_en_f3 ) && ( Fdb >= Ref ) && ( Ui >= (ki*Up ))) 
      Ui <= #1 (Ui - (ki*Up)) ;

//---------------- Compute the derivative output -----------------//
 always @(posedge clk or negedge reset_n)
    if( ~reset_n )
       begin
       	Ud      <= #1 32'h0;
       	Up_prev <= #1 32'h0;
       end
    else if ( pid_en_f4 )                                 // D Controller
       begin
       	Ud      <= #1 kd*(Up - Up_prev);
       	Up_prev <= #1 Up;
       end
		 
//--------------------Compute the final output --------------------//
always @(posedge clk or negedge reset_n)
  if( ~reset_n )
     begin
	  pid_out      <= #1 32'h0;
	  temp_pid_cmp <= #1 1'b0;
	  end
  else if( pid_en_f5 )
    begin
      pid_out      <= #1 Up + Ui + Ud;   
      temp_pid_cmp <= #1 1'b1;  
	 end
  else
    begin
      pid_out      <= #1 pid_out;
      temp_pid_cmp <= #1 1'b0;
    end  

//-----------PID_cmp Calculation -------/
always @(posedge clk or negedge reset_n)
	if( ~reset_n )
		pid_cmp <= #1 0;
	else if ( pid_en )
      pid_cmp <= #1 0;  	
	else if( temp_pid_cmp == 1 )
		pid_cmp <= #1 temp_pid_cmp;

endmodule        