// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041F100 rf_record24_copy_construct_six_floats
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Thiscall destination plus source pointer,RET4,returns destination. Copy-constructs first vec3 via0x40CE30, then individually FLD/FSTP source offsets12,16,20. All24 bytes copied as six float values, not raw memcpy; signaling-NaN conversion/exceptions and arbitrary partial overlap follow native helper/store order. No default radius/tail initialization, allocation or pointer guard.
float *__thiscall rf_record24_copy_construct_six_floats(float *this, float *a2)
{
  rf_vector3_copy_return_destination(this, a2);
  *(this + 3) = a2[3];
  *(this + 4) = a2[4];
  *(this + 5) = a2[5];
  return this;
}

