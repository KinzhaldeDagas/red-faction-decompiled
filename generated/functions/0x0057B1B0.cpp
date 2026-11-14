// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057B1B0 rf_text_parser_set_shared_archive_buffer
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl caller buffer, signed capacity, archive name. Null buffer clears global pointer189745C, capacity663F28=-1 and name first byte1897460=0, returns AL0. Nonnull buffer publishes pointer/capacity and unbounded-copies name, then59F410 reads whole named mounted archive from its physical path. Success returns AL1. On failure prints diagnostic, clears globals but does NOT explicitly set AL false: returns low byte of printf result, so return is not reliable boolean failure. No free/ownership transfer of caller buffer and no appended NUL. Nonzero global189745C also suppresses every parser-buffer free in579190; open578EA0 cached-read branch is ordinarily unreachable because local mode forced1.
char __cdecl rf_text_parser_set_shared_archive_buffer(void *Buffer, int a2, char *String1)
{
  int whole_archive_into_caller_buffer; // eax
  char v5; // [esp+3h] [ebp-Dh]
  char *v6; // [esp+8h] [ebp-8h]
  char *v7; // [esp+Ch] [ebp-4h]

  if ( Buffer )
  {
    unk_189745C = Buffer;
    dword_663F28 = a2;
    v7 = String1;
    v6 = &unk_1897460;
    do
    {
      v5 = *v7;
      *v6++ = *v7++;
    }
    while ( v5 );
    whole_archive_into_caller_buffer = rf_vpackfile_read_whole_archive_into_caller_buffer(Buffer, a2, String1);
    if ( !whole_archive_into_caller_buffer )
    {
      LOBYTE(whole_archive_into_caller_buffer) = printf(
                                                   "************************************************ ERROR BLASTING FILE INTO BUFFER!\n");
      unk_189745C = 0;
      dword_663F28 = -1;
      unk_1897460 = 0;
    }
  }
  else
  {
    unk_189745C = 0;
    dword_663F28 = -1;
    unk_1897460 = 0;
    LOBYTE(whole_archive_into_caller_buffer) = 0;
  }
  return whole_archive_into_caller_buffer;
}

