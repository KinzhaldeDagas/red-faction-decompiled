// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00474BD0 rf_item_pickup_medical_kit
// UNREALRED VERIFIED [item-pickups-20261028]: Shared Medical Kit/First Aid Kit callback. Resolves entity/item handles or returns-1. Single-player/MP server rejects life>=entity-definition max+68; MP client skips rejection/write. With multiplayer and splitscreen flags zero scales quantity by table0x661284[index0x6612A4], adds0.5 then truncates. Authority adds to life+52 and upper clamps; no lower clamp. Player-flagged entity gets quantity-based message. Returns0.
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Startup Medical Kit and First Aid Kit callback each first class row. SP/MPserver rejects life>=classMaxLife, then signed/scaled integer quantity converted into F32 life addition and upper clamp ONLY; negative quantity is not normalized or sent through native damage/death handlers here. SP health scale table661284, MP/split skip scaling.
// UNREALRED VERIFIED [combat-native-pickup-dependencies-20261111]: Medical callback uses same exact health scale661284 (2,1,.8f,.7f) with MP/split bothzero. Native signed addition/upper-only class maximum does not invoke damage/death machinery for negative quantity. The raw class-value availability must be known; generic partial-document default0 is not a proven native parsed cap.
int __cdecl rf_item_pickup_medical_kit(int a1, int a2, int a3)
{
  int v4; // [esp+0h] [ebp-8h]
  int v5; // [esp+4h] [ebp-4h]

  v5 = rf_entity_resolve_handle(a1);
  if ( !v5 )
    return -1;
  if ( (rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority)
    && *(float *)(*(_DWORD *)(v5 + 660) + 68) <= (double)*(float *)(v5 + 52) )
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
    *(float *)(v5 + 52) = (double)a3 + *(float *)(v5 + 52);
    if ( *(float *)(*(_DWORD *)(v5 + 660) + 68) < (double)*(float *)(v5 + 52) )
      *(float *)(v5 + 52) = *(float *)(*(_DWORD *)(v5 + 660) + 68);
  }
  if ( rf_object_has_player_flag(v5) )
    rf_item_show_local_pickup_message(v5, *(_DWORD *)(v4 + 660), a3, 0);
  return 0;
}

