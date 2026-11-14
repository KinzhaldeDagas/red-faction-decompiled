// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00558AD0 rf_vector2_length_squared_x87
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): ECX two-float vector. Returns x*x+y*y rounded to float then loaded into ST0 (saved C type double). No sqrt, finite/overflow guard, output vector, or stack args.
double __thiscall rf_vector2_length_squared_x87(float *this)
{
  return (float)(*this * *this + *(this + 1) * *(this + 1));
}

