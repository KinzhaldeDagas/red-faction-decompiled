// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578760 rf_bitmap_texture_release_reference_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): cdecl one32bit handle. Forwards unchanged to573D20 backend-dispatched texture reference release,returns delegatedEAX. No added underflow/generation/ownership or suppression check;callee byte-ref wrap behavior preserved.
int __cdecl rf_bitmap_texture_release_reference_adapter(unsigned int handle)
{
  return rf_bitmap_texture_release_reference_backend_dispatch(handle);
}

