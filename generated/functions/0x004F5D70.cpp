// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F5D70 rf_level_state_cache_pack_current_level
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Header parameter: case-insensitive lookup current level in count+8, names at+12 stride32. Append uncapped C string and increment count when missing; set current index+188. Level block=header+83544+100128*index; copy current level name, raw shared seconds to block+36, size100128 to block+32, header countdown+196, clear48-byte music-name field+62184, then collect runtime snapshot. Return1 after capture. No local four-slot capacity check, disk write, player/persona snapshot or shared-goal omission-flag change.
char __cdecl rf_level_state_cache_pack_current_level(int a1)
{
  const char *v1; // eax
  char v3; // [esp+3h] [ebp-29h]
  _BYTE *v4; // [esp+8h] [ebp-24h]
  const char *v5; // [esp+Ch] [ebp-20h]
  char v6; // [esp+13h] [ebp-19h]
  _BYTE *v7; // [esp+18h] [ebp-14h]
  const char *v8; // [esp+1Ch] [ebp-10h]
  int v9; // [esp+20h] [ebp-Ch]
  int i; // [esp+24h] [ebp-8h]
  int v11; // [esp+28h] [ebp-4h]

  v9 = -1;
  for ( i = 0; i < *(_DWORD *)(a1 + 8); ++i )
  {
    v1 = rf_string_object_c_str_or_empty(unk_6FC31C);
    if ( !_stricmp(v1, (const char *)(a1 + 32 * i + 12)) )
    {
      v9 = i;
      break;
    }
  }
  if ( v9 == -1 )
  {
    v8 = rf_string_object_c_str_or_empty(unk_6FC31C);
    v7 = (_BYTE *)(a1 + 32 * *(_DWORD *)(a1 + 8) + 12);
    do
    {
      v6 = *v8;
      *v7++ = *v8++;
    }
    while ( v6 );
    *(_DWORD *)(a1 + 188) = (*(_DWORD *)(a1 + 8))++;
  }
  else
  {
    *(_DWORD *)(a1 + 188) = v9;
  }
  v11 = a1 + 100128 * *(_DWORD *)(a1 + 188) + 83544;
  v5 = rf_string_object_c_str_or_empty(unk_6FC31C);
  v4 = (_BYTE *)v11;
  do
  {
    v3 = *v5;
    *v4++ = *v5++;
  }
  while ( v3 );
  *(float *)(v11 + 36) = *(float *)&dword_6FC428;
  *(float *)(a1 + 196) = rf_mission_countdown_remaining_seconds;
  memset((void *)(a1 + 62184), 0, 0x30u);
  *(_DWORD *)(v11 + 32) = 100128;
  rf_level_state_collect_runtime_snapshot((_BYTE *)v11);
  return 1;
}

