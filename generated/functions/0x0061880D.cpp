// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061880D __clrfp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No C arguments. FNSTSW localWORD (nonwaiting),FNCLEX clears x87 exception state,then MOVSX ORIGINAL signed16 status intoEAX. Return pre-clear status
// sign-extended; no CW change or numeric stack pop. Incoming fpstat formal was false; corrected no-arg ABI.
int __cdecl _clrfp()
{
  __int16 v0; // fps

  __asm { fnclex }
  return v0;
}

