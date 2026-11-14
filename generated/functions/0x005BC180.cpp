// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BC180 rf_text_file_create_writer
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, buffered text reader/writer branches, allocation callers and original-PE newline literal): Allocates28-byte object, initializes FILE*/buffer via5BBB50, calls write-open(path,appendByte,stdioBufferSize). Success0 returns object; failure calls scalar deleting destructor490340(flags1),returnsNULL. Binary append/truncate selected by nonzero/zero byte. Used by banlist export; no validation of path/size,flush or extra error reporting.
_DWORD *__cdecl rf_text_file_create_writer(char *FileName, char a2, size_t Size)
{
  _DWORD *v4; // [esp+8h] [ebp-24h]
  _DWORD *v5; // [esp+14h] [ebp-18h]

  v5 = operator new(0x1Cu);
  if ( v5 )
    v4 = rf_text_file_construct(v5);
  else
    v4 = nullptr;
  if ( !v4 )
    return nullptr;
  if ( !rf_text_file_open_write(v4, FileName, a2, Size) )
    return v4;
  rf_text_file_scalar_deleting_destructor(v4, 1);
  return nullptr;
}

