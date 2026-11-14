// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1410 rf_bolt_emitter_snapshot_restore
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Existing bolt emitters match first saved dword id against emitter+0; restore raw state byte+0x58 only. No unmatched deletion, emitter creation, immediate bolt regeneration or enabled-state API call.
int __cdecl rf_bolt_emitter_snapshot_restore(int a1, int a2)
{
  int result; // eax
  int v3; // [esp+4h] [ebp-Ch]
  int j; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(rf_bolt_emitter_registry);
    if ( i >= result )
      break;
    v3 = *(_DWORD *)sub_552200(rf_bolt_emitter_registry, i);
    for ( j = 0; j < a2; ++j )
    {
      if ( *(_DWORD *)(a1 + 8 * j) == *(_DWORD *)v3 )
      {
        *(_BYTE *)(v3 + 88) = *(_BYTE *)(a1 + 8 * j + 4);
        break;
      }
    }
  }
  return result;
}

