// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006185DE __set_errno_from_matherr
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl signed math-error code,void. Code exactly1
// ->errno slot getter,store decimal33. Signed code2 or3 ->getter,store decimal34. All other values (including0,negative,>=4) return WITHOUT fetching/changing errno. No success errno
// reset,invalid-parameter callback,math callback,FP state change,range conversion or status result. Slot provider can use thread-local or shared fallback as separately reviewed; EAX
// on return incidental.
void __cdecl _set_errno_from_matherr(int a1)
{
  if ( a1 == 1 )
  {
    *_errno() = 33;
  }
  else if ( a1 > 1 && a1 <= 3 )
  {
    *_errno() = 34;
  }
}

