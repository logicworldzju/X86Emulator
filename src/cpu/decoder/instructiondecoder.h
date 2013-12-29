#ifndef INSTRUCTIONDECODER_H
#define INSTRUCTIONDECODER_H
#include "../instructionformat.h"
#include "instructionstream.h"

class OpcodeTableEntry;

class InstructionDecoder
{
public:
    InstructionDecoder();
    static bool decode(InstructionStream& stream,
                       OperatingEnvironment env,
                       InstructionLowLevelFormat& lowFormat,
                       InstructionHighLevelFormat& highFormat);
private:
//    static const OpcodeTableEntry& findOpcodeTableEntry(OpcodeTableEntry opcodeTable[],
//                                                 u16 tableSize,u8 opcode);
    static void getModRM(InstructionStream& stream,
                         InstructionLowLevelFormat& lowFormat);
    static void getSIB(InstructionStream& stream,
                         InstructionLowLevelFormat& lowFormat);
    typedef void (*OT_jump)(InstructionStream& stream,
                                    InstructionLowLevelFormat& lowFormat,
                                    InstructionHighLevelFormat& highFormat,
                                IFOperand& operand);
    static void OT_NOT_EXISTS_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OT_RAX_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_RCX_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_RDX_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_RBX_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_RSP_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_RBP_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_RSI_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_RDI_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_ES_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_CS_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_SS_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_DS_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_FS_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_GS_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_A_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_C_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_D_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_E_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_F_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_G_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_I_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_J_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_M_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_O_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_P_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_PR_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_Q_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_R_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_S_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_V_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_VR_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_W_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_X_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_Y_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_ZERO_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    static void OT_ONE_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                            IFOperand& operand);
    typedef void (*OS_jump)(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                                    IFOperand& operand);
    static void OS_NOT_EXISTS_jump(InstructionStream& stream,
                                   InstructionLowLevelFormat& lowFormat,
                                   InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_a_jump(InstructionStream& stream,
                          InstructionLowLevelFormat& lowFormat,
                          InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_b_jump(InstructionStream& stream,
                          InstructionLowLevelFormat& lowFormat,
                          InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_d_jump(InstructionStream& stream,
                          InstructionLowLevelFormat& lowFormat,
                          InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_dq_jump(InstructionStream& stream,
                           InstructionLowLevelFormat& lowFormat,
                           InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_p_jump(InstructionStream& stream,
                          InstructionLowLevelFormat& lowFormat,
                          InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_pd_jump(InstructionStream& stream,
                           InstructionLowLevelFormat& lowFormat,
                           InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_pi_jump(InstructionStream& stream,
                           InstructionLowLevelFormat& lowFormat,
                           InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_ps_jump(InstructionStream& stream,
                           InstructionLowLevelFormat& lowFormat,
                           InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_q_jump(InstructionStream& stream,
                          InstructionLowLevelFormat& lowFormat,
                          InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_s_jump(InstructionStream& stream,
                          InstructionLowLevelFormat& lowFormat,
                          InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_sd_jump(InstructionStream& stream,
                           InstructionLowLevelFormat& lowFormat,
                           InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_si_jump(InstructionStream& stream,
                           InstructionLowLevelFormat& lowFormat,
                           InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_ss_jump(InstructionStream& stream,
                           InstructionLowLevelFormat& lowFormat,
                           InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_v_jump(InstructionStream& stream,
                          InstructionLowLevelFormat& lowFormat,
                          InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_w_jump(InstructionStream& stream,
                          InstructionLowLevelFormat& lowFormat,
                          InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_z_jump(InstructionStream& stream,
                          InstructionLowLevelFormat& lowFormat,
                          InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_slash_n_jump(InstructionStream& stream,
                                InstructionLowLevelFormat& lowFormat,
                                InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_Mw_Rv_jump(InstructionStream& stream,
                              InstructionLowLevelFormat& lowFormat,
                              InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static void OS_d_q_jump(InstructionStream& stream,
                            InstructionLowLevelFormat& lowFormat,
                            InstructionHighLevelFormat& highFormat,
                                   IFOperand& operand);
    static OT_jump OT_jumpTable[];
    static OS_jump OS_jumpTable[];
};

#endif // INSTRUCTIONDECODER_H
