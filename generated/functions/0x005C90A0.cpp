// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C90A0 rf_vector2_dot
// UNREALRED VERIFIED [renderer-helpers-20261028]: Returns float-rounded this.x*other.x + this.y*other.y through x87. Exactly two floats per input; no normalization or pointer validation.
double __thiscall rf_vector2_dot(float *this, float *a2)
{
  return (float)(*this * *a2 + *(this + 1) * a2[1]);
}

