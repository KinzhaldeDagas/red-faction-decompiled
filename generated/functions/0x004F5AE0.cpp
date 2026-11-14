// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F5AE0 rf_level_state_cache_capture_current
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Set shared-goal omission flag0x88E7CC=1. Empty cache initializes header words83544,65545 and current index-1. Count<4 immediately captures current level through0x4F5D70. Otherwise current-level name already cached avoids eviction; absent name selects first cached level not listed in matching164-byte adjacency rule, compacts100128-byte blocks/32-byte names and decrements count before capture. Candidate defaults-1 and no explicit found-index guard precedes compaction loop. No cache reset after capture, player-subrecord write or disk I/O in this function.
char rf_level_state_cache_capture_current()
{
  const char *v1; // eax
  const char *v2; // eax
  char v3; // [esp+3h] [ebp-31h]
  char *v4; // [esp+8h] [ebp-2Ch]
  char *v5; // [esp+Ch] [ebp-28h]
  int m; // [esp+10h] [ebp-24h]
  char v7; // [esp+17h] [ebp-1Dh]
  int k; // [esp+18h] [ebp-1Ch]
  int v9; // [esp+1Ch] [ebp-18h]
  int j; // [esp+20h] [ebp-14h]
  int n; // [esp+20h] [ebp-14h]
  char v12; // [esp+26h] [ebp-Eh]
  int i; // [esp+28h] [ebp-Ch]

  unk_88E7CC = 1;
  if ( !dword_894D40 )
  {
    unk_894D38[0] = 83544;
    unk_894D3C = 65545;
    unk_894DF4 = -1;
  }
  if ( dword_894D40 < 4 )
    return rf_level_state_cache_pack_current_level((int)unk_894D38);
  v12 = 0;
  for ( i = 0; i < dword_894D40; ++i )
  {
    v1 = rf_string_object_c_str_or_empty(unk_6FC31C);
    if ( !_stricmp((const char *)&unk_894D38[8 * i + 3], v1) )
    {
      v12 = 1;
      break;
    }
  }
  if ( !v12 )
  {
    v9 = -1;
    for ( j = 0; j < unk_890500; ++j )
    {
      v2 = rf_string_object_c_str_or_empty(unk_6FC31C);
      if ( !_stricmp((const char *)&unk_890508 + 164 * j, v2) )
      {
        for ( k = 0; k < dword_894D40; ++k )
        {
          v7 = 0;
          for ( m = 0; m < unk_890528[41 * j]; ++m )
          {
            if ( !_stricmp((const char *)&unk_894D38[8 * k + 3], &unk_89052C[164 * j + 32 * m]) )
            {
              v7 = 1;
              break;
            }
          }
          if ( !v7 )
          {
            v9 = k;
            goto LABEL_26;
          }
        }
        break;
      }
    }
LABEL_26:
    for ( n = v9; n < dword_894D40 - 1; ++n )
    {
      memcpy((char *)&unk_8A9390 + 100128 * n, (char *)&unk_8A9390 + 100128 * n + 100128, 0x18720u);
      v5 = &unk_894D44[32 * n + 32];
      v4 = &unk_894D44[32 * n];
      do
      {
        v3 = *v5;
        *v4++ = *v5++;
      }
      while ( v3 );
    }
    --dword_894D40;
  }
  return rf_level_state_cache_pack_current_level((int)unk_894D38) != 0;
}

