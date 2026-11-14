// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F5B0 rf_string_deallocate_buffer
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Thin cdecl wrapper calling operator delete with the provided buffer pointer. Used by string-buffer release; does not access or modify the two-DWORD string object itself. Inherited generic runtime label replaced from verified call target.
void __cdecl rf_string_deallocate_buffer(void *a1)
{
  operator delete(a1);
}

