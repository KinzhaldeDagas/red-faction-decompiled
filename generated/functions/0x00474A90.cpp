// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00474A90 rf_item_pickup_suit_repair
// UNREALRED VERIFIED [item-pickups-20261028]: Resolves entity/item handles or returns-1. In single-player or MP server rejects armor>=entity-definition max+72. If both multiplayer and splitscreen flags are zero, quantity becomes trunc(quantity*float_table0x661284[index0x6612A4]+0.5). Authority adds quantity to armor+56, upper clamps to definition max; no lower clamp. MP client performs no armor write. Player-flagged entity gets message with scaled quantity, even if actual gain was capped. Returns0.
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Startup Suit Repair callback is bound only to first class row. SP/MPserver rejects armor>=classMaxArmor; authority adds signed/scaled quantity to F32 armor then upper clamps ONLY. SP nonsplit scales with health/armor difficulty table661284; no lower floor. MPclient skips mutation. Native local-player message phase is separate.
// UNREALRED VERIFIED [combat-native-pickup-dependencies-20261111]: Health/armor scale661284 contains exact binary32(2.0,1.0,0.800000011920929,0.699999988079071); indexed by actual shared difficulty6612A4 only if MP/split bothzero. Integer quantity*floatScale+double0.5 goes to __ftol2_sse truncation, not RoundToInt or lower floor. Keep active class maximum and current native life/armor float stores distinct.
int __cdecl rf_item_pickup_suit_repair(int a1, int a2, int a3)
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
  if ( !rf_multiplayer_runtime_mode && !rf_splitscreen_runtime_active )
    a3 = (int)((double)a3 * flt_661284[dword_6612A4] + 0.5);
  if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
  {
    *(float *)(v5 + 56) = (double)a3 + *(float *)(v5 + 56);
    if ( *(float *)(*(_DWORD *)(v5 + 660) + 72) < (double)*(float *)(v5 + 56) )
      *(float *)(v5 + 56) = *(float *)(*(_DWORD *)(v5 + 660) + 72);
  }
  if ( rf_object_has_player_flag(v5) )
    rf_item_show_local_pickup_message(v5, *(_DWORD *)(v4 + 660), a3, 0);
  return 0;
}

