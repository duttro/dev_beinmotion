#!/bin/sh
#
# This file was automatically generated.
#
# It can be overwritten by nios2-flash-programmer-generate or nios2-flash-programmer-gui.
#

#
# Converting SOF File: C:\dev_beinmotion\BeInMotion_lab\BeInMotion.sof to: "..\flash/BeInMotion_epcs.flash"
#
$SOPC_KIT_NIOS2/bin/sof2flash --input="C:/dev_beinmotion/BeInMotion_lab/BeInMotion.sof" --output="../flash/BeInMotion_epcs.flash" --epcs 

#
# Programming File: "..\flash/BeInMotion_epcs.flash" To Device: epcs
#
$SOPC_KIT_NIOS2/bin/nios2-flash-programmer "../flash/BeInMotion_epcs.flash" --base=0x21800 --epcs --sidp=0x80 --id=0x0 --accept-bad-sysid --device=1 --instance=0 '--cable=USB-Blaster on localhost [USB-0]' --program 

#
# Converting ELF File: C:\dev_beinmotion\BeInMotion_lab\software\DC_Motor_Synchronization\DC_Motor_Synchronization.elf to: "..\flash/DC_Motor_Synchronization_epcs.flash"
#
$SOPC_KIT_NIOS2/bin/elf2flash --input="C:/dev_beinmotion/BeInMotion_lab/software/DC_Motor_Synchronization/DC_Motor_Synchronization.elf" --output="../flash/DC_Motor_Synchronization_epcs.flash" --epcs --after="../flash/BeInMotion_epcs.flash" 

#
# Programming File: "..\flash/DC_Motor_Synchronization_epcs.flash" To Device: epcs
#
$SOPC_KIT_NIOS2/bin/nios2-flash-programmer "../flash/DC_Motor_Synchronization_epcs.flash" --base=0x21800 --epcs --sidp=0x80 --id=0x0 --accept-bad-sysid --device=1 --instance=0 '--cable=USB-Blaster on localhost [USB-0]' --program 

