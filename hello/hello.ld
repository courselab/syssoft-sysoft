/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *    SPDX-FileCopyrightText: 2025 Andrey <andrey.cortez12@gmail.com>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *  This file is a derivative of SYSeg (https://gitlab.com/monaco/syseg)
 *  and includes modifications made by the following author(s):
 *  Andrey <andrey.cortez12@gmail.com>
 */

/*  Linker script for MBR. */

OUTPUT_FORMAT(binary)		/* Output flat binary blob. */
SECTIONS
{
        . = 0x7C00;		/* Initial memory address (BIOS legacy boot) */
	
        .text :
	{
	  *(.text)              /* Copy input section .text to the oputput. */
	  *(.rodata*)		/* Copy input section .rodata to the output. */
	}
	
        . = 0x7c00 + 510;	/* Advance 510 bytes. */
	
        .signature : 		/* Add a signadure section with this content. */
	{
	    BYTE(0x55)
            BYTE(0xAA)
        }
}

STARTUP(crt0.o);




