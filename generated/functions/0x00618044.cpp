// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00618044 __decomp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Double decomposition, cdecl(double,int*), returns
// mantissa in ST0 and writes exponent through pointer. Comparing against initial FLDZ identifies both signed zeros and returns +0/exponent0. Normal exponent field yields
// exponent=(field-1022), set_exp(original,0) rewrites exponent field to 0x3FE. Infinity/NaN field 0x7FF therefore yields exponent1025 and rewritten field, not special-value
// passthrough. Subnormal path records sign by x87 comparison, shifts 64-bit fraction left until bit52 set while decrementing EDX from -1021, clears bit52, restores sign, calls
// set_exp(mutated copy,0). Smallest subnormal takes52 shifts -> exponent -1073/mantissa +/-0.5; largest takes1 -> -1022. EDX exponent survives set_exp by verified native leaf
// preservation; old generic cdecl spoil inference produced undefined pseudocode temporaries. Input shifts affect own argument copy. No output-pointer check, own SEH, errno or x87
// environment save; comparison/load/store obey live FP environment.
// local variable allocation has failed, the output may be wrong!
double __cdecl _decomp(double a1, int *a2)
{
  double result; // st7
  int v3; // edx
  BOOL v4; // eax

  result = 0.0;
  if ( 0.0 == a1 )
  {
    v3 = 0;
  }
  else if ( (HIWORD(a1) & 0x7FF0) == 0 && ((HIDWORD(a1) & 0xFFFFF) != 0 || LODWORD(a1)) )
  {
    v3 = -1021;
    v4 = a1 < 0.0;
    while ( (BYTE6(a1) & 0x10) == 0 )
    {
      HIDWORD(a1) *= 2;
      if ( SLODWORD(a1) < 0 )
        HIDWORD(a1) |= 1u;
      LODWORD(a1) *= 2;
      --v3;
    }
    HIWORD(a1) &= ~0x10u;
    if ( v4 )
      HIWORD(a1) |= 0x8000u;
    result = _set_exp(a1, 0);
  }
  else
  {
    result = _set_exp(a1, 0);
    v3 = ((*(_DWORD *)((char *)&a1 + 6) >> 4) & 0x7FF) - 1022;
  }
  *a2 = v3;
  return result;
}

