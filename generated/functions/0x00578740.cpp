// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578740 rf_bitmap_texture_add_reference_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): cdecl one32bit handle. Forwards unchanged to573CF0 backend-dispatched texture reference add,returns delegatedEAX. No own bitmap lookup,validation,CPU-pixel refcount change or scope guard.
int __cdecl rf_bitmap_texture_add_reference_adapter(unsigned int handle)
{
  return rf_bitmap_texture_add_reference_backend_dispatch(handle);
}

