// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A1B0 rf_vector2_assign_components
// UNREALRED VERIFIED [level-lifecycle-20261028]: Writes two supplied floats to this[0]/this[1] and returns this. No normalization, finite checks or allocation.
float *__thiscall rf_vector2_assign_components(float *this, float a2, float a3)
{
  *this = a2;
  *(this + 1) = a3;
  return this;
}

