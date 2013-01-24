// Copyright (C) 1991-2011 Altera Corporation
// Your use of Altera Corporation's design tools, logic functions 
// and other software and tools, and its AMPP partner logic 
// functions, and any output files from any of the foregoing 
// (including device programming or simulation files), and any 
// associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License 
// Subscription Agreement, Altera MegaCore Function License 
// Agreement, or other applicable license agreement, including, 
// without limitation, that your use is for the sole purpose of 
// programming logic devices manufactured by Altera and sold by 
// Altera or its authorized distributors.  Please refer to the 
// applicable agreement for further details.

// PROGRAM		"Quartus II"
// VERSION		"Version 11.0 Build 157 04/27/2011 SJ Full Version"
// CREATED		"Fri Jun 03 16:21:47 2011"

module BeInMotion(
	CPU_RST_N,
	ir_rx1,
	ir_rx2,
	ps_dout,
	CLK_FPGA_50M,
	data_0,
	stm_sdo,
	pb,
	sdo,
	ir_led2,
	ir_led1,
	ps_led_on,
	dc_psave,
	sce,
	dclk,
	stm_sdi,
	stm_sck,
	stm_cnv,
	lcd_reset_n,
	lcd_wr_n,
	lcd_cs_n,
	lcd_rs,
	lcd_rd_n,
	ps_enb,
	gauge_sda,
	gauge_scl,
	ps_sda,
	ps_scl,
	gauge_cc_al_n,
	dc_pwm,
	gpio,
	lcd_d,
	user_led,
	stm_out,
	uart_0_rxd,
   uart_0_txd,
   uart_0_cts_n,
   uart_0_rts_n
);


input wire	CPU_RST_N;
input wire	ir_rx1;
input wire	ir_rx2;
input wire	ps_dout;
input wire	CLK_FPGA_50M;
input wire	data_0;
input wire	stm_sdo;
input wire	[6:0] pb;
output wire	sdo;
output wire	ir_led2;
output wire	ir_led1;
output wire	ps_led_on;
output wire	dc_psave;
output wire	sce;
output wire	dclk;
output wire	stm_sdi;
output wire	stm_sck;
output wire	stm_cnv;
output wire	lcd_reset_n;
output wire	lcd_wr_n;
output wire	lcd_cs_n;
output wire	lcd_rs;
output wire	lcd_rd_n;
output wire	ps_enb;
inout wire	gauge_sda;
inout wire	gauge_scl;
inout wire	ps_sda;
inout wire	ps_scl;
inout wire	gauge_cc_al_n;
output wire	[3:0] dc_pwm;
inout wire	[7:0] gpio;
inout wire	[7:0] lcd_d;
output wire	[2:0] user_led;
output wire [3:0] stm_out;

// added ports for new uart
input  wire       uart_0_rxd;   // uart_0_external_connection.rxd
output wire       uart_0_txd;   //                           .txd
input  wire       uart_0_cts_n; //                           .cts_n
output wire       uart_0_rts_n; //                           .rts_n

wire	[15:0] cnt;
wire	dc1_pwm1;
wire	dc1_pwm2;
wire	dc2_pwm1;
wire	dc2_pwm2;
wire	gauge_scl_in;
wire	gauge_scl_oe;
wire	gauge_scl_out;
wire	gauge_sda_in;
wire	gauge_sda_oe;
wire	gauge_sda_out;
wire	osc_clk;
wire	pll_locked;
wire	ps_scl_in;
wire	ps_scl_oe;
wire	ps_scl_out;
wire	ps_sda_in;
wire	ps_sda_oe;
wire	ps_sda_out;
wire	rd_n;
wire	[7:0] rdd;
wire	sys_reset_n;
wire	SYNTHESIZED_WIRE_0;
wire	SYNTHESIZED_WIRE_1;
wire	SYNTHESIZED_WIRE_2;
wire	SYNTHESIZED_WIRE_3;
wire	SYNTHESIZED_WIRE_4;
wire	SYNTHESIZED_WIRE_5;
wire	SYNTHESIZED_WIRE_6;
wire	[7:0] SYNTHESIZED_WIRE_7;
wire	SYNTHESIZED_WIRE_8;
wire    [3:0] stm_out1;

assign	dc_psave = 0;

BeInMotion_qsys	b2v_inst(
   // Clock & Reset
	.clk_clk				         ( osc_clk		),
	.reset_reset_n				   ( sys_reset_n		),
	.pll_locked_export			( pll_locked		),
	
 	 // DC Motor-1 Interface
 	.ir_rx1_conduit_end_export	( ir_rx1		),
 	.ir_led1_export				( ir_led1		),
 	
 	.dc1_pwm2_export			   ( dc1_pwm2		),
 	.dc1_pwm1_1_export			( dc1_pwm1		),
 	 
 	 
 	 // DC Motor-2 Interface
        .ir_led2_export			( ir_led2		),
 	.ir_rx2_conduit_end_export	( ir_rx2		),
 	.dc2_pwm1_export			   ( dc2_pwm1		),
	.dc2_pwm2_export			   ( dc2_pwm2		),
 	 
 	 
 	 // Stepper Motor Interface 	 
	.st_current_sensor_MISO			( stm_sdo		),
	.st_current_sensor_MOSI			( stm_sdi		),
	.st_current_sensor_SCLK			( stm_sck		),
	.st_current_sensor_SS_n			( stm_cnv		),
	
	 //Battery Gas Guage Interface
	.bat_gas_gauge_sda_padoen_o	( gauge_sda_oe		),
	.bat_gas_gauge_scl_pad_o		( gauge_scl_out		),
	.bat_gas_gauge_scl_padoen_o	( gauge_scl_oe		),
	.bat_gas_gauge_sda_pad_o		( gauge_sda_out		),
	.bat_cc_al_n_export			   ( gauge_cc_al_n		),
	.bat_gas_gauge_scl_pad_i		( gauge_scl_in		),
	.bat_gas_gauge_sda_pad_i		( gauge_sda_in		),	
	
         // Proximity Sensor Interface         
	.ps_din_export				      ( ps_dout		),
	.proximity_ir_sda_pad_i			( ps_sda_in		),
	.proximity_ir_scl_pad_i			( ps_scl_in		),	
        .ps_en_export				( ps_enb		),	
	.proximity_ir_scl_padoen_o		( ps_scl_oe		),
	.proximity_ir_scl_pad_o			( ps_scl_out		),
	.proximity_ir_sda_padoen_o		( ps_sda_oe		),
	.proximity_ir_sda_pad_o			( ps_sda_out		),	
	
	 //EPCS Interface
	 
	.epcs_data0				( data_0		),
	.epcs_sce				( sce			),
	.epcs_sdo				( sdo			),
	.epcs_dclk				( dclk			),	
	 
         // LCD Interface
	.lcd_intf_readdata			( rdd			),
	.lcd_intf_write_n			   ( SYNTHESIZED_WIRE_6	),
	.lcd_intf_address			   ( lcd_rs		),
	.lcd_intf_read_n			   ( SYNTHESIZED_WIRE_5	),
	.lcd_intf_chipselect_n		( SYNTHESIZED_WIRE_8	),	
	.lcd_intf_writedata			( SYNTHESIZED_WIRE_7	),	
	
	//Avalon Stepper motor interface
	.stpr_motor_export         ( stm_out) ,
	

	// Push Button
	.pb_export				      ( pb 			),
	
	// User I/O
	.user_io_export				( gpio 			),
	
   // User LED           
	.user_led_export			   ( user_led 		),
	
	// uart0
   .uart_0_external_connection_rxd   ( uart_0_rxd ),
   .uart_0_external_connection_txd   ( uart_0_txd ),
	.uart_0_external_connection_cts_n ( uart_0_cts_n ),
   .uart_0_external_connection_rts_n ( uart_0_rts_n )	
);


Reset_Delay	b2v_inst21(
	.iRST					( SYNTHESIZED_WIRE_4	),
	.iCLK					( osc_clk		),
	.oRESET				( sys_reset_n		)
);


lpm_counter0	b2v_inst1(
	.clock					( osc_clk		),
	.q					      ( cnt			)
);

assign  gauge_scl_in = gauge_scl;

assign  gauge_sda_in = gauge_sda;

assign	SYNTHESIZED_WIRE_1 =  ~gauge_sda_oe;

assign	SYNTHESIZED_WIRE_0 =  ~gauge_scl_oe;

assign  gauge_scl = SYNTHESIZED_WIRE_0 ? gauge_scl_out : 1'bz;
assign  gauge_sda = SYNTHESIZED_WIRE_1 ? gauge_sda_out : 1'bz;

assign  ps_scl_in = ps_scl;
assign  ps_sda_in = ps_sda;

assign	SYNTHESIZED_WIRE_3 =  ~ps_sda_oe;

assign	SYNTHESIZED_WIRE_2 =  ~ps_scl_oe;
assign  ps_scl = SYNTHESIZED_WIRE_2 ? ps_scl_out : 1'bz;
assign  ps_sda = SYNTHESIZED_WIRE_3 ? ps_sda_out : 1'bz;


assign	SYNTHESIZED_WIRE_4 = pll_locked & CPU_RST_N;

assign	rd_n =  ~SYNTHESIZED_WIRE_5;

assign	lcd_wr_n =  ~SYNTHESIZED_WIRE_6;

assign	lcd_cs_n =  ~SYNTHESIZED_WIRE_8;

assign	osc_clk = CLK_FPGA_50M;

assign   rdd   = lcd_d;
assign	lcd_d = rd_n  ?   SYNTHESIZED_WIRE_7  : 8'hzz ;


assign	ps_led_on = cnt[15];
assign	lcd_reset_n = sys_reset_n;
assign	lcd_rd_n = rd_n;
assign	dc_pwm[3] = dc2_pwm2;
assign	dc_pwm[2] = dc2_pwm1;
assign	dc_pwm[1] = dc1_pwm2;
assign	dc_pwm[0] = dc1_pwm1;

endmodule
