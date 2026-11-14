// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004126C0 rf_nav_node_destroy_array_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall object,no stack args. Releases dynamic backing at BYTE40 and112,then invokes backing destructors112 and40 again. No neighbor/pointed-object deletion or graph unlink;release helpers zero headers before repeated destruction. Does not free outer node. Used by scalar deleting adapter519210 and graph destruction519180;other object fields untouched.
void __thiscall rf_nav_node_destroy_array_members(void **this)
{
  rf_pointer_array_release_storage(this + 10);
  rf_pointer_array_release_storage(this + 28);
  rf_pointer_array_destroy_backing_storage(this + 28);
  rf_pointer_array_destroy_backing_storage(this + 10);
}

