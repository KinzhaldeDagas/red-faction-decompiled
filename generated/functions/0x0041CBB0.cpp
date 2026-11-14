// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041CBB0 rf_glare_runtime_construct_common_and_vector_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, glare visibility/reflection and cached-query initialization, native flags/x87 gates and static ownership): Thiscall glare receiver. Calls common-object member constructor, then no-write vector default constructors at+704,+724,+736, returns receiver. Thus no glare-specific payload bytes are initialized by these vector calls; only common RFString+24 and physics-array header+388 are effectively initialized by base. No timestamp+676 construction here, no enabled/cache byte defaults or list/definition setup. Original startup0x629AA8 calls this on glare sentinel0x680AE8; separate0x419630 is physical-debris sentinel constructor.
char *__thiscall rf_glare_runtime_construct_common_and_vector_members(char *this)
{
  rf_common_object_construct_members(this);
  rf_vector3_default_construct_noop(this + 704);
  rf_vector3_default_construct_noop(this + 724);
  rf_vector3_default_construct_noop(this + 736);
  return this;
}

