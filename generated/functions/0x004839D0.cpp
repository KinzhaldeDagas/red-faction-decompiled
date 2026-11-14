// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004839D0 rf_world_obb_region_construct
// UNREALRED VERIFIED [level-lifecycle-20261028]: Calls no-op default vector constructor on record+4, matrix3 constructor on+16 and no-op vector constructor on+52, returns this. No explicit initialization of integer field+0 or vector components; loader fills them. Matrix initialization semantics belong to matrix constructor.
char *__thiscall rf_world_obb_region_construct(char *this)
{
  rf_vector3_default_construct_noop(this + 4);
  rf_matrix3_construct(this + 16);
  rf_vector3_default_construct_noop(this + 52);
  return this;
}

