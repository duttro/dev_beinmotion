//-!!S L S  C O N F I D E N T I A L!!------------------------------------------
// @   Copyright (c) 2001-2010, System Level Solutions (India) Pvt. Ltd.   @
// @                         All rights reserved.                          @
// @                                                                       @
// @    THIS SOFTWARE CONTAINS VALUABLE CONFIDENTIAL AND PROPRIETARY       @
// @    INFORMATION OF SYSTEM LEVEL SOLUTIONS (INDIA) PVT. LTD. AND IS     @
// @    SUBJECTED TO APPLICABLE LICENSING AGREEMENTS. UNAUTHORIZED         @
// @    REPRODUCTION, TRANSMISSION OR DISTRIBUTION OF THIS FILE AND ITS    @
// @    CONTENTS IS A VIOLATION OF APPLICABLE LAWS.                        @
//
//-C O N T A C T---------------------------------------------------------------
// Website      : http://www.slscorp.com
// Email        : info@slscorp.com
// Phone        : +91-2692-232501/232502
// Fax          : +91-2692-232503
//
//-P R O J E C T---------------------------------------------------------------
// Project      : BeMicro SDK Motor Control Add-on Board
// Client       : Altera
//
//-F I L E  D E T A I L S------------------------------------------------------
// Design Unit  : IR Receiver
// File         : ir_receiver.v
// Author       : Hardik Sheth - hsheth@slscorp.com 
// Created      : 26th April,2011
// Description  : 
//
//-S O U R C E  C O N T R O L--------------------------------------------------
// $Id: 
//-----------------------------------------------------------------------------

module ir_receiver ( 
  input  wire        clk,
  input  wire        reset_n,
  input  wire        in_port,
  
  input  wire [31:0] writedata,
  input  wire        address,
  input  wire        write_n,
  input  wire        read_n,
  input  wire        chipselect,
  output reg [31:0] readdata,
  
  output reg        waitrequest,
  output reg        irq
);


reg  in_port_f1,in_port_f2,in_port_f3,in_port_f4,in_port_f5,in_port_f6;
wire in_port_latch;
reg  in_port_latch_f1;
wire in_port_pl;
reg  [31:0] edge_count;
reg  edge_count_clear;
reg  [31:0] edge_count_load;

always @(posedge clk or negedge reset_n)
  if(~reset_n)
    in_port_f1 <=#1 1'b0;
  else
    in_port_f1 <=#1 in_port;


always @(posedge clk or negedge reset_n)
  if(~reset_n)
    in_port_f2 <=#1 1'b0;
  else
    in_port_f2 <=#1 in_port_f1;

always @(posedge clk or negedge reset_n)
  if(~reset_n)
    in_port_f3 <=#1 1'b0;
  else
    in_port_f3 <=#1 in_port_f2;
    
always @(posedge clk or negedge reset_n)
  if(~reset_n)
    in_port_f4 <=#1 1'b0;
  else
    in_port_f4 <=#1 in_port_f3;    
    
always @(posedge clk or negedge reset_n)
  if(~reset_n)
    in_port_f5 <=#1 1'b0;
  else
    in_port_f5 <=#1 in_port_f4;    
  
always @(posedge clk or negedge reset_n)
  if(~reset_n)
    in_port_f6 <=#1 1'b0;
  else
    in_port_f6 <=#1 in_port_f5;  
  
assign in_port_latch =   in_port_f1 & in_port_f2 & in_port_f3 & in_port_f4 & in_port_f5 & in_port_f6; 

always @(posedge clk or negedge reset_n)
  if(~reset_n)
    in_port_latch_f1 <=#1 1'b0;
  else
    in_port_latch_f1 <=#1 in_port_latch;
    
    
assign in_port_pl = in_port_latch_f1 && ~in_port_latch;

always @(posedge clk or negedge reset_n)
  if(~reset_n)
    edge_count <=#1 32'h0;
  else
  if(~edge_count_clear )
    edge_count <=#1 32'h0;
  else
  if(edge_count == edge_count_load)
    edge_count <=#1 edge_count;
  else  
  if(in_port_pl)
    edge_count <=#1 edge_count + 32'h1;
    
always @(posedge clk or negedge reset_n)
  if(~reset_n)
    begin
      edge_count_clear <=#1 1'b0;     
      readdata         <=#1 32'h0;
      edge_count_load  <=#1 32'h1;
    end
  else
    case({write_n,read_n,address})
      3'b010  :   begin   // Write en/clear
                    edge_count_clear <=#1 writedata[0];
                  end               
      3'b011  :   begin
                    edge_count_load  <=#1 writedata;
                  end
      3'b101  :   begin
                    readdata <= edge_count;
                  end
      default :   begin
                    readdata <= edge_count;
                    edge_count_clear <=#1 edge_count_clear;
                    edge_count_load  <=#1 edge_count_load;
                  end
    endcase              

always @(posedge clk or negedge reset_n)
  if(~reset_n)
    waitrequest <=#1 1'b1;    
  else
  if((chipselect && ~write_n) | (chipselect && ~read_n))
    waitrequest <=#1 1'b0;
  else
    waitrequest <=#1 1'b1;
    
    
always @(posedge clk or negedge reset_n)
  if(~reset_n)
    irq <=#1 1'b0;
  else
  if(~write_n && chipselect && (address ==0))
    irq <=#1 writedata[1];
  else
  if(edge_count == edge_count_load)
    irq <=#1 1'b1;
      
endmodule    