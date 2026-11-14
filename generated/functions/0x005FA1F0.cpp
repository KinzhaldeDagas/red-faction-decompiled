// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FA1F0 rf_bluebeard_metadata_scan_from_cursor
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Internal no-arg scan.4096 records stride180 at0x1F6D330;active flag DWORDrecord+172 bit0x10000000. Filter group index0x1F6D24C<0 disables filter,else compares record+120 string against40-byte group-name slot case-insensitively. Starts at global signed cursor0x2021330;first active matching record returns borrowed pointer,sets cursor=i+1 or-1 wheni4095. No match by4096 returnsNULL WITHOUT changing cursor. No guard for negative starting cursor/group index>=256;public next wrapper0x5FA2C0 prevents negative cursor entry. No mutation of records/refcounts.
char *rf_bluebeard_metadata_scan_from_cursor()
{
  const char *v1; // [esp+0h] [ebp-Ch]
  int i; // [esp+8h] [ebp-4h]

  if ( dword_1F6D24C < 0 )
    v1 = nullptr;
  else
    v1 = &unk_1F6A968[40 * dword_1F6D24C];
  for ( i = dword_2021330; ; ++i )
  {
    if ( i >= 4096 )
      return nullptr;
    if ( (unk_1F6D3DC[45 * i] & 0x10000000) != 0 && (!v1 || !_stricmp((const char *)&unk_1F6D3A8 + 180 * i, v1)) )
      break;
  }
  dword_2021330 = i + 1;
  if ( i + 1 >= 4096 )
    dword_2021330 = -1;
  return (char *)&unk_1F6D330 + 180 * i;
}

