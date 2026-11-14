// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DA160 rf_exp_float
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): CORRECTION: decorated log(float) label was false. Thin float wrapper forwards unchanged input to4DA180,which loads x87 and calls __CIexp,rounds result tofloat and returns ST0. Used for particle exponential force attenuation exp(-falloff*distance),not logarithm. No input-domain clamp or overflow handling in wrapper.
double __cdecl rf_exp_float(float a1)
{
  return rf_exp_float_core(a1);
}

