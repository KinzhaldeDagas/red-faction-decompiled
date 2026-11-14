// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006059EB __fpmath
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one flag. Call cfltcvt initializer then P5 FDIV-test helper; cache its rawEAX at2021338. Nonzero flag calls default-precision helper, zero skips.
// FNCLEX ALWAYS clears x87 exception state at end. EAX is last helper residue, not uniform init status; no own SSE enable/feature test, once guard or integer result normalization.
int __cdecl _fpmath(int a1)
{
  int result; // eax

  _cfltcvt_init_0();
  result = _ms_p5_mp_test_fdiv();
  unk_2021338 = result;
  if ( a1 )
    result = _setdefaultprecision();
  __asm { fnclex }
  return result;
}

