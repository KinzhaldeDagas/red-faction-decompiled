// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00513BA0 rf_shadow_projector276_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Thiscall276-byte shadow-projector receiver,no stack args,returns receiver. Calls six16-byte plane-prefix constructors0..95; vector defaults96,108,120; four12-byte vectors132..179; matrix constructor180..215; vectors216,228,240. All underlying vector/plane-prefix/matrix defaults are verified NO-OPs. Therefore initializes NO receiver bytes,including scalar tail252..271 andDWORD272;does not initialize identity,zero planes,extent or ownership. Used by projected-shadow builder512Dxx; subsequent setup supplies actual values.
char *__thiscall rf_shadow_projector276_construct_noop(char *this)
{
  rf_vector_construct_no_unwind(this, 0x10u, 6, rf_vector_prefix_construct_noop);
  rf_vector3_default_construct_noop(this + 96);
  rf_vector3_default_construct_noop(this + 108);
  rf_vector3_default_construct_noop(this + 120);
  rf_vector_construct_no_unwind(this + 132, 0xCu, 4, rf_vector3_default_construct_noop);
  rf_matrix3_construct(this + 180);
  rf_vector3_default_construct_noop(this + 216);
  rf_vector3_default_construct_noop(this + 228);
  rf_vector3_default_construct_noop(this + 240);
  return this;
}

