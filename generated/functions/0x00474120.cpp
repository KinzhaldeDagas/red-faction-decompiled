// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00474120 rf_item_limit_dropped_population_update
// UNREALRED VERIFIED [item-pickups-20261028]: Only when global replicator0x6FAF30 has elapsed, rearms1500ms and chooses count limit10 if multiplayer OR splitscreen nonzero, otherwise6. If eligible candidate count>limit, selects oldest and starts fade through0x4741A0. At most one candidate per elapsed call. Returns incidental helper value, not stable boolean/count.
__int16 rf_item_limit_dropped_population_update()
{
  int oldest_dropped_fade_candidate; // eax
  int v2; // [esp+4h] [ebp-8h]

  LOWORD(oldest_dropped_fade_candidate) = rf_replicator_has_elapsed((int *)&unk_6FAF30);
  if ( (unsigned __int8)oldest_dropped_fade_candidate == 1 )
  {
    rf_replicator_arm_milliseconds((int *)&unk_6FAF30, 1500);
    if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
      v2 = 10;
    else
      v2 = 6;
    oldest_dropped_fade_candidate = rf_item_count_dropped_fade_candidates();
    if ( oldest_dropped_fade_candidate > v2 )
    {
      oldest_dropped_fade_candidate = rf_item_find_oldest_dropped_fade_candidate();
      if ( oldest_dropped_fade_candidate )
        LOWORD(oldest_dropped_fade_candidate) = rf_item_start_one_second_fade(oldest_dropped_fade_candidate);
    }
  }
  return oldest_dropped_fade_candidate;
}

