// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00583C30 rf_quaternion_set_identity_return_this
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This float4 quaternion writes x=y=z=0,w=1,returns this. No allocation or normalization of old data. Used by scene transform state constructor;separate compiled helper from other float4 identity constructors.
float *__thiscall rf_quaternion_set_identity_return_this(float *this)
{
  *this = 0.0;
  *(this + 1) = 0.0;
  *(this + 2) = 0.0;
  *(this + 3) = 1.0;
  return this;
}

