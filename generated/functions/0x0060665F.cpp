// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060665F ?__ArrayUnwind@@YGXPAXIHP6EX0@Z@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Stdcall(endPointer,unsigned stride,signed
// count,thiscallDtor),RET16,void; corrected callback from no-argument C pointer to ECX receiver. SEH4 original65E760 scope0 filter606682,handler6066AB. Predecrement count DWORD
// modulo32; if signbit set exit, else subtract stride from pointer modulo32,ECX=new pointer,CALL dtor with no explicit stack args,ignore result,repeat. Thus ordinary countN>0
// destroys N elements backward starting end-stride; zero and ordinary negative values exit without dereference, BUT INT_MIN decrement wraps to INT_MAX and enters huge iteration
// sequence. No signed-overflow/range/pointer guard. Filter reads exception code via EXCEPTION_POINTERS: E06D7363 ->terminate; all other codes return0/continue-search. Handler
// restoringESP exists but unchanged filter has no returning1 path, so normal local handler entry unreachable. Normal disarm/SEH epilog; no allocation/free, callbackNULL test,
// item-status handling, swallowing of non-C++ exceptions or guarantee to finish remaining elements after exception.
void __stdcall __ArrayUnwind(char *a1, unsigned int a2, int a3, void (__thiscall *a4)(void *))
{
  while ( --a3 >= 0 )
  {
    a1 -= a2;
    ((void (*)(void))a4)();
  }
}

