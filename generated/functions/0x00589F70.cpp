// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589F70 rf_v3c_get_collision_spheres_with_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Writes descriptor count+96 through589FC0, returns pointer+100 through589FA0. Source records have44-byte stride and are read by CSPH dispatch. No allocation, validation or ownership transfer.
void *__thiscall rf_v3c_get_collision_spheres_with_count(const void *this, int *a2)
{
  *a2 = rf_v3c_get_collision_sphere_count(this);
  return rf_v3c_get_collision_sphere_records(this);
}

