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
    REGISTER a, b, reta, retb;
    uint64_t status;

    /*
      TODO: Handle signs a bit better
    */
    switch(instrc.opcode){
      case OP_ADD :{
        int64_t overflow = 0;
        reta.i64 = __builtin_saddl_overflow(a.i64, b.i64, &overflow);
        status   = overflow? status & 0xfffffffffffffffe : status | 1;
      }break;

      case OP_SUB :{
        int64_t overflow = 0;
        reta.i64 = __builtin_ssubl_overflow(a.i64, b.i64, &overflow);
        status   = overflow? status & 0xfffffffffffffffe : status | 1;
      }break;

      case OP_ADC :{
        int64_t ovf0 = 0, ovf1 = 0;
        a.i64    = __builtin_saddl_overflow(a.i64, comp->status & OVERFLOW, &ovf0);
        reta.i64 = __builtin_saddl_overflow(a.i64, b.i64, &ovf1);
        status   = (ovf0 | ovf1)? status & 0xfffffffffffffffe : status | 1;
      }break;

      case OP_SBB :{
        int64_t ovf0 = 0, ovf1 = 0;
        a.i64    = __builtin_ssubl_overflow(a.i64, comp->status & OVERFLOW, &ovf0);
        reta.i64 = __builtin_saddl_overflow(a.i64, b.i64, &ovf1);
        status   = (ovf0 | ovf1)? status & 0xfffffffffffffffe : status | 1;
      }break;

      case OP_IMUL :{
        int64_t overflow = 0;
        __builtin_smull_overflow(a.i64, b.i64, &overflow);
        __int128 ax = a.i64, bx = b.i64;
        ax *= bx;
        reta.i64 = ax;
        retb.i64 = ax >> 64;
        status = overflow? status & 0xfffffffffffffffe : status | 1;
      }break;

      case OP_UMUL :{
        uint64_t overflow = 0;
        __builtin_umull_overflow(a.u64, b.u64, &overflow);
        unsigned __int128 ax = a.u64, bx = b.u64;
        ax *= bx;
        reta.u64 = ax;
        retb.u64 = ax >> 64;
        status = overflow? status & 0xfffffffffffffffe : status | 1;
      }break;

      case OP_UDIV :{
        if(b.u64 != 0){
          reta.u64 = a.u64 / b.u64;
          retb.u64 = a.u64 % b.u64;
        }else{
          return 2;
        }
      }break;

      case OP_IDIV :{
        if(b.i64 != 0){
          reta.i64 = a.i64 / b.i64;
          retb.i64 = a.i64 % b.i64;
        }else{
          return 2;
        }
      }break;

      case OP_XOR :{
        reta.u64 = a.u64 ^ b.u64;
      }break;

      case OP_AND :{
        reta.u64 = a.u64 & b.u64;
      }break;

      case OP_OR  :{
        reta.u64 = a.u64 | b.u64;
      }break;

      case OP_SHL :{
        reta.u64 = a.u64 >> b.u64;
      }break;

      case OP_SHR :{
        reta.u64 = a.u64 << b.u64;
      }break;

      case OP_RTL :{
        reta.u64 = (a.u64 >> b.u64) | (a.u64 << (64 - b.u64));
      }break;

      case OP_RTR :{
        reta.u64 = (a.u64 << b.u64) | (a.u64 >> (64 - b.u64));
      }break;





    }


  }
}
