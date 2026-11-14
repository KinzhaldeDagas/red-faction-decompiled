// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061DFF7 __set_error_mode
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(signed mode), processglobal20213A8 policy
// accessor, not Windows SetErrorMode. Mode0/1/2 return OLD value thenstore newmode; mode3 returnsLIVE value without mutation. Negative/otherpositive
// ->errno22,invalid_parameter(NULL,NULL,NULL,0,0),return-1 onlyifhandlerreturns. No validation of prior global contents, atomic exchange, threadlocal storage, output, mode
// normalization or lock.
int __cdecl _set_error_mode(int Mode)
{
  int result; // eax

  if ( Mode >= 0 )
  {
    if ( Mode <= 2 )
    {
      result = unk_20213A8;
      unk_20213A8 = Mode;
      return result;
    }
    if ( Mode == 3 )
      return unk_20213A8;
  }
  *_errno() = 22;
  _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
  return -1;
}

