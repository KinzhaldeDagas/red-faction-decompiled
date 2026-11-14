// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589EB0 rf_v3c_aux_transform_record_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Constructor for100-byte auxiliary transform record: writes quaternion(0,0,0,1) at+68 through float4 helper and calls no-op vector constructor at+84. Returns this. Name/header fields, translation bytes and other fields are not initialized here.
float *__thiscall rf_v3c_aux_transform_record_construct(float *this)
{
  rf_float4_construct_zero_zero_zero_one(this + 17);
  rf_vector3_default_construct_noop(this + 21);
  return this;
}

