// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005397A0 rf_dual_array28_destroy_members
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Destroys backing storage for member header+16 FIRST,then+4 via47A3F0. Does not free pointed elements,zero headers/prefix or free receiver. Repeated destruction unsafe unless caller resets dangling pointers.
void __thiscall rf_dual_array28_destroy_members(void **this)
{
  rf_pointer_array_destroy_backing_storage(this + 4);
  rf_pointer_array_destroy_backing_storage(this + 1);
}

