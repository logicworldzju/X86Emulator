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

class TestTest : public QObject
{
    Q_OBJECT

public:
    TestTest();

private Q_SLOTS:
    void testCase1();
};

TestTest::TestTest()
{
}

void TestTest::testCase1()
{
    //QVERIFY2(true, "Failure");

}

QTEST_APPLESS_MAIN(TestTest);

#include "tst_testtest.moc"
