#ifndef EXECGPREGISTEROPERAND_H
#define EXECGPREGISTEROPERAND_H

#include "execreadwriteoperand.h"
#include "cpu/registerfile.h"

class ExecGPRegisterOperand :public ExecReadWriteOperand
{
public:
    ExecGPRegisterOperand(RegisterFile& file,u8 gpRegister,IFOperand::IFOperandSize size)
        :_file(file),_gpRegister(gpRegister),_size(size)
    {
    }
    virtual void prepareReadSigned()
    {
        switch(_size)
        {
        case IFOperand::BYTE:
            _sValue = static_cast<s8>(_file.getGPR8Bits(_gpRegister));
            break;
        case IFOperand::WORD:
            _sValue = static_cast<s16>(_file.getGPR16Bits(_gpRegister));
            break;
        case IFOperand::DWORD:
            _sValue = static_cast<s32>(_file.getGPR32Bits(_gpRegister));
            break;
        case IFOperand::QWORD:
            _sValue = static_cast<s64>(_file.getGPR64Bits(_gpRegister));
            break;
        default:
            assert(0);
        }
    }
    virtual void prepareReadUnsigned()
    {
        switch(_size)
        {
        case IFOperand::BYTE:
            _uValue = static_cast<u8>(_file.getGPR8Bits(_gpRegister));
            break;
        case IFOperand::WORD:
            _uValue = static_cast<u16>(_file.getGPR16Bits(_gpRegister));
            break;
        case IFOperand::DWORD:
            _uValue = static_cast<u32>(_file.getGPR32Bits(_gpRegister));
            break;
        case IFOperand::QWORD:
            _uValue = static_cast<u64>(_file.getGPR64Bits(_gpRegister));
            break;
        default:
            assert(0);
        }
    }
    virtual void setU8(u8 value)
    {
        assert(_size==IFOperand::BYTE);
        _file.setGPR8Bits(_gpRegister,value);
    }
    virtual void setU16(u16 value)
    {
        assert(_size==IFOperand::WORD);
        _file.setGPR16Bits(_gpRegister,value);
    }
    virtual void setU32(u32 value)
    {
        assert(_size==IFOperand::DWORD);
        _file.setGPR32Bits(_gpRegister,value);
    }
    virtual void setU64(u64 value)
    {
        assert(_size==IFOperand::QWORD);
        _file.setGPR64Bits(_gpRegister,value);
    }
protected:
    RegisterFile& _file;
    u8 _gpRegister;
};

#endif // EXECGPREGISTEROPERAND_H
