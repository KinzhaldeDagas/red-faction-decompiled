// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00491340 rf_vector_prefix_construct_noop
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Calls no-op vector3 default on receiver,returns receiver. Consequently no member bytes initialized;used for plane/vertex/vector-prefix objects across callers,original C++ aggregate class unproven. Does not zero xyz,flags or scalar tail fields.
void *__thiscall rf_vector_prefix_construct_noop(void *this)
{
  rf_vector3_default_construct_noop(this);
  return this;
}

