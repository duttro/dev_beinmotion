# Download the sof in preparation for the nios2-flash-programmer
#
nios2-configure-sof '--cable=USB-Blaster on localhost [USB-0]'


# Programming File: "BeInMotion_epcs.flash" To Device: epcs
#
nios2-flash-programmer "BeInMotion_epcs.flash" --base=0x21800 --epcs --sidp=0x60 --id=0x0 --timestamp=1312222159 --device=1 --instance=0 '--cable=USB-Blaster on localhost [USB-0]' --program --verbose 


# Programming File: "DC_Motor_Synchronization_epcs.flash" To Device: epcs
#
nios2-flash-programmer "DC_Motor_Synchronization_epcs.flash" --base=0x21800 --epcs --sidp=0x60 --id=0x0 --timestamp=1312222159 --device=1 --instance=0 '--cable=USB-Blaster on localhost [USB-0]' --program --verbose 

