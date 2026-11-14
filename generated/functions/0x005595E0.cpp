// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005595E0 rf_vector3_zero_return_destination
// UNREALRED VERIFIED [renderer-mesh-20261028]: Writes three floatzeros at this+0/+4/+8 and returns this. This is an explicit zeroing helper; unlike no-op defaultvectorconstructor0x4F2700,it does initialize components.
float *__thiscall rf_vector3_zero_return_destination(float *this)
{
  *this = 0.0;
  *(this + 1) = 0.0;
  *(this + 2) = 0.0;
  return this;
}

