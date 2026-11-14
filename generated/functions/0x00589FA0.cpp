// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589FA0 rf_v3c_get_collision_sphere_records
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Returns descriptor pointer DWORD+100. Corrected old integer return representation to void pointer. Does not test count or pointer validity.
void *__thiscall rf_v3c_get_collision_sphere_records(const void *this)
{
  return *((void **)this + 25);
}

