// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605A24 _sqrt
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Ordinary sqrt(double) entry: LEA EDX to caller DOUBLE at entryESP+4; CALL fload_withFB. Nine-byte IDA function then FALLS THROUGH at605A2D into shared
// kernel, with original return PC/argument stack and helper-established flags/ST0. No own RET/FSQRT or fresh input ST0 requirement. Existing separate function boundary retained;
// kernel is not silently counted as decoded by this adapter annotation.
double __cdecl sqrt(double X)
{
  bool v1; // zf
  long double v2; // st7

  v2 = _fload_withFB(&X);
  return crt_sqrt_x87_core(v2, v1, X);
}

