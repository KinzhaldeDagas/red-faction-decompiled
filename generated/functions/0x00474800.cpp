// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00474800 rf_item_pickup_miner_envirosuit
// UNREALRED VERIFIED [item-pickups-20261028]: Arguments entity handle,item handle,quantity. Missing entity/item returns-1. In single-player or MP server rejects armor>=definition max(+72), then sets armor+56 to that maximum. MP client skips both full-armor rejection and armor write. Player-flagged entity gets pickup message with original quantity. Returns0 on accepted path; no item deletion here.
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Startup Miner Envirosuit callback only first class row: SP/MPserver rejects full armor then sets exact classMaxArmor. No signed-quantity addition or generic partial repair behavior. Missing owner/item is-1.
int __cdecl rf_item_pickup_miner_envirosuit(int a1, int a2, int a3)
{
  int v4; // [esp+0h] [ebp-8h]
  int v5; // [esp+4h] [ebp-4h]

  v5 = rf_entity_resolve_handle(a1);
  if ( !v5 )
    return -1;
  if ( (rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority)
    && *(float *)(*(_DWORD *)(v5 + 660) + 72) <= (double)*(float *)(v5 + 56) )
  {
    return -1;
  }
  v4 = rf_item_resolve_handle(a2);
  if ( !v4 )
    return -1;
  if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
    *(float *)(v5 + 56) = *(float *)(*(_DWORD *)(v5 + 660) + 72);
  if ( rf_object_has_player_flag(v5) )
    rf_item_show_local_pickup_message(v5, *(_DWORD *)(v4 + 660), a3, 0);
  return 0;
}

