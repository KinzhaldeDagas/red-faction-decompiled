// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525FD0 rf_world_decal_record_construct_subobjects
// UNREALRED VERIFIED [decal-face-links-20261028]: Delegates default vector constructors at+0/+48/+188/+200, matrix constructor+12 and six16-byte plane subobjects at+92 through0x491340. Default vector constructor0x4F2700 is no-op, so this body does not zero vector data or initialize scalar/owner/list fields. Plane/matrix semantics belong to their helpers; returns this.
char *__thiscall rf_world_decal_record_construct_subobjects(char *this)
{
  rf_vector3_default_construct_noop(this);
  rf_matrix3_construct(this + 12);
  rf_vector3_default_construct_noop(this + 48);
  rf_vector_construct_no_unwind(this + 92, 0x10u, 6, rf_vector_prefix_construct_noop);
  rf_vector3_default_construct_noop(this + 188);
  rf_vector3_default_construct_noop(this + 200);
  return this;
}

