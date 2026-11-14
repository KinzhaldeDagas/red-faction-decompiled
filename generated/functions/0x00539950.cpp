// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539950 rf_uv_scroll_descriptor_destroy
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Destroys member DWORD/pointer-array backing at descriptor+12 through destructor-style helper47A3F0;does not free associated face objects or descriptor itself. Header count/capacity/backing left unchanged,so not a reusable clear/reset;no velocity/key writes.
void __thiscall rf_uv_scroll_descriptor_destroy(void **this)
{
  rf_pointer_array_destroy_backing_storage(this + 3);
}

