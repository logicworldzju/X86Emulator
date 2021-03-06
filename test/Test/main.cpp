#include <QtCore/QString>
#include <QtTest/QtTest>

#include "cpu/cputype.h"
#include "cpu/instructionformat.h"
#include "cpu/opcodetable.h"
#include "cpu/decoder/instructiondecoder.h"
#include "cpu/decoder/instructionstreamfromfile.h"
#include "cpu/decoder/instructionstreamfrommemory.h"
#include "cpu/executer/operand/execgpregisteroperand.h"
#include "cpu/executer/operand/execimmediateoperand.h"
#include "cpu/executer/operand/execmemoryoperand.h"
#include "cpu/executer/operand/execsegmentregisteroperand.h"
#include "cpu/register/registerfile.h"
#include "interrupt/interrupt.h"
#include "io/ioportlist.h"
#include "memory/debugmemory.h"
#include "gui/video.h"

#include "testmemory.h"

//QTEST_APPLESS_MAIN(TestMemory);

#include "testioportlist.h"
//QTEST_APPLESS_MAIN(TestIOPortList);

#include "testinstructionstream.h"
//QTEST_APPLESS_MAIN(TestInstructionStream)

#include "testregisterfile.h"
//QTEST_APPLESS_MAIN(TestRegisterFile)

#include "testexecoperand.h"
//QTEST_APPLESS_MAIN(TestExecOperand)

#include "testdecoderencoder.h"
//QTEST_APPLESS_MAIN(TestDecoderEncoder)

#include "testexecute.h"
//QTEST_MAIN(TestExecute)

#include "testinstructionexecuter.h"
//QTEST_MAIN(TestInstructionExecuter)

#include "testbios.h"
//QTEST_MAIN(TestBIOS)

#include "testdebugcpu.h"
//QTEST_MAIN(TestDebugCPU)

#include "testcharactercode.h"
//QTEST_MAIN(TestCharacterCode)

#include "testconsolewidget.h"
//QTEST_MAIN(TestConsoleWidget)

#include "testvideo.h"
//QTEST_MAIN(TestVideo)

#include "testkeyboard.h"
//QTEST_MAIN(TestKeyboard)

#include "testtimeofday.h"
//QTEST_MAIN(TestTimeOfDay)

#include "testfloppy.h"
//QTEST_MAIN(TestFloppy)

#include "testdiskette.h"
QTEST_MAIN(TestDiskette)

//QTEST_
