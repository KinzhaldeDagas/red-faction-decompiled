// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00582360 rf_float4_construct_components
// UNREALRED VERIFIED [transfer-scene-20261028]: Thiscall destination and4 float arguments. Stores components in argument order at+0,+4,+8,+12 and returns destination. No allocation or normalization.
float *__thiscall rf_float4_construct_components(float *this, float a2, float a3, float a4, float a5)
{
  *this = a2;
  *(this + 1) = a3;
  *(this + 2) = a4;
  *(this + 3) = a5;
  return this;
}

