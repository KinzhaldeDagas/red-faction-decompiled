// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DA180 rf_exp_float_core
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Loads float argument into x87 ST0,calls CRT __CIexp at609E0C,stores returned result to32-bit float local,reloads and returns ST0. __CIexp dispatch verified in original code. No local special-case handling,finite/range check or logarithm operation. Core behind falsely decorated4DA160 wrapper.
double __cdecl rf_exp_float_core(float a1)
{
  return (float)exp(a1);
}

