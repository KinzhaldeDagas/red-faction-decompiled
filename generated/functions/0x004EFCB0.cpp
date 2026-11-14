// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EFCB0 rf_localization_store_literal_fallback_string
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, thermal renderer x87 branches, native stack aliases, localization pool writes and skin-profile selection): Cdecl source C string. Before validating capacity, writes cursor663044 to fallback table88C498[count88E3D8] and increments count, unchecked. Signed strlen compared to51200-(cursor-87FC98-1); length>=remaining returns0, retaining publication/count increment and leaving cursor unchanged. Success copies source INCLUDING terminating NUL byte without escape decoding, advances cursor by length+1, returns count-1. Zero is both valid first index and failure; no rollback, index cap, NULL/overflow or pool-reset logic.
int __cdecl rf_localization_store_literal_fallback_string(const char *a1)
{
  char v2; // al
  _BYTE *v3; // [esp+8h] [ebp-20h]
  const char *v4; // [esp+Ch] [ebp-1Ch]
  int v5; // [esp+20h] [ebp-8h]

  unk_88C498[unk_88E3D8++] = (int)off_663044;
  v5 = strlen(a1);
  if ( v5 >= 51200 - (off_663044 - &unk_87FC98 - 1) )
    return 0;
  v4 = a1;
  v3 = off_663044;
  do
  {
    v2 = *v4;
    *v3++ = *v4++;
  }
  while ( v2 );
  off_663044 = (_UNKNOWN *)((char *)off_663044 + v5 + 1);
  return unk_88E3D8 - 1;
}

