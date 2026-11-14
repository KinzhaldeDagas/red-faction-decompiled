// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D250 rf_vector3_set_components_thiscall
// UNREALRED VERIFIED [stream-serializers-20261029]: Thiscall destination and3 float components. Stores at offsets0,4,8 and returns destination. No allocation,normalization or arithmetic. Distinct ABI wrapper from other named vector setters.
float *__thiscall rf_vector3_set_components_thiscall(float *this, float a2, float a3, float a4)
{
  *this = a2;
  *(this + 1) = a3;
  *(this + 2) = a4;
  return this;
}

