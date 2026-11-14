// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EF970 rf_localization_store_escaped_string
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, thermal renderer x87 branches, native stack aliases, localization pool writes and skin-profile selection): Cdecl source C string,index. Snapshots shared cursor663044; for signed index>=0 stores cursor into table88D438[index] BEFORE capacity check, with no upper bound. Computes signed source strlen and remaining=51200-(cursor-87FC98-1) with32-bit arithmetic; length>=remaining returnsNULL, leaving any published table pointer and cursor unchanged. Copies non-NUL input bytes, replacing literal backslash+n with byte10; backslash+v with at least five source bytes consumes next three chars via atoi and writes low byte (no digit validation, possiblyNUL), otherwise copies literal byte. CRITICAL: exit on source NUL DOES NOT write a destination terminator; relies on existing buffer contents. Advances shared cursor by ORIGINAL
// source length+1, not decoded output length, returns original cursor. No NULL guard, rollback, output initialization or decoded-length compaction. Pool base87FC98 and nominal size51200; subtracting an extra1 makes available check one byte more permissive than conventional len+1<=capacity-used.
_BYTE *__cdecl rf_localization_store_escaped_string(const char *a1, int a2)
{
  char v3; // al
  char String[4]; // [esp+20h] [ebp-18h] BYREF
  _BYTE *v5; // [esp+24h] [ebp-14h]
  _BYTE *v6; // [esp+28h] [ebp-10h]
  const char *v7; // [esp+2Ch] [ebp-Ch]
  signed int v8; // [esp+30h] [ebp-8h]
  int v9; // [esp+34h] [ebp-4h]

  v6 = off_663044;
  if ( a2 >= 0 )
    unk_88D438[a2] = (int)v6;
  v8 = strlen(a1);
  v9 = 51200 - (off_663044 - &unk_87FC98 - 1);
  if ( v8 >= v9 )
    return nullptr;
  v7 = a1;
  v5 = v6;
  while ( *v7 )
  {
    if ( *v7 == 92 && v7[1] == 110 )
    {
      *v5 = 10;
      v7 += 2;
    }
    else if ( *v7 == 92 && v7[1] == 118 && strlen(v7) >= 5 )
    {
      String[0] = v7[2];
      String[1] = v7[3];
      String[2] = v7[4];
      String[3] = 0;
      v3 = atoi(String);
      *v5 = v3;
      v7 += 5;
    }
    else
    {
      *v5 = *v7++;
    }
    ++v5;
  }
  off_663044 = (_UNKNOWN *)((char *)off_663044 + v8 + 1);
  return v6;
}

