// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FA0E0 rf_bluebeard_metadata_add_group_name
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl NULstring. Table0x1F6A968 has256 slots stride40,count0x1F6D16C. Rejects count>=256 OR strlen>=39,so maximum accepted length38,returns-1. Case-insensitive duplicate scan also returns-1 (does NOT return existing index). Copies accepted spelling,NUL unbounded only after length gate,returns old count thenincrements. Empty name accepted once. No NULL/negative-count guard;used by bluebeard.bty sound metadata loader0x5FA580.
int __cdecl rf_bluebeard_metadata_add_group_name(char *String2)
{
  char v2; // al
  char *v3; // [esp+8h] [ebp-1Ch]
  char *v4; // [esp+Ch] [ebp-18h]
  int i; // [esp+20h] [ebp-4h]

  if ( dword_1F6D16C >= 256 || strlen(String2) >= 0x27 )
    return -1;
  for ( i = 0; i < dword_1F6D16C; ++i )
  {
    if ( !_stricmp(&unk_1F6A968[40 * i], String2) )
      return -1;
  }
  v4 = String2;
  v3 = &unk_1F6A968[40 * dword_1F6D16C];
  do
  {
    v2 = *v4;
    *v3++ = *v4++;
  }
  while ( v2 );
  return dword_1F6D16C++;
}

