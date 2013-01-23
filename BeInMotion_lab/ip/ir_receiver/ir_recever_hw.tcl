# TCL File Generated by Component Editor 11.0
# Thu May 26 10:28:18 IST 2011
# DO NOT MODIFY


# +-----------------------------------
# | 
# | ir_receiver "DC Motor Optical Receiver" v1.0
# | System Level Solutions 2011.05.26.10:28:18
# | Optical Receiver for DC Motor
# | 
# | E:/designs/altera/altra-p-bmsob-motcon/trunk/soc/syn/ref_design/sys_q11_qsys_BeInMotion/ip/ir_receiver/ir_recever.v
# | 
# |    ./ir_recever.v syn, sim
# | 
# +-----------------------------------

# +-----------------------------------
# | request TCL package from ACDS 11.0
# | 
package require -exact sopc 11.0
# | 
# +-----------------------------------

# +-----------------------------------
# | module ir_receiver
# | 
set_module_property DESCRIPTION "Optical Receiver for DC Motor"
set_module_property NAME ir_receiver
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property GROUP "SLS/DC Motor"
set_module_property AUTHOR "System Level Solutions"
set_module_property ICON_PATH sls_logo.jpg
set_module_property DISPLAY_NAME "DC Motor Optical Receiver"
set_module_property TOP_LEVEL_HDL_FILE ir_recever.v
set_module_property TOP_LEVEL_HDL_MODULE ir_receiver
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property ANALYZE_HDL AUTO
set_module_property STATIC_TOP_LEVEL_MODULE_NAME ir_receiver
set_module_property FIX_110_VIP_PATH false
# | 
# +-----------------------------------

# +-----------------------------------
# | files
# | 
add_file ir_recever.v {SYNTHESIS SIMULATION}
# | 
# +-----------------------------------

# +-----------------------------------
# | parameters
# | 
# | 
# +-----------------------------------

# +-----------------------------------
# | display items
# | 
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point clock
# | 
add_interface clock clock end
set_interface_property clock clockRate 0

set_interface_property clock ENABLED true

add_interface_port clock clk clk Input 1
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point reset
# | 
add_interface reset reset end
set_interface_property reset associatedClock clock
set_interface_property reset synchronousEdges DEASSERT

set_interface_property reset ENABLED true

add_interface_port reset reset_n reset_n Input 1
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point avalon_slave_0
# | 
add_interface avalon_slave_0 avalon end
set_interface_property avalon_slave_0 addressUnits WORDS
set_interface_property avalon_slave_0 associatedClock clock
set_interface_property avalon_slave_0 associatedReset reset
set_interface_property avalon_slave_0 bitsPerSymbol 8
set_interface_property avalon_slave_0 burstOnBurstBoundariesOnly false
set_interface_property avalon_slave_0 burstcountUnits WORDS
set_interface_property avalon_slave_0 explicitAddressSpan 0
set_interface_property avalon_slave_0 holdTime 0
set_interface_property avalon_slave_0 linewrapBursts false
set_interface_property avalon_slave_0 maximumPendingReadTransactions 0
set_interface_property avalon_slave_0 readLatency 0
set_interface_property avalon_slave_0 readWaitTime 1
set_interface_property avalon_slave_0 setupTime 0
set_interface_property avalon_slave_0 timingUnits Cycles
set_interface_property avalon_slave_0 writeWaitTime 0

set_interface_property avalon_slave_0 ENABLED true

add_interface_port avalon_slave_0 writedata writedata Input 32
add_interface_port avalon_slave_0 address address Input 1
add_interface_port avalon_slave_0 write_n write_n Input 1
add_interface_port avalon_slave_0 read_n read_n Input 1
add_interface_port avalon_slave_0 chipselect chipselect Input 1
add_interface_port avalon_slave_0 readdata readdata Output 32
add_interface_port avalon_slave_0 waitrequest waitrequest Output 1
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point conduit_end
# | 
add_interface conduit_end conduit end

set_interface_property conduit_end ENABLED true

add_interface_port conduit_end in_port export Input 1
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point interrupt_sender
# | 
add_interface interrupt_sender interrupt end
set_interface_property interrupt_sender associatedAddressablePoint avalon_slave_0
set_interface_property interrupt_sender associatedClock clock
set_interface_property interrupt_sender associatedReset reset

set_interface_property interrupt_sender ENABLED true

add_interface_port interrupt_sender irq irq Output 1
# | 
# +-----------------------------------
