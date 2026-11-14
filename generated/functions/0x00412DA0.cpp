// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00412DA0 rf_physics_state_construct_empty_sphere_collection
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): Thiscall physics-state P (object+136),no stackargs. Calls no-op matrix constructors at20/56/116/152,vector constructors at92/104/188/200/212/224/236/264/276,and no-op68-byte contact constructor300. Initializes array24 headerP252/P256/P260 to count0/capacity0/baseNULL by4133B0(P252,0). Those THREE header DWORDs are the ONLY persistent receiver writes. Matrices/velocities/bounds/contact,flags288,time296 andscalar fields remain uninitialized. ReturnsP;no live-storage release before overwriting array header. In local motion-buffer snapshot this does NOT initialize matrixP152 subsequently read by restore;constructor calls are not zero initialization.
char *__thiscall rf_physics_state_construct_empty_sphere_collection(char *this)
{
  rf_matrix3_construct(this + 20);
  rf_matrix3_construct(this + 56);
  rf_vector3_default_construct_noop(this + 92);
  rf_vector3_default_construct_noop(this + 104);
  rf_matrix3_construct(this + 116);
  rf_matrix3_construct(this + 152);
  rf_vector3_default_construct_noop(this + 188);
  rf_vector3_default_construct_noop(this + 200);
  rf_vector3_default_construct_noop(this + 212);
  rf_vector3_default_construct_noop(this + 224);
  rf_vector3_default_construct_noop(this + 236);
  rf_array24_construct_capacity(this + 252, 0);
  rf_vector3_default_construct_noop(this + 264);
  rf_vector3_default_construct_noop(this + 276);
  rf_physics_hit_record_construct_noop(this + 300);
  return this;
}

