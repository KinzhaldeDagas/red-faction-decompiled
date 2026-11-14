// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040CFA0 rf_vector3_length
// UNREALRED VERIFIED [room-render-20261028]: Computes float-rounded x*x+y*y+z*z from this vec3 and calls rf_sqrt_float,returning x87 float result. Does not mutate vector,normalize or use squared distance. No finite/zero guard.
double __thiscall rf_vector3_length(float *this)
{
  float v2; // [esp+4h] [ebp-8h]

  v2 = *this * *this + *(this + 1) * *(this + 1) + *(this + 2) * *(this + 2);
  return rf_sqrt_float(v2);
}

