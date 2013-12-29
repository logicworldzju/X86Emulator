#ifndef EXECGPREGISTEROPERAND_H
#define EXECGPREGISTEROPERAND_H

#include "execreadwriteoperand.h"
#include "../../register/registerfile.h"

class ExecGPRegisterOperand :public ExecReadWriteOperand
{
public:
    ExecGPRegisterOperand(RegisterFile& file,u8 gpRegister,DataSize size,
                          bool hasREXPrefix)
        :_file(file),_gpRegister(gpRegister),_hasREXPrefix(hasREXPrefix)
    {
        _size=size;
    }
    virtual void prepareReadSigned()
    {
        switch(_size)
        {
        case DATA_SIZE_BYTE:
            if(_hasREXPrefix)
                _sValue = static_cast<s8>(_file.getGPR8BitsLow(_gpRegister));
            else
                _sValue = static_cast<s8>(_file.getGPR8Bits(_gpRegister));
            break;
        case DATA_SIZE_WORD:
            _sValue = static_cast<s16>(_file.getGPR16Bits(_gpRegister));
            break;
        case DATA_SIZE_DWORD:
            _sValue = static_cast<s32>(_file.getGPR32Bits(_gpRegister));
            break;
        case DATA_SIZE_QWORD:
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
        case DATA_SIZE_BYTE:
            if(_hasREXPrefix)
                _uValue = static_cast<u8>(_file.getGPR8BitsLow(_gpRegister));
            else
                _uValue = static_cast<u8>(_file.getGPR8Bits(_gpRegister));
            break;
        case DATA_SIZE_WORD:
            _uValue = static_cast<u16>(_file.getGPR16Bits(_gpRegister));
            break;
        case DATA_SIZE_DWORD:
            _uValue = static_cast<u32>(_file.getGPR32Bits(_gpRegister));
            break;
        case DATA_SIZE_QWORD:
            _uValue = static_cast<u64>(_file.getGPR64Bits(_gpRegister));
            break;
        default:
            assert(0);
        }
    }
    virtual void setU8(u8 value)
    {
        assert(_size==DATA_SIZE_BYTE);
        _file.setGPR8Bits(_gpRegister,value);
    }
    virtual void setU16(u16 value)
    {
        assert(_size==DATA_SIZE_WORD);
        _file.setGPR16Bits(_gpRegister,value);
    }
    virtual void setU32(u32 value)
    {
        assert(_size==DATA_SIZE_DWORD);
        _file.setGPR32Bits(_gpRegister,value);
    }
    virtual void setU64(u64 value)
    {
        assert(_size==DATA_SIZE_QWORD);
        _file.setGPR64Bits(_gpRegister,value);
    }
protected:
    RegisterFile& _file;
    u8 _gpRegister;
    bool _hasREXPrefix;
};

#endif // EXECGPREGISTEROPERAND_H
