// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00582330 rf_float4_construct_zero_zero_zero_one
// UNREALRED VERIFIED [transfer-scene-20261028]: Thiscall writes four consecutive floats (0,0,0,1), returns destination. No allocation or normalization. Used as a four-component scene transform member constructor.
float *__thiscall rf_float4_construct_zero_zero_zero_one(float *this)
{
  *this = 0.0;
  *(this + 1) = 0.0;
  *(this + 2) = 0.0;
  *(this + 3) = 1.0;
  return this;
}

