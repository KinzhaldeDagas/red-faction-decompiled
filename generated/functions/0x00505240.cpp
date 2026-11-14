// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00505240 rf_trigger_weapon_point_scan_all
// UNREALRED VERIFIED [event-item-dispatch-20261028]: Rejects multiplayer-runtime mode==1 without server authority. Otherwise traverses every trigger from runtime list head to sentinel0x90B510 using next+652; calls rf_trigger_weapon_point_activation(trigger,caller argument), returns true if any call returns exactly1. Does not stop after first hit. Hex-Rays exposes an x87 argument artifact; do not infer a public floating parameter solely from it.
char __cdecl rf_trigger_weapon_point_scan_all(float *a1)
{
  char v3; // al
  int i; // [esp+0h] [ebp-8h]
  char v5; // [esp+7h] [ebp-1h]

  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
    return 0;
  v5 = 0;
  for ( i = rf_trigger_runtime_list_head; (_UNKNOWN *)i != &unk_90B510; i = *(_DWORD *)(i + 652) )
  {
    rf_trigger_weapon_point_activation(i, a1);
    if ( v3 == 1 )
      v5 = 1;
  }
  return v5;
}

