
//-!!S L S  C O N F I D E N T I A L!!------------------------------------------
// @   Copyright (c) 2001-2010, System Level Solutions (India) Pvt. Ltd.   @
// @                         All rights reserved.                          @
// @                                                                       @
//
//-C O N T A C T---------------------------------------------------------------
// Website      : http://www.slscorp.com
// Email        : info@slscorp.com
// Phone        : +91-2692-232501/232502
// Fax          : +91-2692-232503
//
//-P R O J E C T---------------------------------------------------------------
// Project      : BeMicro Motor Control Application
// Client       : Altera
//
//-F I L E  D E T A I L S------------------------------------------------------
// Design Unit  : Stepper Motor Controller
// File         : st_motor_cntrlr.v
// Author       : Hardik Sheth -hsheth@slscorp.com
// Created      : 3rd June, 2011
//
//-S O U R C E  C O N T R O L--------------------------------------------------
// $Id:  $
//-----------------------------------------------------------------------------

`timescale 1ns/100ps
module st_motor_top (
   input   wire         clk,
   input   wire         reset_n,   
   input   wire         write_n,
   input   wire         read_n,
   input   wire         chipselect,
   input   wire  [ 2:0] address,
   input   wire  [31:0] writedata,
   output  reg   [31:0] readdata,
	
   output  wire  [ 3:0] st_output
);



  reg   [31:0]    freq_counter;
  reg             st_clk;
  
  wire            write = ( ~write_n && chipselect && read_n );
  wire            read  = (  write_n && chipselect && ~read_n );
  reg   [31:0]    step_count_reg;
  reg   [ 2:0]    current_state;
  reg             full_mode_en;
  reg   [ 3:0]    full_output,half_output,wave_output,full_micro_output;
  
  reg   [31:0]    control_reg;
  reg   [ 7:0]    command_reg;
  reg             mode_op_cmp;
  reg   [ 1:0]    CS_FULL_MODE;
  reg   [ 2:0]    CS_HALF_MODE;
  reg   [ 1:0]    CS_WAVE_MODE;
  reg   [ 1:0]    CS_MICRO_MODE;
  reg   [31:0]    step_count; 
  reg             half_mode_en;
  reg             wave_mode_en;
  reg             micro_mode_en;

  
  wire  [27:0]    st_freq      = control_reg[31:4];
  wire            direction    = control_reg[0];
  wire  [2:0]     mode         = control_reg[3:1];
  wire            start        = command_reg[0];
  wire            stop         = command_reg[1];
  wire            step_cmp;
  wire  [31:0]    st_free_count;
  wire  [3:0]     micro_output;
  

//------------------------------------Micro step parameters-----------------//

  reg  [31:0]  free_count;         //Free runnning counter
  reg  [6:0]   count_127;         // 7 bit counter for comparision with data
  
  //Number of pulses required in positive half in each winding
  reg  [3:0]  count_a;
  reg  [3:0]  count_b;
  
  //Data loaded to generate the pulses in both windings
  reg  [6:0]  data_a;
  reg  [6:0]  data_b;
   
  //continuous pulses in winding "A-A1" and "B-B1"
  reg         pulse_a;
  reg         pulse_b;
  
  //Compare Registers for both the windings
  reg         cmp_reg_a;
  reg         cmp_reg_b;

  
  assign step_cmp = ( step_count_reg == step_count );
  assign  st_output = full_mode_en ? full_output : (half_mode_en? half_output : (wave_mode_en ? wave_output : micro_output)) ;
   
 /************Microstep outputs***************************/
  assign  micro_output[0] = pulse_a & full_micro_output[0];
  assign  micro_output[1] = pulse_b & full_micro_output[1]; 
  assign  micro_output[2] = pulse_a & full_micro_output[2];
  assign  micro_output[3] = pulse_b & full_micro_output[3];

  parameter [2:0] IDLE      =  3'b000,
                  WAVE      =  3'b001,
                  HALF      =  3'b010,
                  FULL      =  3'b011,
                  MICRO     =  3'b100; 
                  
  parameter [1:0] WAVE_MODE1 = 2'b00,
                  WAVE_MODE2 = 2'b01,
	          WAVE_MODE3 = 2'b10,
	          WAVE_MODE4 = 2'b11;                
						
  parameter [1:0] FULL_MODE1 = 2'b00,
                  FULL_MODE2 = 2'b01,
	          FULL_MODE3 = 2'b10,
	          FULL_MODE4 = 2'b11;
                  
  parameter [2:0] HALF_MODE1 = 3'b000,                 
                  HALF_MODE2 = 3'b001,
                  HALF_MODE3 = 3'b010,
                  HALF_MODE4 = 3'b011,
                  HALF_MODE5 = 3'b100,
                  HALF_MODE6 = 3'b101,
                  HALF_MODE7 = 3'b110,
                  HALF_MODE8 = 3'b111;
                  
  parameter [1:0] MICRO_MODE1 = 2'b00,
                  MICRO_MODE2 = 2'b01,
	          MICRO_MODE3 = 2'b10,
	          MICRO_MODE4 = 2'b11;                 
				       		
      
  always @(posedge clk or negedge reset_n)
    if(~reset_n)
      st_clk <= #1 1'b0;
    else
      if(freq_counter == st_freq )
        st_clk <=#1 1'b1;
      else
        st_clk <=#1 1'b0;
        
  always @(posedge clk or negedge reset_n)      
    if(~reset_n)
      freq_counter <=#1 32'h0;
    else    
    if(freq_counter == st_freq)
      freq_counter <=#1 32'h0;
    else
      freq_counter <=#1 freq_counter + 32'h1;
       
   
  always @(posedge clk or negedge reset_n)
    if(~reset_n)
      begin
        control_reg    <= #1 32'h00;
        command_reg    <= #1 8'h0;
        step_count_reg <= #1 32'h0; 
      end
    else
      if(write)
        case(address)
          3'b000   :   control_reg <=#1 writedata;
          3'b001   :   command_reg <=#1 writedata[7:0];
          3'b010   :   step_count_reg <=#1 writedata;          
        endcase
      else
      if(read)
        case(address)
          3'b000   :   readdata  <=#1 control_reg;
          3'b001   :   readdata  <=#1 {31'h0,(current_state == IDLE)};
          3'b010   :   readdata  <=#1 step_count_reg;
        endcase
      else
        begin
          command_reg <=#1 8'h0;
        end
  
  
  
  always @(posedge clk or negedge reset_n)
    if(~reset_n)
      begin
        current_state  <=#1 IDLE;
        full_mode_en   <=#1 1'b0;
        half_mode_en   <=#1 1'b0;
        wave_mode_en   <=#1 1'b0;
        micro_mode_en  <=#1 1'b0;
      end
    else
      begin
        full_mode_en   <=#1 1'b0;
        half_mode_en   <=#1 1'b0;
        wave_mode_en   <=#1 1'b0;
        micro_mode_en  <=#1 1'b0;
        case(current_state)
          IDLE  :  begin
                     if(start)
                       begin   
                         case ( mode )
                            3'b000 : current_state <=#1 WAVE;
                            3'b001 : current_state <=#1 HALF;
                            3'b010 : current_state <=#1 FULL;
                            3'b011 : current_state <=#1 MICRO;
                           default : current_state <=#1 IDLE;
                         endcase
                       end  
                   end
                  
           WAVE :  begin
                     wave_mode_en <=#1 1'b1;
                     if(mode_op_cmp || stop)
		       current_state <=#1 IDLE;
		     else
		       current_state <=#1 WAVE;
                   end
               
           HALF :  begin
                     half_mode_en <=#1 1'b1;
                     if(mode_op_cmp || stop)
                       current_state <=#1 IDLE;
                     else
                       current_state <=#1 HALF;                     
                   end
                   
           FULL :  begin
                     full_mode_en <=#1 1'b1;
                     if(mode_op_cmp || stop)
                       current_state <=#1 IDLE;
                     else
                       current_state <=#1 FULL;
                   end
                   
                    
           MICRO : begin
                     micro_mode_en <=#1 1'b1;
                     if(mode_op_cmp || stop)
                       current_state <=#1 IDLE;
                     else
                       current_state <=#1 MICRO;
                   end         
        endcase
      end
  
 
  
  always @(full_mode_en or reset_n or step_cmp or half_mode_en or wave_mode_en or micro_mode_en)
    if(~reset_n)
      mode_op_cmp <=#1 1'b1;
    else
    if(full_mode_en | half_mode_en | wave_mode_en | micro_mode_en)
      begin      
        if(step_cmp)
          mode_op_cmp <=#1 1'b1;
        else
          mode_op_cmp <=#1 1'b0;
      end
    else		
      mode_op_cmp <= #1 1'b0;		
   
  
  always @(posedge clk or negedge reset_n)
    if(~reset_n)
      step_count <=#1 32'h0;
    else  
    if(st_clk && (full_mode_en | half_mode_en | wave_mode_en | micro_mode_en) )
      step_count <=#1 step_count + 32'h1;
    else
    if( ~full_mode_en && ~half_mode_en && ~wave_mode_en && ~micro_mode_en)
      step_count <=#1 32'h0;   


//*****************************************************
//
//                    FULL Mode
//
//*****************************************************  

  always @(posedge st_clk or negedge reset_n)
    if(~reset_n )
      begin        
        full_output <=#1 4'h0;
        CS_FULL_MODE<=#1 FULL_MODE1;
      end
    else
    if( ~full_mode_en )	 
      begin        
        full_output <=#1 4'h0;
        CS_FULL_MODE<=#1 FULL_MODE1;
      end	 
    else
      begin
        if(direction)
          case(CS_FULL_MODE)
            FULL_MODE1  : begin                            
                            full_output <=#1 4'b1100;
                            CS_FULL_MODE<=#1 FULL_MODE2;
                          end
            FULL_MODE2  : begin
                            full_output <=#1 4'b1001;
                            CS_FULL_MODE<=#1 FULL_MODE3;
                          end
            FULL_MODE3  : begin
                            full_output <=#1 4'b0011;
                            CS_FULL_MODE<=#1 FULL_MODE4;
                          end
            FULL_MODE4  : begin
                            full_output <=#1 4'b0110;
                            CS_FULL_MODE<=#1 FULL_MODE1;
                          end                        
          endcase 
        else
        if(~direction)
          case(CS_FULL_MODE)
            FULL_MODE1  : begin                            
                            full_output <=#1 4'b1100;
                            CS_FULL_MODE<=#1 FULL_MODE2;
                          end
            FULL_MODE2  : begin
                            full_output <=#1 4'b0110;
                            CS_FULL_MODE<=#1 FULL_MODE3;
                          end
            FULL_MODE3  : begin
                            full_output <=#1 4'b0011;
                            CS_FULL_MODE<=#1 FULL_MODE4;
                          end
            FULL_MODE4  : begin
                            full_output <=#1 4'b1001;
                            CS_FULL_MODE<=#1 FULL_MODE1;
                          end                        
          endcase          
      end
        
        
 //***************************************************
 //
 //                  WAVE Mode
 //
 //
 //***************************************************
   
   always @(posedge st_clk or negedge reset_n)
       if(~reset_n )
         begin        
           wave_output <=#1 4'h0;
           CS_WAVE_MODE<=#1 WAVE_MODE1;
         end
       else
       if( ~wave_mode_en )	 
         begin        
           wave_output <=#1 4'h0;
           CS_WAVE_MODE<=#1 WAVE_MODE1;
         end	 
       else
         begin
           if(direction)
             case(CS_WAVE_MODE)
               WAVE_MODE1  : begin                            
                               wave_output <=#1 4'b1000;
                               CS_WAVE_MODE<=#1 WAVE_MODE2;
                             end
               WAVE_MODE2  : begin
                               wave_output <=#1 4'b0001;
                               CS_WAVE_MODE<=#1 WAVE_MODE3;
                             end
               WAVE_MODE3  : begin
                               wave_output <=#1 4'b0010;
                               CS_WAVE_MODE<=#1 WAVE_MODE4;
                             end
               WAVE_MODE4  : begin
                               wave_output <=#1 4'b0100;
                               CS_WAVE_MODE<=#1 WAVE_MODE1;
                             end                        
             endcase 
           else
           if(~direction)
             case(CS_WAVE_MODE)
               WAVE_MODE1  : begin                            
                               wave_output <=#1 4'b1000;
                               CS_WAVE_MODE<=#1 WAVE_MODE2;
                             end
               WAVE_MODE2  : begin
                               wave_output <=#1 4'b0100;
                               CS_WAVE_MODE<=#1 WAVE_MODE3;
                             end
               WAVE_MODE3  : begin
                               wave_output <=#1 4'b0010;
                               CS_WAVE_MODE<=#1 WAVE_MODE4;
                             end
               WAVE_MODE4  : begin
                               wave_output <=#1 4'b0001;
                               CS_WAVE_MODE<=#1 WAVE_MODE1;
                             end                        
             endcase          
      end
        
//*****************************************************
//
//                    HALF Mode
//
//*****************************************************

  always @(posedge st_clk or negedge reset_n)
    if(~reset_n )
      begin        
        half_output <=#1 4'h0;
        CS_HALF_MODE<=#1 HALF_MODE1;
      end
    else
    if( ~half_mode_en )  
      begin        
        half_output <=#1 4'h0;
        CS_HALF_MODE<=#1 HALF_MODE1;
      end    
    else
      begin
        if(direction)
          case(CS_HALF_MODE)
            HALF_MODE1  : begin                            
                            half_output <=#1 4'b1100;
                            CS_HALF_MODE<=#1 HALF_MODE2;
                          end
            HALF_MODE2  : begin                            
                            half_output <=#1 4'b1000;
                            CS_HALF_MODE<=#1 HALF_MODE3;
                          end                     
            HALF_MODE3  : begin                            
                            half_output <=#1 4'b1001;
                            CS_HALF_MODE<=#1 HALF_MODE4;
                          end                          
            HALF_MODE4  : begin                            
                            half_output <=#1 4'b0001;
                            CS_HALF_MODE<=#1 HALF_MODE5;
                          end   
            HALF_MODE5  : begin                            
                            half_output <=#1 4'b0011;
                            CS_HALF_MODE<=#1 HALF_MODE6;
                          end  
            HALF_MODE6  : begin                            
                            half_output <=#1 4'b0010;
                            CS_HALF_MODE<=#1 HALF_MODE7;
                          end  
            HALF_MODE7  : begin                            
                            half_output <=#1 4'b0110;
                            CS_HALF_MODE<=#1 HALF_MODE8;
                          end  
            HALF_MODE8  : begin                            
                            half_output <=#1 4'b0100;
                            CS_HALF_MODE<=#1 HALF_MODE1;
                          end                              
          endcase 
        else
        if(~direction)
          case(CS_HALF_MODE)
            HALF_MODE1  : begin                            
                            half_output <=#1 4'b1100;
                            CS_HALF_MODE<=#1 HALF_MODE2;
                          end
            HALF_MODE2  : begin                            
                            half_output <=#1 4'b0100;
                            CS_HALF_MODE<=#1 HALF_MODE3;
                          end                     
            HALF_MODE3  : begin                            
                            half_output <=#1 4'b0110;
                            CS_HALF_MODE<=#1 HALF_MODE4;
                          end                          
            HALF_MODE4  : begin                            
                            half_output <=#1 4'b0010;
                            CS_HALF_MODE<=#1 HALF_MODE5;
                          end   
            HALF_MODE5  : begin                            
                            half_output <=#1 4'b0011;
                            CS_HALF_MODE<=#1 HALF_MODE6;
                          end  
            HALF_MODE6  : begin                            
                            half_output <=#1 4'b0001;
                            CS_HALF_MODE<=#1 HALF_MODE7;
                          end  
            HALF_MODE7  : begin                            
                            half_output <=#1 4'b1001;
                            CS_HALF_MODE<=#1 HALF_MODE8;
                          end  
            HALF_MODE8  : begin                            
                            half_output <=#1 4'b1000;
                            CS_HALF_MODE<=#1 HALF_MODE1;
                          end                              
          endcase     
      end
      
  //*******************************************************
  //
  //                MICRO Mode
  //
  //******************************************************/
  always @(posedge st_clk or negedge reset_n)
    if(~reset_n )
      begin        
        full_micro_output <=#1 4'h0;
        CS_MICRO_MODE<=#1 MICRO_MODE1;
      end
    else
    if( ~micro_mode_en )	 
      begin        
        full_micro_output <=#1 4'h0;
        CS_MICRO_MODE<=#1 MICRO_MODE1;
      end	 
    else
      if(count_a==7 || count_a==15)
      begin
        if(direction)
          case(CS_MICRO_MODE)
            MICRO_MODE1  : begin                            
                            full_micro_output <=#1 4'b1100;
                            CS_MICRO_MODE<=#1 MICRO_MODE2;
                          end
            MICRO_MODE2  : begin
                            full_micro_output <=#1 4'b1001;
                            CS_MICRO_MODE<=#1 MICRO_MODE3;
                          end
            MICRO_MODE3  : begin
                            full_micro_output <=#1 4'b0011;
                            CS_MICRO_MODE<=#1 MICRO_MODE4;
                          end
            MICRO_MODE4  : begin
                            full_micro_output <=#1 4'b0110;
                            CS_MICRO_MODE<=#1 MICRO_MODE1;
                          end                        
          endcase 
        else
        if(~direction)
          case(CS_MICRO_MODE)
            MICRO_MODE1  : begin                            
                            full_micro_output <=#1 4'b1100;
                            CS_MICRO_MODE<=#1 MICRO_MODE2;
                          end
            MICRO_MODE2  : begin
                            full_micro_output <=#1 4'b0110;
                            CS_MICRO_MODE<=#1 MICRO_MODE3;
                          end
            MICRO_MODE3  : begin
                            full_micro_output <=#1 4'b0011;
                            CS_MICRO_MODE<=#1 MICRO_MODE4;
                          end
            MICRO_MODE4  : begin
                            full_micro_output <=#1 4'b1001;
                            CS_MICRO_MODE<=#1 MICRO_MODE1;
                          end                        
          endcase          
      end    
      
//------------------------------------Micro step logic--------------------------------//


assign st_free_count = st_freq >> 7;

/************Block for the free running counter with specified limits***********************/
  always @(posedge clk or negedge reset_n)
    begin
      if(~reset_n)
   	    free_count <= 0;
      else if(free_count == st_free_count)
        free_count <= 0;
      else    
        free_count <= free_count + 1;
    end


/******Block to assign condition when 7 bit counter should be started*************/   
 always @(posedge clk or negedge reset_n)
   begin
    if(~reset_n)
        count_127 <= 0;
    else if(free_count==st_free_count)  	
       begin
          count_127 <= count_127 + 1;
          if(count_127 ==7'd124)
          begin
            count_127 <= 0;
          end
       end 
   end
   
  /******Block to assign condition when 7 bit counter should be started*************/   
 always @(posedge st_clk or negedge reset_n)
   begin
    if(~reset_n)
     	count_a <= 0;
    else 
        count_a <= count_a + 4'b1;
  end 
  
 /**********Block to increment the pulses (total 16)************/
 always @(posedge st_clk or negedge reset_n)
   begin
    if(~reset_n)
        count_b <= 0;
    else 
        count_b <= count_b + 4'b1;
   end 


/********Values of data for "A and A1"to compare with the counter to generate the pulse**********/   
 always @(posedge clk or negedge reset_n)
   begin
     if(~reset_n)
     	data_a = 0;        //original:data_a
     else
       begin
         case(count_a)
         	4'b0000 : data_a = 8'd0;
	        4'b0001 : data_a = 8'd18;
	        4'b0010 : data_a = 8'd36;
	        4'b0011 : data_a = 8'd54;        //UP
	        4'b0100 : data_a = 8'd72;
	        4'b0101 : data_a = 8'd90;
	        4'b0110 : data_a = 8'd108;
	        4'b0111 : data_a = 8'd124;
	         	
	        4'b1000 : data_a = 8'd124;
	        4'b1001 : data_a = 8'd108;
	       	4'b1010 : data_a = 8'd90;
	 	4'b1011 : data_a = 8'd72;        //Down
	 	4'b1100 : data_a = 8'd54;
	       	4'b1101 : data_a = 8'd36;
	 	4'b1110 : data_a = 8'd18;
		4'b1111 : data_a = 8'd0;
       endcase
     end
   end   
   
   /************Values of the data of "B and B1" to generate the pulse*************/
    always @(posedge clk or negedge reset_n)
   begin
     if(~reset_n)
     	data_b = 0;      //original :  data_b
     else 
       begin
         case(count_b)
         	4'b0000 : data_b = 8'd124;
	        4'b0001 : data_b= 8'd108;
	        4'b0010 : data_b = 8'd90;
	        4'b0011 : data_b = 8'd72;        //UP
	        4'b0100 : data_b = 8'd54;
	        4'b0101 : data_b = 8'd36;
	        4'b0110 : data_b = 8'd18;
	        4'b0111 : data_b = 8'd0;
	         	
	        4'b1000 : data_b = 8'd0;
	        4'b1001 : data_b = 8'd18;
	 	4'b1010 : data_b = 8'd36;
	 	4'b1011 : data_b = 8'd54;        //Down
	 	4'b1100 : data_b = 8'd72;
	 	4'b1101 : data_b = 8'd90;
	       	4'b1110 : data_b = 8'd108;
		4'b1111 : data_b = 8'd124;
       endcase
     end
   end   

  /**********Micro Pulses in "A"*******************/ 
 always @(posedge clk or negedge reset_n)
   begin
     if(~reset_n)
         pulse_a <= 0;
     else if(count_127 == 0)
       pulse_a <= 0;
    else if(count_127 == data_a && cmp_reg_a == 1)
       pulse_a <= ~pulse_a;
   end

 /***********Micro Pulses in "B"****************/
 always @(posedge clk or negedge reset_n)
   begin
      if(~reset_n)
          pulse_b <= 0;
      else if(count_127 == 0)
        pulse_b <= 0;
     else if(count_127 == data_b && cmp_reg_b == 1)
        pulse_b <= ~pulse_b;
  end

/********Compare Register for windings "A" and "A1"*********/   
always @(posedge clk or negedge reset_n)
  begin
    if(~reset_n)
  	cmp_reg_a <= 0;
    else if (count_127 == 0)
  	cmp_reg_a <= 1;
    else if(count_127 == data_a)
  	cmp_reg_a <= 0;
  end	  
      
/********Compare Register for windings "B" and "B1"*********/   
always @(posedge clk or negedge reset_n)
  begin
    if(~reset_n)
  	cmp_reg_b <= 0;
    else if (count_127 == 0)
   	cmp_reg_b <= 1;
    else if(count_127 == data_b)
   	cmp_reg_b <= 0;
  end	

endmodule



                        