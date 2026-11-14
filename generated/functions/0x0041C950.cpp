// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041C950 rf_solid_collision_query_construct_clear_face_hint
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shape-sphere/model/solid sweeps, x87 unordered gates, descriptor constructors and native output mutation): Thiscall receiver,no stack arguments. Calls no-op vector constructors at4,52,64,84,96 and no-op matrix constructor at16; ONLY memory write is DWORD0=0 (cached face hint), then returns receiver. Leaves pose,segment,radius76,flags80 and work vectors unchanged/uninitialized. Does not set identity,clear whole108-byte query or initialize flags. No own NULL guard.
char *__thiscall rf_solid_collision_query_construct_clear_face_hint(char *this)
{
  rf_vector3_default_construct_noop(this + 4);
  rf_matrix3_construct(this + 16);
  rf_vector3_default_construct_noop(this + 52);
  rf_vector3_default_construct_noop(this + 64);
  rf_vector3_default_construct_noop(this + 84);
  rf_vector3_default_construct_noop(this + 96);
  *(_DWORD *)this = 0;
  return this;
}

