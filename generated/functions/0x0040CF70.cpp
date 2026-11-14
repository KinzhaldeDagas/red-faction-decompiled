// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040CF70 rf_vector3_set_components_return_destination
// UNREALRED VERIFIED [renderer-mesh-20261028]: Writes three callerfloatcomponents into this+0/+4/+8 and returns this. No normalization,allocation or extra fields.
float *__thiscall rf_vector3_set_components_return_destination(float *this, float a2, float a3, float a4)
{
  *this = a2;
  *(this + 1) = a3;
  *(this + 2) = a4;
  return this;
}

