// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F6D0 rf_string_destroy_buffer
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Thiscall no-stack-argument wrapper around55F580. Frees owned buffer when non-NULL and clears pointer; stored extent remains unchanged. Does not delete the containing two-DWORD object.
void __thiscall rf_string_destroy_buffer(_DWORD *this)
{
  rf_string_release_buffer_keep_extent(this);
}

