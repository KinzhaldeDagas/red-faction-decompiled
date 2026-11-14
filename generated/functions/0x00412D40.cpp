// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00412D40 rf_vector_bundle_construct_invalid_timestamp92
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): Thiscall receiver,no stackargs. Calls no-op vector constructors at offsets4,16,28,40,52,64;writes ONLY DWORD92=-1 via invalid timestamp constructor. Returns receiverEAX;does NOT zero vector components,field0,gaps or other scalar fields,query clock,allocate or validate pointer. Aggregate original C++ identity unproven;offset92 is4-byte timestamp,not a replicator object.
int *__thiscall rf_vector_bundle_construct_invalid_timestamp92(int *this)
{
  rf_vector3_default_construct_noop(this + 1);
  rf_vector3_default_construct_noop(this + 4);
  rf_vector3_default_construct_noop(this + 7);
  rf_vector3_default_construct_noop(this + 10);
  rf_vector3_default_construct_noop(this + 13);
  rf_vector3_default_construct_noop(this + 16);
  rf_timestamp4_construct_invalid(this + 23);
  return this;
}

