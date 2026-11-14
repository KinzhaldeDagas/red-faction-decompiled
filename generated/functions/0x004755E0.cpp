// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004755E0 rf_item_pickup_multiplayer_powerup
// UNREALRED VERIFIED [item-pickups-20261028]: Resolves entity, player record via0x4DD720(entity handle), and item; any missing returns-1. Only MP mode==1 AND server authority==1 calls0x4AD040(player,powerup ID from0x4ACFF0(item+668),1000*item quantity+676). Player-flagged entity gets pickup message regardless of authority. Returns0 after resolutions; no powerup application in non-MP path here.
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Powerup callback requires actual player-record resolution4DD720 even for non-player-flag entities. Missing entry returns-1. Only actual MPmode1 and serverauthority1 applies4AD040 to duration wrapping32(1000*raw item+676 quantity), using class-string4ACFF0. Five startup names bind first ordinal. Do not fabricate native player-record ownership from a host AI controller.
int __cdecl rf_item_pickup_multiplayer_powerup(int a1, int a2, int a3)
{
  int v4; // eax
  int v5; // [esp-4h] [ebp-10h]
  int v6; // [esp+0h] [ebp-Ch]
  int v7; // [esp+4h] [ebp-8h]
  _DWORD *v8; // [esp+8h] [ebp-4h]

  v7 = rf_entity_resolve_handle(a1);
  if ( !v7 )
    return -1;
  v8 = sub_4DD720(a1);
  if ( !v8 )
    return -1;
  v6 = rf_item_resolve_handle(a2);
  if ( !v6 )
    return -1;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v5 = 1000 * *(_DWORD *)(v6 + 676);
    v4 = sub_4ACFF0(v6 + 668);
    rf_powerup_apply_or_refresh_player_kind((int)v8, v4, v5);
  }
  if ( rf_object_has_player_flag(v7) )
    rf_item_show_local_pickup_message(v7, *(_DWORD *)(v6 + 660), a3, 0);
  return 0;
}

