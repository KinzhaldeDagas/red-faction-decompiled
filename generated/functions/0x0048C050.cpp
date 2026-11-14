// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048C050 rf_common_derived_destroy_base_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, glare visibility/reflection and cached-query initialization, native flags/x87 gates and static ownership): Thiscall derived/common receiver, no stack args. Only calls common-object embedded-member destructor0x412580, destroying nested physics-array member+136 and RFString+24. No extra vector/timestamp destruction, scene/list unlink, bitmap/solid deletion or outer allocation free. Used by physical-debris and glare STATIC sentinel atexit adapters; does not drain either runtime list.
void __thiscall rf_common_derived_destroy_base_members(void *this)
{
  rf_common_object_destroy_embedded_members((int)this);
}

