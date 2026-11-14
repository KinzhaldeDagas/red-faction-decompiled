// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059F110 rf_vpackfile_find_archive_record_case_insensitive
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl archive name. Linear scan of rf_vpackfile_count mounted records at rf_vpackfiles with176-byte stride; stricmp against record name at0, returns first matching record pointer or NULL. Does not open files, check archive validity, normalize path separators or validate input NULL/count. Same archive-name lookup used by59F410 whole-archive read.
char *__cdecl rf_vpackfile_find_archive_record_case_insensitive(char *String1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_vpackfile_count; ++i )
  {
    if ( !_stricmp(String1, &rf_vpackfiles[176 * i]) )
      return &rf_vpackfiles[176 * i];
  }
  return nullptr;
}

