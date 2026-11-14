// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006066BD ??_M@YGXPAXIHP6EX0@Z@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native stdcall(base,strideUnsigned32,countSigned32,thiscallDestructor), RET16, SEH-prolog4/epilog4 frame. Compute low32(stride*count), add to local base
// with32-bit wrap. Set state0; loop DEC count then JS exit, SUB pointer,stride, MOV ECX,pointer,CALL callback without pushed argument; normal positive count destroys reverse
// count-1..0. Count0 and ordinary negative counts make no callback, but INT_MIN DEC wraps to INT_MAX and does NOT exit: no overflow/negative-range validation. Zero stride repeatedly
// addresses same element, products/address arithmetic wrap, callback/base NULL unguarded. Normal completion sets completedDWORD1,tryLevel-2, calls606708 local finally, whose
// completed test skips unwind, then restores frame and RET16. Abnormal finally with completed0 calls __ArrayUnwind(current pointer,stride,remaining count,callback), with four stack
// slots and helper-owned cleanup; remaining count was already decremented before throwing callback. No containing-array free, callback success test, initialized-capacity lookup,
// rollback/reconstruction or semantic EAX result. Scope record65E780 and captured local finally belong to this function, not extra normal destructor passes.
void __stdcall `eh vector destructor iterator'(char *a1, unsigned int a2, int a3, void (__thiscall *a4)(void *))
{
  char *i; // [esp+34h] [ebp+8h]

  for ( i = &a1[a3 * a2]; --a3 >= 0; a4(i) )
    i -= a2;
}

