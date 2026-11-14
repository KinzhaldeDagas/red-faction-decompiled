// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006186DF __handle_qnan1
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Unary math-error adapter; cdecl(operation,double
// arg,unsigned savedCW), ST0 result. Own code performs NO NaN classification or quiet-bit edit. Global0x666060==0 delegates umatherr(1,operation,arg,+0.0,arg,savedCW), caller
// cleanup36. Nonzero mode sets errno33, restores raw x87 CW with ctrlfp(savedCW,0xFFFF), then FLD original argument. FP loads/stores obey live FP environment; no payload preservation
// guarantee, SSE-state restoration or own SEH.
double __cdecl _handle_qnan1(int a1, double a2, unsigned int a3)
{
  if ( !dword_666060 )
    return _umatherr(1, a1, a2, 0.0, a2, a3);
  *_errno() = 33;
  _ctrlfp(a3, 0xFFFFu);
  return a2;
}

