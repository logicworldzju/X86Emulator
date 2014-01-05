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
2. cd into the src/ ,use qmake to generate the native makefile,then make it.Using Qt Creater to open the X86Emulator.pro and Compiling it is another but actually the same way.
3. Finally,you will find a X86Emulator executable file in the X86Emulator directory.

The End
------------
As a course project, its life ended after a demo in the course projcet presentation.The project is partially succeeded.It do run MS-DOS 6.22 now,but not all commands and programs in DOS works well.
###Screenshots
The followings are some screenshots.

DOS start up screen.  
![Start DOS](https://raw.github.com/wiki/logicworldzju/X86Emulator/images/startDOS.png "Start DOS")

The most successful one.  
![PV12](https://raw.github.com/wiki/logicworldzju/X86Emulator/images/pv12.png "PV12")

The Next one is the screenshot of the X86Emulator debugger which is very similar to bochs's.  
![Debugger](https://raw.github.com/wiki/logicworldzju/X86Emulator/images/debugger.png "Debugger")

The last one is a failed case,EDIT.EXE in DOS.  
![EDIT.EXE](https://raw.github.com/wiki/logicworldzju/X86Emulator/images/editFailed.png "EDIT.EXE")

So there are still some bugs in the code or hardware emulation is not enough for Edit.EXE.

###Acknowledgement
Bochs is a nice x86 emulator,without which I would not start up this project and end this project.  
EasyVM is a nice implementation reference,as it is small and easy enough to understand.Many thanks to its author,Yixin Liang,who open source it.

Further
------------
If you want to do some course projects like x86 emulator,assembler,disassembler,executer,analyser etc.This is a good reference. The following is a design of the CPU Instruction Processing Pipeline.
![CPU Instruction Processing Pipeline](https://raw.github.com/wiki/logicworldzju/X86Emulator/images/cpuArch.png "CPU Instruction Processing Pipeline")
As I have taken future extension into consideration during the design,it is not hard to use this code to make a x86 disassembler etc.And the whole design is in the wiki pages,but mainly in chinese.
