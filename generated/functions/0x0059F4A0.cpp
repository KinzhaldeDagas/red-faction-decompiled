// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059F4A0 rf_vpackfile_find_member_size_and_byte_offset
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, input remapping,text wrapping,Bink playback/default records,archive metadata,projection/aperture/classification and glass submission): Cdecl archiveName,memberName,outSize*,outByteOffset*,caller pops16 bytes. Resolves loaded archive case-insensitively; missing archive returns0 without output writes. Walks signed count at archive+164 over24-byte entries at table+168,first case-insensitive member match using filename pointer entry+4. On match stores entry DWORD12 to size,entry DWORD8 shifted left11 to byte offset(32-bit wrap),returns1. Missing member returns0 and preserves outputs. No archive open/read,seek,resource load,output-pointer check,overflow or entry-bound validation; offsets are2048-byte block units converted to bytes.
int __cdecl rf_vpackfile_find_member_size_and_byte_offset(char *a1, char *String1, _DWORD *a3, _DWORD *a4)
{
  int i; // [esp+0h] [ebp-8h]
  char *archive_record_case_insensitive; // [esp+4h] [ebp-4h]

  archive_record_case_insensitive = rf_vpackfile_find_archive_record_case_insensitive(a1);
  if ( !archive_record_case_insensitive )
    return 0;
  for ( i = 0; i < *((_DWORD *)archive_record_case_insensitive + 41); ++i )
  {
    if ( !_stricmp(String1, *(const char **)(*((_DWORD *)archive_record_case_insensitive + 42) + 24 * i + 4)) )
    {
      *a3 = *(_DWORD *)(*((_DWORD *)archive_record_case_insensitive + 42) + 24 * i + 12);
      *a4 = *(_DWORD *)(*((_DWORD *)archive_record_case_insensitive + 42) + 24 * i + 8) << 11;
      return 1;
    }
  }
  return 0;
}

