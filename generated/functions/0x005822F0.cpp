// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005822F0 rf_affine_pair_default_construct_noop
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Calls no-op matrix3 constructor at0,vector3 at+36,matrix3 at+48,vector3 at+84;returns receiver. Layout suggests two contiguous48-byte affine prefixes,but no values initialized and exact original class role unproven. Does not create identity transforms,zero translations or allocate.
char *__thiscall rf_affine_pair_default_construct_noop(char *this)
{
  rf_matrix3_construct(this);
  rf_vector3_default_construct_noop(this + 36);
  rf_matrix3_construct(this + 48);
  rf_vector3_default_construct_noop(this + 84);
  return this;
}

