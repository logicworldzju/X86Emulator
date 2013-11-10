#ifndef EXECREADWRITEOPERAND_H
#define EXECREADWRITEOPERAND_H

#include "execreadoperand.h"
#include "execwriteoperand.h"

class ExecReadWriteOperand :public ExecWriteOperand,public ExecReadOperand
{

};

#endif // EXECREADWRITEOPERAND_H
