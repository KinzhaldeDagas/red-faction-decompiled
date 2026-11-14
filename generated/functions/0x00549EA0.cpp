// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00549EA0 rf_float4_construct_components_after_vector_noop
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Calls no-op vector3 default on receiver,then writes four supplied scalar floats at0,4,8,12,returns receiver. No normalization,allocation,sign/default-component conversion. Vector no-op does not initialize any additional bytes.
float *__thiscall rf_float4_construct_components_after_vector_noop(float *this, float a2, float a3, float a4, float a5)
{
  rf_vector3_default_construct_noop(this);
  *this = a2;
  *(this + 1) = a3;
  *(this + 2) = a4;
  *(this + 3) = a5;
  return this;
}

