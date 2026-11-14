// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FA2C0 rf_bluebeard_metadata_next
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Recovered no-arg function0x5FA2C0..0x5FA2D7. If signed cursor0x2021330>=0 returns internal scan0x5FA1F0,elseNULL. Does not increment cursor itself,reset filter or alter record state. Guard prevents scanner reading index-1 after end sentinel.
void *__cdecl rf_bluebeard_metadata_next()
{
  if ( dword_2021330 >= 0 )
    return rf_bluebeard_metadata_scan_from_cursor();
  else
    return nullptr;
}

