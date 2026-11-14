// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589FC0 rf_v3c_get_collision_sphere_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Returns descriptor integer DWORD+96; no mutation or bounds validation.
int __thiscall rf_v3c_get_collision_sphere_count(const void *this)
{
  return *((_DWORD *)this + 24);
}

