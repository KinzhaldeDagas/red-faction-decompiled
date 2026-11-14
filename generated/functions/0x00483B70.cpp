// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00483B70 rf_rfl_moving_group_member_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL region-version layouts, cutscene stream ABI and count bounds, constructor/destructor ownership and debris descriptor bits): 
// Thiscall moving-group member constructor, returns receiver. Calls no-op vector4,matrix16,vector88 constructors only. No initialization of id0,pose,intermediate scalars/flags52..87
// or vector88 payload. Caller is rf_rfl_moving_groups_section_load at480832; no extra semantics inferred from struct offset names.
char *__thiscall rf_rfl_moving_group_member_construct_noop(char *this)
{
  rf_vector3_default_construct_noop(this + 4);
  rf_matrix3_construct(this + 16);
  rf_vector3_default_construct_noop(this + 88);
  return this;
}

