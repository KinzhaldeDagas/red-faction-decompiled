// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059F410 rf_vpackfile_read_whole_archive_into_caller_buffer
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl caller buffer, signed capacity, mounted archive name. Finds record59F110; missing record or capacity<signed DWORD filesize at record+172 returns0. Opens physical record.path+32 in rb; fopen failure returns0. Otherwise fread(buffer,recordSize,1,FILE), ignores return entirely, closes and returns1 even for a short/error read. No VPP-member extraction, caller-buffer allocation, appended NUL or file-change size recheck. Capacity equality accepted; signed comparisons have no negative-size validation.57B1B0 uses this to install a shared archive buffer.
int __cdecl rf_vpackfile_read_whole_archive_into_caller_buffer(void *Buffer, int a2, char *String1)
{
  FILE *Stream; // [esp+0h] [ebp-8h]
  char *archive_record_case_insensitive; // [esp+4h] [ebp-4h]

  archive_record_case_insensitive = rf_vpackfile_find_archive_record_case_insensitive(String1);
  if ( !archive_record_case_insensitive )
    return 0;
  if ( a2 < *((_DWORD *)archive_record_case_insensitive + 43) )
    return 0;
  Stream = fopen(archive_record_case_insensitive + 32, "rb");
  if ( !Stream )
    return 0;
  fread(Buffer, *((_DWORD *)archive_record_case_insensitive + 43), 1u, Stream);
  fclose(Stream);
  return 1;
}

