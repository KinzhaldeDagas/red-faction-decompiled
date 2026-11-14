// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C5700 rf_geomod_impact_chunk_construct_members_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original fragment spawn and bounded pool, eight-vertex twelve-triangle layout, fourteen-ray scoring, full room-pointer ABI and native glass branching): 
// Thiscall chunk returns receiver. NOOP vec3 constructors at8(position),72(velocity),84(axis); matrix20 ctor calls three NOOP vec3 rows, RGBA64 ctorNOOP; iterator for eight12B
// vertices at124 via NOOP prefix ctor. No fields are explicitly initialized, including links0/4,radius56,bitmap68,budget100,owner104,room108,age112,lifetime116,flags120,triangle
// data220..651. No allocation/default identity or zeroing; pool init and spawn supply those writes separately.
char *__thiscall rf_geomod_impact_chunk_construct_members_noop(char *this)
{
  rf_vector3_default_construct_noop(this + 8);
  rf_matrix3_construct(this + 20);
  rf_rgba8_default_construct_noop(this + 64);
  rf_vector3_default_construct_noop(this + 72);
  rf_vector3_default_construct_noop(this + 84);
  rf_vector_construct_no_unwind(this + 124, 0xCu, 8, rf_vector_prefix_construct_noop);
  return this;
}

