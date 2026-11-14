// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C1AA0 rf_sound_preload_bluebeard_btz_list
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): When ready, opens <global path 189CD90>/bluebeard.btz in text mode, reads lines into a 256-byte buffer, removes a terminal LF, and searches already registered names case-insensitively. For an unmarked match, calls load_entry(index,0,1) and sets record byte +61 on nonnegative return; loader sets pin byte +63 when loading. Loops on !feof without checking fgets return; a failed read may reuse stale or uninitialized line data. Path sprintf is unbounded. Closes the stream at end; inferred FILE* return is incidental and is not a live stream.
FILE *rf_sound_preload_bluebeard_btz_list()
{
  FILE *result; // eax
  int name_case_insensitive; // [esp+10h] [ebp-214h]
  char String2; // [esp+14h] [ebp-210h] BYREF
  _BYTE v3[3]; // [esp+15h] [ebp-20Fh] BYREF
  int v4; // [esp+118h] [ebp-10Ch]
  char Buffer[256]; // [esp+11Ch] [ebp-108h] BYREF
  FILE *Stream; // [esp+220h] [ebp-4h]

  result = (FILE *)rf_sound_backend_ready;
  if ( rf_sound_backend_ready )
  {
    sprintf(Buffer, "%s\\bluebeard.btz", &unk_189CD90);
    result = fopen(Buffer, "r");
    Stream = result;
    if ( result )
    {
      while ( !feof(Stream) )
      {
        fgets(&String2, 256, Stream);
        v4 = &v3[strlen(&String2)] - v3;
        if ( *((_BYTE *)&name_case_insensitive + v4 + 3) == 10 )
          *((_BYTE *)&name_case_insensitive + v4 + 3) = 0;
        name_case_insensitive = rf_sound_resource_find_name_case_insensitive(&String2);
        if ( name_case_insensitive != -1
          && !unk_1D85DF5[64 * name_case_insensitive]
          && rf_sound_load_entry(name_case_insensitive, 0, 1) >= 0 )
        {
          unk_1D85DF5[64 * name_case_insensitive] = 1;
        }
      }
      return (FILE *)fclose(Stream);
    }
  }
  return result;
}

