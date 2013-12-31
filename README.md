X86Emulator
===========

Another x86 emulator which is like bochs. But it is much weaker in the functionality. As it is a course project,now we only want to emulate MS-DOS on it.
Some features
-------------
* It supports bochs like debugging. For example,set break points,show registers,disasm instructions.
* It supports Windows,Linux and other platforms that Qt4.x can work. Qt is used as a GUI toolkit in the project. And the core part of the code can work on any platform that supports c++ and does arithmetic calculation with 2's complement.
* It supports almost all basic instructions and system instrutions in the one byte opcode table in the 16bit,32bit and 64bit mode. As 32bit protect-mode and 64bit long-mode is real complicated,we didn't implement it. So it can only emulate the real mode programs like MS-DOS.
* We emulate the BIOS intermediate layer which DOS relays on,so there is no real hardware emulation. So it takes much lesser time to code. And this is a very important difference between X86Emulator and bochs.

How to build it
------------
### Some requirements
* Qt 4.x or 5.x
* nasm(may not be necessary)

### Steps
1. cd into the src/bios/ and execute the genBin.sh(unix) or genBin.cmd(windows).As I have upload one bios.bin, this may not be necessary.
2. cd into the src/ ,use qmake to generate the native makefile,then make it.Using Qt Creater to open the X86Emulator.pro and Compiling it is another but actually the same method.
3. Finally,you will find a X86Emulator executable file in the X86Emulator directory.
