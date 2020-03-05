#ifndef __VM_HEADER__
#define __VM_HEADER__


#include "stdint.h"



typedef enum{
  OP_ADD,
  OP_SUB,
  OP_ADC,
  OP_SBB,
  OP_IMUL,
  OP_UMUL,
  OP_IDIV,
  OP_UDIV,
  OP_AND,
  OP_XOR,
  OP_OR,
  OP_SHL,
  OP_SHR,
  OP_RTL,
  OP_RTR,
  OP_ILS,
  OP_ULS,
  OP_ILSE,
  OP_ULSE,
  OP_IGT,
  OP_UGT,
  OP_IGTE,
  OP_UGTE,
  OP_EQ,
  OP_NEQ,
  OP_NZ,
  OP_FADD,
  OP_FSUB,
  OP_FMUL,
  OP_FDIV,
  OP_FLS,
  OP_FLSE,
  OP_FGT,
  OP_FGTE,
  OP_FEQ,
  OP_FNEQ,
  OP_FNZ,
  OP_LOD,
  OP_STR,
  OP_CMOV,
  OP_B,
  OP_JMP,
  OP_PUSH,
  OP_POP
}OPCODE;

const int OVERFLOW = 1;


typedef enum{
  B8, B16, B32, B64
}OPSIZE;


typedef struct{
  OPCODE   opcode;
  OPSIZE   size;
  uint8_t  regs, sib;
  int32_t  imm;
}INSTRUCTION;



typedef struct{
  void*          ram;
  INSTRUCTION*   program;
  uint64_t       registers[16];
  uint64_t       status, ip;
  uint32_t*      screen;
  int            programsize, ramsize, h, w;
}COMPUTER;







#endif
