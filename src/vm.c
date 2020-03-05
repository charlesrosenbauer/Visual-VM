#include "stdint.h"
#include "vm.h"







int step(COMPUTER* comp, int steps){

  for(int i = 0; i < steps; i++){

    // Get instruction
    INSTRUCTION instrc;
    if((comp->ip < 0) || (comp->ip >= comp->programsize)){
      return 1;
    }
    instrc = comp->program[comp->ip];
    uint64_t a, b, reta, retb, status;

    /*
      TODO: Handle signs a bit better
    */
    switch(instrc.opcode){
      case OP_ADD :{
        int overflow = 0;
        reta = __builtin_addl(a, b, &overflow);
        status = overflow? status & 0xfffffffffffffffe : status | 1;
      }break;

      case OP_SUB :{
        int overflow = 0;
        reta = __builtin_subl(a, b, &overflow);
        status = overflow? status & 0xfffffffffffffffe : status | 1;
      }break;

      case OP_ADC :{
        int ovf0 = 0, ovf1 = 0;
        a    = __builtin_addl(a, comp->status & OVERFLOW, &ovf0);
        reta = __builtin_addl(a, b, &ovf1);
        status = (ovf0 | ovf1)? status & 0xfffffffffffffffe : status | 1;
      }break;

      case OP_SBB :{
        int ovf0 = 0, ovf1 = 0;
        a    = __builtin_subl(a, comp->status & OVERFLOW, &ovf0);
        reta = __builtin_addl(a, b, &ovf1);
        status = (ovf0 | ovf1)? status & 0xfffffffffffffffe : status | 1;
      }break;

      case OP_IMUL :{
        int overflow = 0;
        reta = __builtin_smull(a, b, &overflow);
        __int128 ax = a, bx = b;
        ax *= bx;
        reta = ax;
        retb = ax >> 64;
        status = overflow? status & 0xfffffffffffffffe : status | 1;
      }break;

      case OP_UMUL :{
        int overflow = 0;
        reta = __builtin_umull(a, b, &overflow);
        unsigned __int128 ax = a, bx = b;
        ax *= bx;
        reta = ax;
        retb = ax >> 64;
        status = overflow? status & 0xfffffffffffffffe : status | 1;
      }break;

      case OP_UDIV :{
        if(b != 0){
          reta = a / b;
          retb = a % b;
        }else{
          return 2;
        }
      }break;

      case OP_IDIV :{
        if(b != 0){
          reta = a / b;
          retb = a % b;
        }else{
          return 2;
        }
      }break;

      case OP_XOR :{
        reta = a ^ b;
      }break;

      case OP_AND :{
        reta = a & b;
      }break;

      case OP_OR  :{
        reta = a | b;
      }break;

      case OP_SHL :{
        reta = a >> b;
      }break;

      case OP_SHR :{
        reta = a << b;
      }break;

      case OP_RTL :{
        reta = (a >> b) | (a << (64 - b));
      }break;

      case OP_RTR :{
        reta = (a << b) | (a >> (64 - b));
      }break;





    }


  }
}
