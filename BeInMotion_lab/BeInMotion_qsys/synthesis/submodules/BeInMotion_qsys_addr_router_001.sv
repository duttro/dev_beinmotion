// (C) 2001-2011 Altera Corporation. All rights reserved.
// Your use of Altera Corporation's design tools, logic functions and other 
// software and tools, and its AMPP partner logic functions, and any output 
// files any of the foregoing (including device programming or simulation 
// files), and any associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License Subscription 
// Agreement, Altera MegaCore Function License Agreement, or other applicable 
// license agreement, including, without limitation, that your use is for the 
// sole purpose of programming logic devices manufactured by Altera and sold by 
// Altera or its authorized distributors.  Please refer to the applicable 
// agreement for further details.


// $Id: //acds/rel/11.1sp1/ip/merlin/altera_merlin_router/altera_merlin_router.sv.terp#1 $
// $Revision: #1 $
// $Date: 2011/09/26 $
// $Author: max $

// -------------------------------------------------------
// Merlin Router
//
// Asserts the appropriate one-hot encoded channel based on 
// either (a) the address or (b) the dest id. The DECODER_TYPE
// parameter controls this behaviour. 0 means address decoder,
// 1 means dest id decoder.
//
// In the case of (a), it also sets the destination id.
// -------------------------------------------------------

`timescale 1 ns / 1 ns

module BeInMotion_qsys_addr_router_001_default_decode
  #(
     parameter DEFAULT_CHANNEL = 1,
               DEFAULT_DESTID = 1 
   )
  (output [75 - 71 : 0] default_destination_id,
   output [30-1 : 0] default_src_channel
  );

  assign default_destination_id = 
    DEFAULT_DESTID[75 - 71 : 0];
  generate begin : default_decode
    if (DEFAULT_CHANNEL == -1)
      assign default_src_channel = '0;
    else
      assign default_src_channel = 30'b1 << DEFAULT_CHANNEL;
  end endgenerate

endmodule


module BeInMotion_qsys_addr_router_001
(
    // -------------------
    // Clock & Reset
    // -------------------
    input clk,
    input reset,

    // -------------------
    // Command Sink (Input)
    // -------------------
    input                       sink_valid,
    input  [77-1 : 0]    sink_data,
    input                       sink_startofpacket,
    input                       sink_endofpacket,
    output                      sink_ready,

    // -------------------
    // Command Source (Output)
    // -------------------
    output                          src_valid,
    output reg [77-1    : 0] src_data,
    output reg [30-1 : 0] src_channel,
    output                          src_startofpacket,
    output                          src_endofpacket,
    input                           src_ready
);

    // -------------------------------------------------------
    // Local parameters and variables
    // -------------------------------------------------------
    localparam PKT_ADDR_H = 53;
    localparam PKT_ADDR_L = 36;
    localparam PKT_DEST_ID_H = 75;
    localparam PKT_DEST_ID_L = 71;
    localparam ST_DATA_W = 77;
    localparam ST_CHANNEL_W = 30;
    localparam DECODER_TYPE = 0;

    localparam PKT_TRANS_WRITE = 56;
    localparam PKT_TRANS_READ  = 57;

    localparam PKT_ADDR_W = PKT_ADDR_H-PKT_ADDR_L + 1;
    localparam PKT_DEST_ID_W = PKT_DEST_ID_H-PKT_DEST_ID_L + 1;




    // -------------------------------------------------------
    // Figure out the number of bits to mask off for each slave span
    // during address decoding
    // -------------------------------------------------------
    localparam PAD0 = log2ceil(32'h20 - 32'h0);
    localparam PAD1 = log2ceil(32'h40 - 32'h20);
    localparam PAD2 = log2ceil(32'h60 - 32'h40);
    localparam PAD3 = log2ceil(32'h80 - 32'h60);
    localparam PAD4 = log2ceil(32'h88 - 32'h80);
    localparam PAD5 = log2ceil(32'h20000 - 32'h10000);
    localparam PAD6 = log2ceil(32'h21800 - 32'h21000);
    localparam PAD7 = log2ceil(32'h22000 - 32'h21800);
    localparam PAD8 = log2ceil(32'h22020 - 32'h22000);
    localparam PAD9 = log2ceil(32'h22040 - 32'h22020);
    localparam PAD10 = log2ceil(32'h22060 - 32'h22040);
    localparam PAD11 = log2ceil(32'h22080 - 32'h22060);
    localparam PAD12 = log2ceil(32'h22090 - 32'h22080);
    localparam PAD13 = log2ceil(32'h220a0 - 32'h22090);
    localparam PAD14 = log2ceil(32'h220b0 - 32'h220a0);
    localparam PAD15 = log2ceil(32'h220c0 - 32'h220b0);
    localparam PAD16 = log2ceil(32'h220d0 - 32'h220c0);
    localparam PAD17 = log2ceil(32'h220e0 - 32'h220d0);
    localparam PAD18 = log2ceil(32'h220f0 - 32'h220e0);
    localparam PAD19 = log2ceil(32'h22100 - 32'h220f0);
    localparam PAD20 = log2ceil(32'h22110 - 32'h22100);
    localparam PAD21 = log2ceil(32'h22120 - 32'h22110);
    localparam PAD22 = log2ceil(32'h22130 - 32'h22120);
    localparam PAD23 = log2ceil(32'h22140 - 32'h22130);
    localparam PAD24 = log2ceil(32'h22150 - 32'h22140);
    localparam PAD25 = log2ceil(32'h22160 - 32'h22150);
    localparam PAD26 = log2ceil(32'h22168 - 32'h22160);
    localparam PAD27 = log2ceil(32'h22170 - 32'h22168);
    localparam PAD28 = log2ceil(32'h22178 - 32'h22170);
    localparam PAD29 = log2ceil(32'h22180 - 32'h22178);

    // -------------------------------------------------------
    // Work out which address bits are significant based on the
    // address range of the slaves. If the required width is too
    // large or too small, we use the address field width instead.
    // -------------------------------------------------------
    localparam ADDR_RANGE = 32'h22180;
    localparam RANGE_ADDR_WIDTH = log2ceil(ADDR_RANGE);
    localparam OPTIMIZED_ADDR_H = (RANGE_ADDR_WIDTH > PKT_ADDR_W) ||
                                  (RANGE_ADDR_WIDTH == 0) ?
                                        PKT_ADDR_H :
                                        PKT_ADDR_L + RANGE_ADDR_WIDTH - 1;
    localparam RG = RANGE_ADDR_WIDTH-1;

      wire [PKT_ADDR_W-1 : 0] address = sink_data[OPTIMIZED_ADDR_H : PKT_ADDR_L];

    // -------------------------------------------------------
    // Pass almost everything through, untouched
    // -------------------------------------------------------
    assign sink_ready        = src_ready;
    assign src_valid         = sink_valid;
    assign src_startofpacket = sink_startofpacket;
    assign src_endofpacket   = sink_endofpacket;

    wire [PKT_DEST_ID_W-1:0] default_destid;
    wire [30-1 : 0] default_src_channel;




    BeInMotion_qsys_addr_router_001_default_decode the_default_decode(
      .default_destination_id (default_destid),
      .default_src_channel (default_src_channel)
    );

    always @* begin
        src_data    = sink_data;
        src_channel = default_src_channel;

        src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = default_destid;
        // --------------------------------------------------
        // Address Decoder
        // Sets the channel and destination ID based on the address
        // --------------------------------------------------

        // ( 0x0 .. 0x20 )
        if ( {address[RG:PAD0],{PAD0{1'b0}}} == 'h0 ) begin
            src_channel = 30'b000010000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 25;
        end

        // ( 0x20 .. 0x40 )
        if ( {address[RG:PAD1],{PAD1{1'b0}}} == 'h20 ) begin
            src_channel = 30'b000100000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 26;
        end

        // ( 0x40 .. 0x60 )
        if ( {address[RG:PAD2],{PAD2{1'b0}}} == 'h40 ) begin
            src_channel = 30'b010000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 28;
        end

        // ( 0x60 .. 0x80 )
        if ( {address[RG:PAD3],{PAD3{1'b0}}} == 'h60 ) begin
            src_channel = 30'b100000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 29;
        end

        // ( 0x80 .. 0x88 )
        if ( {address[RG:PAD4],{PAD4{1'b0}}} == 'h80 ) begin
            src_channel = 30'b001000000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 27;
        end

        // ( 0x10000 .. 0x20000 )
        if ( {address[RG:PAD5],{PAD5{1'b0}}} == 'h10000 ) begin
            src_channel = 30'b000000000000000000000000000010;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 1;
        end

        // ( 0x21000 .. 0x21800 )
        if ( {address[RG:PAD6],{PAD6{1'b0}}} == 'h21000 ) begin
            src_channel = 30'b000000000000000000000000000001;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 0;
        end

        // ( 0x21800 .. 0x22000 )
        if ( {address[RG:PAD7],{PAD7{1'b0}}} == 'h21800 ) begin
            src_channel = 30'b000000000000000000000000000100;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 2;
        end

        // ( 0x22000 .. 0x22020 )
        if ( {address[RG:PAD8],{PAD8{1'b0}}} == 'h22000 ) begin
            src_channel = 30'b000000000000000000000000010000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 4;
        end

        // ( 0x22020 .. 0x22040 )
        if ( {address[RG:PAD9],{PAD9{1'b0}}} == 'h22020 ) begin
            src_channel = 30'b000000000000000000100000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 11;
        end

        // ( 0x22040 .. 0x22060 )
        if ( {address[RG:PAD10],{PAD10{1'b0}}} == 'h22040 ) begin
            src_channel = 30'b000000010000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 22;
        end

        // ( 0x22060 .. 0x22080 )
        if ( {address[RG:PAD11],{PAD11{1'b0}}} == 'h22060 ) begin
            src_channel = 30'b000000100000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 23;
        end

        // ( 0x22080 .. 0x22090 )
        if ( {address[RG:PAD12],{PAD12{1'b0}}} == 'h22080 ) begin
            src_channel = 30'b000000000000000000000000100000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 5;
        end

        // ( 0x22090 .. 0x220a0 )
        if ( {address[RG:PAD13],{PAD13{1'b0}}} == 'h22090 ) begin
            src_channel = 30'b000000000000000000000001000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 6;
        end

        // ( 0x220a0 .. 0x220b0 )
        if ( {address[RG:PAD14],{PAD14{1'b0}}} == 'h220a0 ) begin
            src_channel = 30'b000000000000000000000010000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 7;
        end

        // ( 0x220b0 .. 0x220c0 )
        if ( {address[RG:PAD15],{PAD15{1'b0}}} == 'h220b0 ) begin
            src_channel = 30'b000000000000000000000100000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 8;
        end

        // ( 0x220c0 .. 0x220d0 )
        if ( {address[RG:PAD16],{PAD16{1'b0}}} == 'h220c0 ) begin
            src_channel = 30'b000000000000000000001000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 9;
        end

        // ( 0x220d0 .. 0x220e0 )
        if ( {address[RG:PAD17],{PAD17{1'b0}}} == 'h220d0 ) begin
            src_channel = 30'b000000000000000000010000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 10;
        end

        // ( 0x220e0 .. 0x220f0 )
        if ( {address[RG:PAD18],{PAD18{1'b0}}} == 'h220e0 ) begin
            src_channel = 30'b000000000000000001000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 12;
        end

        // ( 0x220f0 .. 0x22100 )
        if ( {address[RG:PAD19],{PAD19{1'b0}}} == 'h220f0 ) begin
            src_channel = 30'b000000000000000010000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 13;
        end

        // ( 0x22100 .. 0x22110 )
        if ( {address[RG:PAD20],{PAD20{1'b0}}} == 'h22100 ) begin
            src_channel = 30'b000000000000000100000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 14;
        end

        // ( 0x22110 .. 0x22120 )
        if ( {address[RG:PAD21],{PAD21{1'b0}}} == 'h22110 ) begin
            src_channel = 30'b000000000000001000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 15;
        end

        // ( 0x22120 .. 0x22130 )
        if ( {address[RG:PAD22],{PAD22{1'b0}}} == 'h22120 ) begin
            src_channel = 30'b000000000001000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 18;
        end

        // ( 0x22130 .. 0x22140 )
        if ( {address[RG:PAD23],{PAD23{1'b0}}} == 'h22130 ) begin
            src_channel = 30'b000000000010000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 19;
        end

        // ( 0x22140 .. 0x22150 )
        if ( {address[RG:PAD24],{PAD24{1'b0}}} == 'h22140 ) begin
            src_channel = 30'b000000000100000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 20;
        end

        // ( 0x22150 .. 0x22160 )
        if ( {address[RG:PAD25],{PAD25{1'b0}}} == 'h22150 ) begin
            src_channel = 30'b000000001000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 21;
        end

        // ( 0x22160 .. 0x22168 )
        if ( {address[RG:PAD26],{PAD26{1'b0}}} == 'h22160 ) begin
            src_channel = 30'b000000000000000000000000001000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 3;
        end

        // ( 0x22168 .. 0x22170 )
        if ( {address[RG:PAD27],{PAD27{1'b0}}} == 'h22168 ) begin
            src_channel = 30'b000000000000010000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 16;
        end

        // ( 0x22170 .. 0x22178 )
        if ( {address[RG:PAD28],{PAD28{1'b0}}} == 'h22170 ) begin
            src_channel = 30'b000000000000100000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 17;
        end

        // ( 0x22178 .. 0x22180 )
        if ( {address[RG:PAD29],{PAD29{1'b0}}} == 'h22178 ) begin
            src_channel = 30'b000001000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 24;
        end
    end

    // --------------------------------------------------
    // Ceil(log2()) function
    // --------------------------------------------------
    function integer log2ceil;
        input reg[63:0] val;
        reg [63:0] i;

        begin
            i = 1;
            log2ceil = 0;

            while (i < val) begin
                log2ceil = log2ceil + 1;
                i = i << 1;
            end
        end
    endfunction

endmodule


