// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559280 rf_vector3_normalize_return_length
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Computes float length=sqrt(x*x+y*y+z*z), multiplies all components in place by 1/length, and returns the original length in x87 ST0. No zero-length or finite-value guard. The return reloads the stored float length; ECX is the vector pointer.
double __thiscall rf_vector3_normalize_return_length(float *this)
{
  float v2; // [esp+4h] [ebp-10h]
  float v4; // [esp+Ch] [ebp-8h]
  float v5; // [esp+10h] [ebp-4h]

  v2 = *this * *this + *(this + 1) * *(this + 1) + *(this + 2) * *(this + 2);
  v5 = rf_sqrt_float(v2);
  v4 = 1.0 / v5;
  *this = *this * v4;
  *(this + 1) = *(this + 1) * v4;
  *(this + 2) = *(this + 2) * v4;
  return v5;
}

