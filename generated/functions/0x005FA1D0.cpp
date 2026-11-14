// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FA1D0 rf_bluebeard_metadata_first
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Recovered no-arg function0x5FA1D0..0x5FA1E4. Sets global iteration cursor0x2021330=0,then returns internal scan0x5FA1F0. Preserves current group filter and record contents. Borrowed record pointer orNULL;not thread-safe per shared cursor.
void *__cdecl rf_bluebeard_metadata_first()
{
  dword_2021330 = 0;
  return rf_bluebeard_metadata_scan_from_cursor();
}

