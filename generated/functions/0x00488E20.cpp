// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00488E20 rf_mover_hold_open_for_trigger
// UNREALRED VERIFIED [mission-mover-runtime-20261013] Door endpoint hold gate: only Waiting bit1 + door bit2 + forward bit0x2000 + mode!=1. Resolves stored triggering UID (+0x314) as trigger; tests active entities by point containment (or strict sphere distance), then corpses, scheduling corpse eviction when present. If occupied, caller rearms target-key wait without advancing to next segment. It is not a solid collision/sweep test.
// UNREALRED VERIFIED [mission-mover-occupancy-20261020] Open-wait occupancy first scans non-respawn-inactive entities; the first contained entity returns occupied without processing corpses. Only if no entity occupies does it scan ALL corpses, set occupied for every contained corpse, and call0x41E310 for each. Protected/already-retiring corpses still count as occupants; retirement eligibility is independent. Caller gates this path to expired waits on forward, door, non-mode1 linear movers.
// UNREALRED VERIFIED [mission-unhide-20261020] Endpoint occupancy scans living entities with the inactive filter, then separately scans corpses without that filter and queues intersecting corpses for retirement. UnrealRed preserves this corpse exception in IsMoverCorpseOccupant.
void __cdecl rf_mover_hold_open_for_trigger(_DWORD *a1)
{
  int j; // [esp+0h] [ebp-14h]
  int v3; // [esp+4h] [ebp-10h]
  int i; // [esp+8h] [ebp-Ch]
  float v5; // [esp+Ch] [ebp-8h]
  float v6; // [esp+Ch] [ebp-8h]
  char v7; // [esp+13h] [ebp-1h]

  v7 = 0;
  if ( (a1[198] & 1) != 0 && rf_mover_flag2_is_set((int)a1) && (a1[198] & 0x2000) != 0 && a1[186] != 1 )
  {
    v3 = rf_trigger_find_by_uid(a1[197]);
    if ( v3 )
    {
      for ( i = unk_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
      {
        if ( !rf_object_has_respawn_inactive_flag(i) )
        {
          if ( *(_DWORD *)(v3 + 660) == 1 )
          {
            if ( rf_oriented_box_contains_point(
                   (const float *)(i + 60),
                   (const float *)(v3 + 60),
                   (const float *)(v3 + 72),
                   (const float *)(v3 + 712)) )
            {
              v7 = 1;
              break;
            }
          }
          else
          {
            v5 = rf_vector_fast_distance((const float *)(i + 60), (const float *)(v3 + 60));
            if ( *(float *)(v3 + 120) > (double)v5 )
            {
              v7 = 1;
              break;
            }
          }
        }
      }
      if ( !v7 )
      {
        for ( j = rf_corpse_list_head; (_UNKNOWN *)j != &unk_681AF8; j = *(_DWORD *)(j + 652) )
        {
          if ( *(_DWORD *)(v3 + 660) == 1 )
          {
            if ( rf_oriented_box_contains_point(
                   (const float *)(j + 60),
                   (const float *)(v3 + 60),
                   (const float *)(v3 + 72),
                   (const float *)(v3 + 712)) )
            {
              rf_corpse_schedule_eviction(j);
            }
          }
          else
          {
            v6 = rf_vector_fast_distance((const float *)(j + 60), (const float *)(v3 + 60));
            if ( *(float *)(v3 + 120) > (double)v6 )
              rf_corpse_schedule_eviction(j);
          }
        }
      }
    }
  }
}

