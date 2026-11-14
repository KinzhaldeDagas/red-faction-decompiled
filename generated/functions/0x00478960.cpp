// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00478960 rf_push_region_snapshot_restore
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] For each existing push region, find first saved key matching region+4, copy raw byte entry+4 to region+0x68. Missing match leaves state unchanged. No region deletion/recreation, geometry query or bool normalization.
int __cdecl rf_push_region_snapshot_restore(int a1, int a2)
{
  int result; // eax
  int j; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(rf_push_region_registry);
    if ( i >= result )
      break;
    for ( j = 0; j < a2; ++j )
    {
      if ( *(_DWORD *)(*(_DWORD *)sub_552200(rf_push_region_registry, i) + 4) == *(_DWORD *)(a1 + 8 * j) )
      {
        *(_BYTE *)(*(_DWORD *)sub_552200(rf_push_region_registry, i) + 104) = *(_BYTE *)(a1 + 8 * j + 4);
        break;
      }
    }
  }
  return result;
}

