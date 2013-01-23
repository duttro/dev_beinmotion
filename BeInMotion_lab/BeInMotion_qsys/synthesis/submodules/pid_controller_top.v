`timescale 1ns/100ps
module pid_controller_top (  
       input wire	        clk,
       input wire         reset_n,
       input wire         avalon_chip_select,
       input wire  [2:0]  address,
       input wire         write,
       input wire  [31:0] write_data,
       input  wire        read,
       output reg  [31:0] read_data
 );
  
  reg  pid_en;
  
  reg  [31:0] kp,
              ki,
              kd;
				  
  reg  [31:0] ref_reg,
              fdb_reg;
              
  wire [31:0] pid_out;
  wire        pid_cmp;
 
  wire        Av_write = (  write  && avalon_chip_select && ~read );
  wire        Av_read  = ( ~write  && avalon_chip_select &&  read );           
 
  parameter   Max = 32'hFFFF,
              Min = 32'h0000;
              
/*-------------------------------------------------------------------------------------------*/
 pid_controller p1 (
                     .clk 		       ( clk ),
                     .reset_n 		 ( reset_n ),
							.kp             ( kp ),
                     .ki             ( ki ),
                     .kd             ( kd ),
                     .Max            ( Max ),
                     .Min            ( Min ), 
                     .Ref            ( ref_reg ),
                     .Fdb 		       ( fdb_reg ),
                     .pid_en 	       ( pid_en ),
                     .pid_cmp        ( pid_cmp ),
                     .pid_out        ( pid_out )
							
						 );
                  
/*---------------------------Read-Write logic----------------------------------------------------*/                        
 
 always @(posedge clk or negedge reset_n)
   if(~reset_n)
     begin
       kp           <= #1 32'h0;
       ki           <= #1 32'h0;
       kd           <= #1 32'h0;
       ref_reg      <= #1 32'h0;
       fdb_reg      <= #1 32'h0;
       read_data    <= #1 32'h0;
     end
     
   else if( Av_write )
       case(address)
         3'b000      : kp         <= #1 write_data ;
         3'b001      : ki         <= #1 write_data ;
         3'b010      : kd         <= #1 write_data ;
         3'b011      : ref_reg    <= #1 write_data ;
         3'b100      : fdb_reg    <= #1 write_data ;
       endcase
       
   else if( Av_read )    
       case(address)
         3'b000      : read_data <= #1 kp ;
         3'b001      : read_data <= #1 ki ;
         3'b010      : read_data <= #1 kd ;
         3'b011      : read_data <= #1 ref_reg ;
         3'b100      : read_data <= #1 fdb_reg ;
         3'b101      : read_data <= #1 pid_en ;
         3'b110      : read_data <= #1 pid_out ;
         3'b111      : read_data <= #1 pid_cmp;
       endcase

 always @(posedge clk or negedge reset_n)
   if(~reset_n)
      pid_en       <= #1 32'h0;
   else if( Av_write && address == 3'b101 )
		pid_en     <= #1 write_data ;
	else
		pid_en <= 0;
		
endmodule
