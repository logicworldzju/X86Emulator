#include "printer.h"
#include <assert.h>
#include <QDebug>

Printer::Printer()
    :_ioPort(*this)
{
}

u32 Printer::readFromPort(Memory &memory, RegisterFile &registerFile)
{
    assert(0);
    return 0xcccccccc;
}

void Printer::write2Port(u32 value, Memory &memory, RegisterFile &registerFile)
{
    (void)value;(void)memory;(void)registerFile;
    qDebug()<<"Printer:write2Printer"<<endl;
    qDebug()<<registerFile.toString().c_str();
}
