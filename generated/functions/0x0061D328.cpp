// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061D328 __controlfp_s
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(optional unsigned*CurrentState,unsigned
// NewValue,unsigned Mask),errno_t. Clear mask bit80000h first (effectiveMask=Mask&FFF7FFFFh). Invalid iff (NewValue&effectiveMask&FCF0FCE0h)!=0; only selected SET unsupported bits
// rejected,not mask bits alone or invalid multibit field combinations. Invalid branch: if output nonNULL query control87(0,0) and store BEFORE errno/callback; then
// errno22,invalid_parameter five zero diagnostic slots,return22 if handler returns. NULL output allowed,not invalid. Valid branch always control87(NewValue,effectiveMask),optional
// store returned actual aggregate state,return0; no success errno clear. This interface never requests bit80000h changes,unlike raw control87. No writable-output guard,independent
// x87/SSE normalization,SEH,atomic update/rollback or hardware-error conversion to errno. query can wait on pending FP conditions; delegates own live hardware effects.
errno_t __cdecl _controlfp_s(unsigned int *CurrentState, unsigned int NewValue, unsigned int Mask)
{
  unsigned int v4; // [esp-4h] [ebp-8h]

  if ( (Mask & 0xFFF7FFFF & NewValue & 0xFCF0FCE0) != 0 )
  {
    if ( CurrentState )
      *CurrentState = _control87(0, 0);
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return 22;
  }
  else
  {
    v4 = Mask & 0xFFF7FFFF;
    if ( CurrentState )
      *CurrentState = _control87(NewValue, v4);
    else
      _control87(NewValue, v4);
    return 0;
  }
}

