// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00491360 rf_lag_compensation_record424_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Thiscall424-byte snapshot record,returns receiver. Calls no-op vector8,matrix20 constructors and physics_state_construct_empty_sphere_collection(receiver56). Physics delegate
// initializes ONLY its array header at252/256/260,thus snapshot308/312/316=count0/capacity0/baseNULL; other physical matrices/vectors/scalars/contact remain untouched. In particular
// snapshot matrix208 is NOT zero/identity initialized. Static constructor62C3C0 invokes EH vector construction for32 records,stride424,base754158,with491390 destructor callback. No
// record handle/model/sample zeroing.
char *__thiscall rf_lag_compensation_record424_construct(char *this)
{
  rf_vector3_default_construct_noop(this + 8);
  rf_matrix3_construct(this + 20);
  rf_physics_state_construct_empty_sphere_collection(this + 56);
  return this;
}

