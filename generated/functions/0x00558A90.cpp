// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00558A90 rf_vector2_length
// UNREALRED VERIFIED [level-lifecycle-20261028]: Computes float-rounded x*x+y*y from two-float this and passes to rf_sqrt_float; x87 floating return. No normalization or zero-vector special case in body.
double __thiscall rf_vector2_length(float *this)
{
  float v2; // [esp+4h] [ebp-8h]

  v2 = *this * *this + *(this + 1) * *(this + 1);
  return rf_sqrt_float(v2);
}

