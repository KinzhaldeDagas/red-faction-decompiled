// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589EE0 rf_v3c_collision_sphere_record_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Constructor for44-byte collision-sphere record calls no-op vector constructor at position+28 and returns this. Does not initialize name, integer+24, position contents or radius+40.
char *__thiscall rf_v3c_collision_sphere_record_construct(char *this)
{
  rf_vector3_default_construct_noop(this + 28);
  return this;
}

