// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BC0B0 rf_text_file_create_reader
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, buffered text reader/writer branches, allocation callers and original-PE newline literal): Allocates28-byte object with operator new, invokes constructor5BBB50 (only FILE*/buffer initialized), calls read-open(path,capacity). Open status0 returns object; failure invokes scalar deleting destructor490340(flags1) then returnsNULL. No image xrefs observed,which does not prove dead code. No minimum buffer size or allocation exception translation.
_DWORD *__cdecl rf_text_file_create_reader(char *FileName, size_t Size)
{
  _DWORD *v3; // [esp+8h] [ebp-24h]
  _DWORD *v4; // [esp+14h] [ebp-18h]

  v4 = operator new(0x1Cu);
  if ( v4 )
    v3 = rf_text_file_construct(v4);
  else
    v3 = nullptr;
  if ( !v3 )
    return nullptr;
  if ( !rf_text_file_open_read(v3, FileName, Size) )
    return v3;
  rf_text_file_scalar_deleting_destructor(v3, 1);
  return nullptr;
}

