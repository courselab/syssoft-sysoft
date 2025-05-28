 #    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 #    SPDX-FileCopyrightText: 2025 Andrey <andrey.cortez12@gmail.com>
 #
 #    SPDX-License-Identifier: GPL-3.0-or-later
 #
 #  This file is a derivative of SYSeg (https://gitlab.com/monaco/syseg)
 #  and includes modifications made by the following author(s):
 #  Andrey <andrey.cortez12@gmail.com>

 CC=gcc
 MAKE=make

 this: hello.bin

 # Note: Removed duplicate "this: hello.bin" line

 # Added -fno-stack-protector to prevent __stack_chk_fail errors
 main.o : main.c
	$(CC) -m16 -O1 -Wall -fno-pic -fno-asynchronous-unwind-tables -fno-stack-protector -c $< -fno-builtin -nostdinc -I. -o $@

 libc.o : libc.S
	$(CC) -m16 -O1 -Wall -fno-pic -fno-asynchronous-unwind-tables -c $< -fno-builtin -o $@

 crt0.o : crt0.S
	$(CC) -m16 -O1 -Wall -fno-pic -fno-asynchronous-unwind-tables -c $< -fno-builtin -o $@

 # Corrected line: hello.ld is now an order-only prerequisite.
 # Linker command now explicitly lists main.o and libc.o.
 # crt0.o is OMITTED from the linker command line here, assuming that
 # hello.ld is responsible for including crt0.o (e.g., via an INPUT(crt0.o) command).
 # If crt0.o is listed here AND hello.ld also pulls it in, it can cause "multiple definition" errors for _start.
 # crt0.o is still a prerequisite for hello.bin to ensure it's compiled first.
 hello.bin : main.o libc.o crt0.o | hello.ld
	$(CC) -m16 main.o libc.o -nostartfiles -nostdlib -T hello.ld -orphan-handling=discard -o $@




 #
 # Housekeeping
 #

 clean:
	rm -f  *.bin *.elf *.o *.s *.iso *.img *.i kh
	$(MAKE) clean-extra


 # SYSeg's  convenience rules (not related to the example itself)
 include bintools.mk
