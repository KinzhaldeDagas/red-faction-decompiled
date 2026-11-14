// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040DBD0 rf_vector_construct_no_unwind
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Stdcall(base,stride,count,constructor), four DWORD slots, RET16. Each iteration subtracts1 from the32-bit count slot then tests sign of that wrapped result;
// if nonnegative invokes constructor indirectly with current base in ECX and no explicit stack arguments, advances base by stride with32-bit wrap, repeats. Positive signed counts run
// count constructors; zero and ordinary negative counts skip. INT_MIN wraps to INT_MAX on the first decrement and is therefore not a skipped-negative case. No callback
// null/stride/bounds checks, exception registration, or rollback/destructor callback. Generic compiler vector-construction helper retains library classification; constructor EAX is
// not a specified aggregate result.
void __stdcall rf_vector_construct_no_unwind(char *a1, unsigned int a2, int a3, void *(__thiscall *a4)(void *))
{
  while ( --a3 >= 0 )
  {
    a4(a1);
    a1 += a2;
  }
}

