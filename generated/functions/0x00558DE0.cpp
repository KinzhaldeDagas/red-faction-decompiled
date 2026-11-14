// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00558DE0 rf_vector3_dot_xyz_by_value
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): ECX vector plus three FLOAT stack values, RET12. Computes x*a+y*b+z*c, rounds result to float and returns through ST0 as saved double. Not pointer arguments or an output-vector operation.
double __thiscall rf_vector3_dot_xyz_by_value(float *this, float a2, float a3, float a4)
{
  return (float)(*this * a2 + *(this + 1) * a3 + *(this + 2) * a4);
}

