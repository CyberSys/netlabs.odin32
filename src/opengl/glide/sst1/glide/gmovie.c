/* $Id: gmovie.c,v 1.2 2001-09-05 14:30:53 bird Exp $ */
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
** $Header: /home/ktk/tmp/odin/2007/netlabs.cvs/odin32/src/opengl/glide/sst1/glide/gmovie.c,v 1.2 2001-09-05 14:30:53 bird Exp $
** $Log: gmovie.c,v $
** Revision 1.2  2001-09-05 14:30:53  bird
** Added $Id:$ keyword.
**
** Revision 1.1  2000/02/25 00:31:16  sandervl
** Created new Voodoo 1 Glide dir
**
 *
 * 3     3/09/97 10:31a Dow
 * Added GR_DIENTRY for di glide functions
**
*/
#include <string.h>

#include <3dfx.h>
#define FX_DLL_DEFINITION
#include <fxdll.h>
#include <glide.h>
#include "fxglide.h"

GR_DIENTRY(guMovieStart, void, ( void ))
{
   GrErrorCallback( "guMovieStart:  unsupported on SST hardware", FXFALSE );
}

GR_DIENTRY(guMovieStop, void, ( void ))
{
   GrErrorCallback( "guMovieStop:  unsupported on SST hardware", FXFALSE );
}

GR_DIENTRY(guMovieSetName, void, ( const char *name ))
{
   GrErrorCallback( "guMovieSetName:  unsupported on SST hardware", FXFALSE );
}

