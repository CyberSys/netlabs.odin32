/*
** THIS SOFTWARE IS SUBJECT TO COPYRIGHT PROTECTION AND IS OFFERED ONLY
** PURSUANT TO THE 3DFX GLIDE GENERAL PUBLIC LICENSE. THERE IS NO RIGHT
** TO USE THE GLIDE TRADEMARK WITHOUT PRIOR WRITTEN PERMISSION OF 3DFX
** INTERACTIVE, INC. A COPY OF THIS LICENSE MAY BE OBTAINED FROM THE 
** DISTRIBUTOR OR BY CONTACTING 3DFX INTERACTIVE INC(info@3dfx.com). 
** THIS PROGRAM IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER 
** EXPRESSED OR IMPLIED. SEE THE 3DFX GLIDE GENERAL PUBLIC LICENSE FOR A
** FULL TEXT OF THE NON-WARRANTY PROVISIONS.  
** 
** USE, DUPLICATION OR DISCLOSURE BY THE GOVERNMENT IS SUBJECT TO
** RESTRICTIONS AS SET FORTH IN SUBDIVISION (C)(1)(II) OF THE RIGHTS IN
** TECHNICAL DATA AND COMPUTER SOFTWARE CLAUSE AT DFARS 252.227-7013,
** AND/OR IN SIMILAR OR SUCCESSOR CLAUSES IN THE FAR, DOD OR NASA FAR
** SUPPLEMENT. UNPUBLISHED RIGHTS RESERVED UNDER THE COPYRIGHT LAWS OF
** THE UNITED STATES.  
** 
** COPYRIGHT 3DFX INTERACTIVE, INC. 1999, ALL RIGHTS RESERVED
**
**
** $Revision: 1.1 $ 
** $Date: 2000-02-25 00:33:58 $ 
**
*/

#include <3dfx.h>
#include <fxpci.h>
#include "sst1_pci.h"

const PciRegister SST1_PCI_INIT_ENABLE = { 0x40, 4, READ_WRITE }; 
const PciRegister SST1_PCI_BUS_SNOOP_0 = { 0x44, 4, WRITE_ONLY }; 
const PciRegister SST1_PCI_BUS_SNOOP_1 = { 0x48, 4, WRITE_ONLY }; 
const PciRegister SST1_PCI_CFG_STATUS  = { 0x4C, 4, READ_WRITE }; 

const PciRegister SST1_PCI_VCLK_ENABLE = { 0xc0, 4, WRITE_ONLY };
const PciRegister SST1_PCI_VCLK_DISABLE= { 0xe0, 4, WRITE_ONLY };

