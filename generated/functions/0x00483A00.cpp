// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00483A00 rf_push_region_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL region-version layouts, cutscene stream ABI and count bounds, constructor/destructor ownership and debris descriptor bits): 
// Thiscall push-region constructor, returns receiver. No-op vectors12,64,76,88 and no-op matrix constructor24. Does not initialize id/type/flags at0..11, shape-specific
// scalar60,strength100, matrix/position, or remaining payload. Used by RFL push-region loader; concrete authored fields and owning registry are assigned by that caller, not defaults
// here.
char *__thiscall rf_push_region_construct_noop(char *this)
{
  rf_vector3_default_construct_noop(this + 12);
  rf_matrix3_construct(this + 24);
  rf_vector3_default_construct_noop(this + 64);
  rf_vector3_default_construct_noop(this + 76);
  rf_vector3_default_construct_noop(this + 88);
  return this;
}

