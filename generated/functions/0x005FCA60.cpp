// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FCA60 rf_jpeg_write_tables
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcapimin.c:jpeg_write_tables matched): Recovered0x5FCA60..0x5FCAEE. Requiresstate100 elseerror20;resets error mgr,initializes destination,initializes markerwriter0x5FF3E0,write_tables_only callbackmarker+16,then term_destination. Does NOT jpeg_abort/freeimagepool afterward (v6b behavior),so tables/permanent config retained andmarker/destination work allocations persist until abort/fullcycle. Does not close FILE/change globalstate itself;APIvoid.
void __cdecl rf_jpeg_write_tables(void *cinfo)
{
  if ( *((_DWORD *)cinfo + 5) != 100 )
  {
    *(_DWORD *)(*(_DWORD *)cinfo + 20) = 20;
    *(_DWORD *)(*(_DWORD *)cinfo + 24) = *((_DWORD *)cinfo + 5);
    (**(void (__cdecl ***)(void *))cinfo)(cinfo);
  }
  (*(void (__cdecl **)(void *))(*(_DWORD *)cinfo + 16))(cinfo);
  (*(void (__cdecl **)(void *))(*((_DWORD *)cinfo + 6) + 8))(cinfo);
  rf_jpeg_jinit_marker_writer((int)cinfo);
  (*(void (__cdecl **)(void *))(*((_DWORD *)cinfo + 86) + 16))(cinfo);
  (*(void (__cdecl **)(void *))(*((_DWORD *)cinfo + 6) + 16))(cinfo);
}

