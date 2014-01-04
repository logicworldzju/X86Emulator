#ifndef PRINTER_H
#define PRINTER_H
#include "io/ioport.h"

class Printer
{
public:
    Printer();
    IOPort& getIOPort(){return _ioPort;}
    u32 readFromPort(Memory &memory, RegisterFile &registerFile);
    void write2Port(u32 value, Memory &memory, RegisterFile &registerFile);
private:
    class PrinterIOPort:public IOPort
    {
    public:
        PrinterIOPort(Printer& printer):_printer(printer){}
        u32 readFromPort(Memory &memory, RegisterFile &registerFile){return _printer.readFromPort(memory,registerFile);}
        void write2Port(u32 value, Memory &memory, RegisterFile &registerFile){_printer.write2Port(value,memory,registerFile);}
    private:
        Printer& _printer;
    };
    PrinterIOPort _ioPort;
};

#endif // PRINTER_H
