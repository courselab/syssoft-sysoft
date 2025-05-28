 #    SPDX-FileCopyrightText: 2025 Andrey <andrey.cortez12@gmail.com>
 #    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 #
 #    SPDX-License-Identifier: GPL-3.0-or-later
 #
 #  This file is a derivative of SYSeg (https://gitlab.com/monaco/syseg)
 #  and includes modifications made by the following author(s):
 #  Andrey <andrey.cortez12@gmail.com>

         .code16gcc
         .global printf
         .global get_conventional_memory_kb /* Our new function */

         .section .text

 printf:
         /* Expects pointer to null-terminated string in %cx */
         mov   %cx, %bx          /* Use %bx as base pointer for string */
         mov   $0x0e,%ah         /* BIOS teletype output function */
         mov   $0x0, %si         /* Index into the string */
 loop:
         mov   (%bx, %si), %al   /* Get character from string */
         cmp   $0x0, %al         /* Check for null terminator */
         je    end               /* If null, end of string */
         int   $0x10             /* Call BIOS video service */
         add   $0x1, %si         /* Increment string index */
         jmp   loop              /* Repeat for next character */
 end:
         mov %si, %ax            /* Return number of characters printed (optional, common practice) */
         ret

 get_conventional_memory_kb:
         /*
          * This function calls BIOS interrupt 0x12 to get the
          * conventional memory size in kilobytes.
          * The result is returned in %ax by the BIOS.
          * GCC expects function return values in %ax for integers,
          * so no explicit mov to %ax is needed before ret.
          */
         int   $0x12             /* Call BIOS interrupt to get memory size */
                                 /* AX = memory size in Kbytes */
         ret                     /* Return to caller, result is in %ax */
