#ifndef __VM_HEADER__
#define __VM_HEADER__


#include "stdint.h"



typedef struct{
  uint8_t  opcode;
  uint8_t  a, b, sib;
  uint32_t imm;
}OPCODE;






#endif
