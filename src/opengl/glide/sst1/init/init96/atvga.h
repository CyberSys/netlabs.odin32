/* 
 * THIS SOFTWARE IS SUBJECT TO COPYRIGHT PROTECTION AND IS OFFERED ONLY
 * PURSUANT TO THE 3DFX GLIDE GENERAL PUBLIC LICENSE. THERE IS NO RIGHT
 * TO USE THE GLIDE TRADEMARK WITHOUT PRIOR WRITTEN PERMISSION OF 3DFX
 * INTERACTIVE, INC. A COPY OF THIS LICENSE MAY BE OBTAINED FROM THE 
 * DISTRIBUTOR OR BY CONTACTING 3DFX INTERACTIVE INC(info@3dfx.com). 
 * THIS PROGRAM IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER 
 * EXPRESSED OR IMPLIED. SEE THE 3DFX GLIDE GENERAL PUBLIC LICENSE FOR A
 * FULL TEXT OF THE NON-WARRANTY PROVISIONS.  
 * 
 * USE, DUPLICATION OR DISCLOSURE BY THE GOVERNMENT IS SUBJECT TO
 * RESTRICTIONS AS SET FORTH IN SUBDIVISION (C)(1)(II) OF THE RIGHTS IN
 * TECHNICAL DATA AND COMPUTER SOFTWARE CLAUSE AT DFARS 252.227-7013,
 * AND/OR IN SIMILAR OR SUCCESSOR CLAUSES IN THE FAR, DOD OR NASA FAR
 * SUPPLEMENT. UNPUBLISHED RIGHTS RESERVED UNDER THE COPYRIGHT LAWS OF
 * THE UNITED STATES.  
 * 
 * COPYRIGHT 3DFX INTERACTIVE, INC. 1999, ALL RIGHTS RESERVED
 */


#ifndef __ATVGA_H__
#define __ATVGA_H__

/*
** $Revision: 1.1 $ 
** $Date: 2000-02-25 00:31:27 $ 
**
*/

#define VGA_REGISTER_INPUT_STATUS_1_MONO                    0x3BA
#define VGA_REGISTER_INPUT_STATUS_1_COLOR                   0x3DA
#define VR_IS1_DISPLAY_INACTIVE                             (1 << 0)
#define VR_IS1_DISPLAY_VRETRACE                             (1 << 3)

#define VGA_REGISTER_SEQUENCER                              0x3C4
#define AR_SEQ_REMAP_CONTROL                                        0x1B    /* 6 */
#define AR_SEQ_FLAT_MODEL_CONTROL                                   0x1C    /* 6 */
#define AR_SEQ_ALTERNATE_ACCESS_POINTER                     0x1D    /* 8 */
#define AR_SEQ_ALTERNATE_ACCESS_DECODE_LO_INDEX             0x1E    /* 8 */
#define AR_SEQ_ALTERNATE_ACCESS_DECODE_HI_INDEX             0x1F    /* 8 */


#define MMEXT_REGISTER_WINDOW0_CONTROL                      0x082
#define MMEXT_REGISTER_WINDOW0_BASE_ADDRESS                 0x084
#define MMEXT_REGISTER_WINDOW0_STRETCH_FACTOR_HORIZONTAL_1  0x086
#define MMEXT_REGISTER_WINDOW0_STRETCH_FACTOR_HORIZONTAL_2  0x088
#define MMEXT_REGISTER_WINDOW0_STRETCH_FACTOR_VERTICAL_1    0x08A
#define MMEXT_REGISTER_WINDOW0_STRETCH_FACTOR_VERTICAL_2    0x08C
#define MMEXT_REGISTER_WINDOW_SEQUENCE_CONTROL              0x08E

#define MMEXT_REGISTER_DISPLAY_MEMORY_CONFIGURATION         0x0C4   /* 12 */

#define MMEXT_REGISTER_PIXEL_FIFO_REQUEST_POINT             0xD4    /* 24 */
#define MMEXT_REGISTER_ENABLE_EXTENDED_REGISTERS            0x0DB   /* 4 */
#define AR_ENABLE_DOS_SPACE                                 0x01
#define AR_ENABLE_LINEAR_SPACE                              0x02
#define AR_ENABLE_COPROCESSOR_APERTURE                      0x04
#define AR_ENABLE_SECOND_LINEAR_APERTURE                    0x08

#define MMEXT_REGISTER_MCLK_CONTROL                         0x0E8   /* 8 */
#define MMEXT_REGISTER_MCLK_DENOMINATOR                     0x0E9   /* 8 */
#define MMEXT_REGISTER_MCLK_NUMERATOR                       0x0EA   /* 8 */

#define MMEXT_REGISTER_SERIAL_INPUT                         0x1F4   /* 16 */

#define MMEXT_REGISTER_TILE                                 0x200
#define TILE_REGISTER_CONTROL                               0x00
#define TILE_REGISTER_DISPLAY_POSITION_LEFT                 0x02
#define TILE_REGISTER_DISPLAY_POSITION_RIGHT                0x04
#define TILE_REGISTER_DISPLAY_POSITION_BOTTOM               0x06
#define TILE_REGISTER_DATA_WIDTH                            0x08
#define TILE_REGISTER_DATA_BASE_LOCATION_LO                 0x0A
#define TILE_REGISTER_DATA_BASE_LOCATION_HI                 0x0C

#define VGA_CRTC_INDEX                          0x3D4
#define VGA_CRTC_DATA                           0x3D5
#define VCRTC_SERIAL_START_ADDRESS_HI           0x0C
#define VCRTC_SERIAL_START_ADDRESS_LO           0x0D
#define ATCRTC_SERIAL_OVERFLOW                  0x1C
#define VGA_INPUT_STATUS_1C                     0x3DA
#define VIS1C_PIXEL_DISPLAY_INACTIVE            BIT(0)
#define VIS1C_VERTICAL_RETRACE_ACTIVE           BIT(3)

#endif

