// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061863F __umatherr
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Math-error adapter, cdecl(errorCode,operation,arg1
// double,arg2 double,defaultResult double,savedCW), 36 stack bytes; ST0 result. Linear first-match search of29 native {operation,namePointer} pairs at0x665DD8; absent/NULL name uses
// fallback. Table identifies operation16 atan2,22 fmod,29 pow. Named path builds32-byte C math record {int type,+4 name,+8 arg1 double,+16 arg2 double,+24 retval double}; distinct
// from C++ std::exception. Restore raw x87 control via ctrlfp(savedCW,0xFFFF), then DIRECT CALL zero stub0x61D8D7 with record pointer; ADD ESP12 cleans pending CW args and record
// arg. Unchanged stub returns0 without examining/mutating record, so errnoFromMatherr(errorCode) runs; return local record.retval. Fallback restores CW, calls errno setter, returns
// original default. No indirect user callback or mode-global test in this function; restoration covers raw x87 CW only, no SSE state/own SEH/rollback on exceptions.
double __cdecl _umatherr(int a1, int a2, double a3, double a4, double a5, unsigned int a6)
{
  int v6; // eax
  _UNKNOWN **v7; // eax

  v6 = 0;
  while ( dword_665DD8[2 * v6] != a2 )
  {
    if ( ++v6 >= 29 )
    {
      v7 = nullptr;
      goto LABEL_5;
    }
  }
  v7 = (&off_665DDC)[2 * v6];
LABEL_5:
  if ( v7 )
  {
    _ctrlfp(a6, 0xFFFFu);
    if ( !crt_return_zero_0061d8d7() )
      _set_errno_from_matherr(a1);
    return a5;
  }
  else
  {
    _ctrlfp(a6, 0xFFFFu);
    _set_errno_from_matherr(a1);
    return a5;
  }
}

