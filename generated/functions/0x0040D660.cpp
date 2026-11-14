// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D660 rf_float_minimum_two_values
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Cdecl two floats; returns second if second<=first,otherwise first,through ST0. Existing verified minimum behavior retained with descriptive name. Assembly FCOMPP then TEST AH,0x41 makes unordered comparison select SECOND too; no symmetric NaN normalization.
double __cdecl rf_float_minimum_two_values(float a1, float a2)
{
  if ( a2 <= (double)a1 )
    return a2;
  else
    return a1;
}

