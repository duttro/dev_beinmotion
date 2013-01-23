## Generated SDC file "BeInMotion.sdc"

## Copyright (C) 1991-2011 Altera Corporation
## Your use of Altera Corporation's design tools, logic functions 
## and other software and tools, and its AMPP partner logic 
## functions, and any output files from any of the foregoing 
## (including device programming or simulation files), and any 
## associated documentation or information are expressly subject 
## to the terms and conditions of the Altera Program License 
## Subscription Agreement, Altera MegaCore Function License 
## Agreement, or other applicable license agreement, including, 
## without limitation, that your use is for the sole purpose of 
## programming logic devices manufactured by Altera and sold by 
## Altera or its authorized distributors.  Please refer to the 
## applicable agreement for further details.


## VENDOR  "Altera"
## PROGRAM "Quartus II"
## VERSION "Version 11.0 Build 157 04/27/2011 SJ Full Version"

## DATE    "Fri Jul 08 17:16:56 2011"

##
## DEVICE  "EP4CE22F17C7"
##


#**************************************************************
# Time Information
#**************************************************************

set_time_format -unit ns -decimal_places 3



#**************************************************************
# Create Clock
#**************************************************************

create_clock -name {altera_reserved_tck} -period 100.000 -waveform { 0.000 50.000 } [get_ports {altera_reserved_tck}]
create_clock -name {CLK_FPGA_50M} -period 20.000 -waveform { 0.000 10.000 } [get_ports {CLK_FPGA_50M}]

#**************************************************************
# Create Generated Clock
#**************************************************************

create_generated_clock -name {b2v_inst|pll|sd1|pll7|clk[0]} -source [get_pins {b2v_inst|pll|sd1|pll7|inclk[0]}] -duty_cycle 50.000 -multiply_by 1 -divide_by 50 -master_clock {CLK_FPGA_50M} [get_pins {b2v_inst|pll|sd1|pll7|clk[0]}] 
create_generated_clock -name st_clk -source [get_ports {CLK_FPGA_50M}] -divide_by 50000 [get_nets {b2v_inst|stpr_motor_cntrl|st_clk}]

#**************************************************************
# Set Clock Latency
#**************************************************************



#**************************************************************
# Set Clock Uncertainty
#**************************************************************

derive_clock_uncertainty
set_clock_uncertainty -rise_from [get_clocks {altera_reserved_tck}] -rise_to [get_clocks {altera_reserved_tck}]  0.020 
set_clock_uncertainty -rise_from [get_clocks {altera_reserved_tck}] -fall_to [get_clocks {altera_reserved_tck}]  0.020 
set_clock_uncertainty -fall_from [get_clocks {altera_reserved_tck}] -rise_to [get_clocks {altera_reserved_tck}]  0.020 
set_clock_uncertainty -fall_from [get_clocks {altera_reserved_tck}] -fall_to [get_clocks {altera_reserved_tck}]  0.020 
set_clock_uncertainty -rise_from [get_clocks {CLK_FPGA_50M}] -rise_to [get_clocks {CLK_FPGA_50M}]  0.020 
set_clock_uncertainty -rise_from [get_clocks {CLK_FPGA_50M}] -fall_to [get_clocks {CLK_FPGA_50M}]  0.020 
set_clock_uncertainty -rise_from [get_clocks {CLK_FPGA_50M}] -rise_to [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -setup 0.070 
set_clock_uncertainty -rise_from [get_clocks {CLK_FPGA_50M}] -rise_to [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -hold 0.100 
set_clock_uncertainty -rise_from [get_clocks {CLK_FPGA_50M}] -fall_to [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -setup 0.070 
set_clock_uncertainty -rise_from [get_clocks {CLK_FPGA_50M}] -fall_to [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -hold 0.100 
set_clock_uncertainty -fall_from [get_clocks {CLK_FPGA_50M}] -rise_to [get_clocks {CLK_FPGA_50M}]  0.020 
set_clock_uncertainty -fall_from [get_clocks {CLK_FPGA_50M}] -fall_to [get_clocks {CLK_FPGA_50M}]  0.020 
set_clock_uncertainty -fall_from [get_clocks {CLK_FPGA_50M}] -rise_to [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -setup 0.070 
set_clock_uncertainty -fall_from [get_clocks {CLK_FPGA_50M}] -rise_to [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -hold 0.100 
set_clock_uncertainty -fall_from [get_clocks {CLK_FPGA_50M}] -fall_to [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -setup 0.070 
set_clock_uncertainty -fall_from [get_clocks {CLK_FPGA_50M}] -fall_to [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -hold 0.100 
set_clock_uncertainty -rise_from [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -rise_to [get_clocks {CLK_FPGA_50M}] -setup 0.100 
set_clock_uncertainty -rise_from [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -rise_to [get_clocks {CLK_FPGA_50M}] -hold 0.070 
set_clock_uncertainty -rise_from [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -fall_to [get_clocks {CLK_FPGA_50M}] -setup 0.100 
set_clock_uncertainty -rise_from [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -fall_to [get_clocks {CLK_FPGA_50M}] -hold 0.070 
set_clock_uncertainty -rise_from [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -rise_to [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}]  0.020 
set_clock_uncertainty -rise_from [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -fall_to [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}]  0.020 
set_clock_uncertainty -fall_from [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -rise_to [get_clocks {CLK_FPGA_50M}] -setup 0.100 
set_clock_uncertainty -fall_from [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -rise_to [get_clocks {CLK_FPGA_50M}] -hold 0.070 
set_clock_uncertainty -fall_from [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -fall_to [get_clocks {CLK_FPGA_50M}] -setup 0.100 
set_clock_uncertainty -fall_from [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -fall_to [get_clocks {CLK_FPGA_50M}] -hold 0.070 
set_clock_uncertainty -fall_from [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -rise_to [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}]  0.020 
set_clock_uncertainty -fall_from [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}] -fall_to [get_clocks {b2v_inst|pll|sd1|pll7|clk[0]}]  0.020 


#**************************************************************
# Set Input Delay
#**************************************************************



#**************************************************************
# Set Output Delay
#**************************************************************



#**************************************************************
# Set Clock Groups
#**************************************************************

set_clock_groups -asynchronous -group [get_clocks {altera_reserved_tck}] 


#**************************************************************
# Set False Path
#**************************************************************

set_false_path -from [get_registers {*|alt_jtag_atlantic:*|jupdate}] -to [get_registers {*|alt_jtag_atlantic:*|jupdate1*}]
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|rdata[*]}] -to [get_registers {*|alt_jtag_atlantic*|td_shift[*]}]
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|read_req}] 
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|read_write}] -to [get_registers {*|alt_jtag_atlantic:*|read_write1*}]
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|rvalid}] -to [get_registers {*|alt_jtag_atlantic*|td_shift[*]}]
set_false_path -from [get_registers {*|t_dav}] -to [get_registers {*|alt_jtag_atlantic:*|td_shift[0]*}]
set_false_path -from [get_registers {*|t_dav}] -to [get_registers {*|alt_jtag_atlantic:*|write_stalled*}]
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|user_saw_rvalid}] -to [get_registers {*|alt_jtag_atlantic:*|rvalid0*}]
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|wdata[*]}] -to [get_registers *]
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|write_stalled}] -to [get_registers {*|alt_jtag_atlantic:*|t_ena*}]
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|write_stalled}] -to [get_registers {*|alt_jtag_atlantic:*|t_pause*}]
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|write_valid}] 
set_false_path -from [get_registers {*altera_avalon_st_clock_crosser:*|in_data_buffer*}] -to [get_registers {*altera_avalon_st_clock_crosser:*|out_data_buffer*}]
set_false_path -to [get_keepers {*altera_std_synchronizer:*|din_s1}]
set_false_path -from [get_keepers {*BeInMotion_qsys_cpu:*|BeInMotion_qsys_cpu_nios2_oci:the_BeInMotion_qsys_cpu_nios2_oci|BeInMotion_qsys_cpu_nios2_oci_break:the_BeInMotion_qsys_cpu_nios2_oci_break|break_readreg*}] -to [get_keepers {*BeInMotion_qsys_cpu:*|BeInMotion_qsys_cpu_nios2_oci:the_BeInMotion_qsys_cpu_nios2_oci|BeInMotion_qsys_cpu_jtag_debug_module_wrapper:the_BeInMotion_qsys_cpu_jtag_debug_module_wrapper|BeInMotion_qsys_cpu_jtag_debug_module_tck:the_BeInMotion_qsys_cpu_jtag_debug_module_tck|*sr*}]
set_false_path -from [get_keepers {*BeInMotion_qsys_cpu:*|BeInMotion_qsys_cpu_nios2_oci:the_BeInMotion_qsys_cpu_nios2_oci|BeInMotion_qsys_cpu_nios2_oci_debug:the_BeInMotion_qsys_cpu_nios2_oci_debug|*resetlatch}] -to [get_keepers {*BeInMotion_qsys_cpu:*|BeInMotion_qsys_cpu_nios2_oci:the_BeInMotion_qsys_cpu_nios2_oci|BeInMotion_qsys_cpu_jtag_debug_module_wrapper:the_BeInMotion_qsys_cpu_jtag_debug_module_wrapper|BeInMotion_qsys_cpu_jtag_debug_module_tck:the_BeInMotion_qsys_cpu_jtag_debug_module_tck|*sr[33]}]
set_false_path -from [get_keepers {*BeInMotion_qsys_cpu:*|BeInMotion_qsys_cpu_nios2_oci:the_BeInMotion_qsys_cpu_nios2_oci|BeInMotion_qsys_cpu_nios2_oci_debug:the_BeInMotion_qsys_cpu_nios2_oci_debug|monitor_ready}] -to [get_keepers {*BeInMotion_qsys_cpu:*|BeInMotion_qsys_cpu_nios2_oci:the_BeInMotion_qsys_cpu_nios2_oci|BeInMotion_qsys_cpu_jtag_debug_module_wrapper:the_BeInMotion_qsys_cpu_jtag_debug_module_wrapper|BeInMotion_qsys_cpu_jtag_debug_module_tck:the_BeInMotion_qsys_cpu_jtag_debug_module_tck|*sr[0]}]
set_false_path -from [get_keepers {*BeInMotion_qsys_cpu:*|BeInMotion_qsys_cpu_nios2_oci:the_BeInMotion_qsys_cpu_nios2_oci|BeInMotion_qsys_cpu_nios2_oci_debug:the_BeInMotion_qsys_cpu_nios2_oci_debug|monitor_error}] -to [get_keepers {*BeInMotion_qsys_cpu:*|BeInMotion_qsys_cpu_nios2_oci:the_BeInMotion_qsys_cpu_nios2_oci|BeInMotion_qsys_cpu_jtag_debug_module_wrapper:the_BeInMotion_qsys_cpu_jtag_debug_module_wrapper|BeInMotion_qsys_cpu_jtag_debug_module_tck:the_BeInMotion_qsys_cpu_jtag_debug_module_tck|*sr[34]}]
set_false_path -from [get_keepers {*BeInMotion_qsys_cpu:*|BeInMotion_qsys_cpu_nios2_oci:the_BeInMotion_qsys_cpu_nios2_oci|BeInMotion_qsys_cpu_nios2_ocimem:the_BeInMotion_qsys_cpu_nios2_ocimem|*MonDReg*}] -to [get_keepers {*BeInMotion_qsys_cpu:*|BeInMotion_qsys_cpu_nios2_oci:the_BeInMotion_qsys_cpu_nios2_oci|BeInMotion_qsys_cpu_jtag_debug_module_wrapper:the_BeInMotion_qsys_cpu_jtag_debug_module_wrapper|BeInMotion_qsys_cpu_jtag_debug_module_tck:the_BeInMotion_qsys_cpu_jtag_debug_module_tck|*sr*}]
set_false_path -from [get_keepers {*BeInMotion_qsys_cpu:*|BeInMotion_qsys_cpu_nios2_oci:the_BeInMotion_qsys_cpu_nios2_oci|BeInMotion_qsys_cpu_jtag_debug_module_wrapper:the_BeInMotion_qsys_cpu_jtag_debug_module_wrapper|BeInMotion_qsys_cpu_jtag_debug_module_tck:the_BeInMotion_qsys_cpu_jtag_debug_module_tck|*sr*}] -to [get_keepers {*BeInMotion_qsys_cpu:*|BeInMotion_qsys_cpu_nios2_oci:the_BeInMotion_qsys_cpu_nios2_oci|BeInMotion_qsys_cpu_jtag_debug_module_wrapper:the_BeInMotion_qsys_cpu_jtag_debug_module_wrapper|BeInMotion_qsys_cpu_jtag_debug_module_sysclk:the_BeInMotion_qsys_cpu_jtag_debug_module_sysclk|*jdo*}]
set_false_path -from [get_keepers {sld_hub:*|irf_reg*}] -to [get_keepers {*BeInMotion_qsys_cpu:*|BeInMotion_qsys_cpu_nios2_oci:the_BeInMotion_qsys_cpu_nios2_oci|BeInMotion_qsys_cpu_jtag_debug_module_wrapper:the_BeInMotion_qsys_cpu_jtag_debug_module_wrapper|BeInMotion_qsys_cpu_jtag_debug_module_sysclk:the_BeInMotion_qsys_cpu_jtag_debug_module_sysclk|ir*}]
set_false_path -from [get_keepers {sld_hub:*|sld_shadow_jsm:shadow_jsm|state[1]}] -to [get_keepers {*BeInMotion_qsys_cpu:*|BeInMotion_qsys_cpu_nios2_oci:the_BeInMotion_qsys_cpu_nios2_oci|BeInMotion_qsys_cpu_nios2_oci_debug:the_BeInMotion_qsys_cpu_nios2_oci_debug|monitor_go}]
set_false_path -to [get_pins -nocase -compatibility_mode {*|alt_rst_sync_uq1|altera_reset_synchronizer_int_chain*|clrn}]


#**************************************************************
# Set Multicycle Path
#**************************************************************



#**************************************************************
# Set Maximum Delay
#**************************************************************



#**************************************************************
# Set Minimum Delay
#**************************************************************



#**************************************************************
# Set Input Transition
#**************************************************************

