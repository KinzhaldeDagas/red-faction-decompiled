// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00488D40 rf_mover_trigger_has_active_entity
// UNREALRED VERIFIED [mission-mover-runtime-20261013] Closing-door trigger occupancy scans active entity positions inside the stored source trigger. Excludes respawn-inactive objects, not merely all combat-dead bodies. Called when closing target index0 and mode!=1; true reverses the linear segment. This is distinct from physical solid obstruction resolution.
// UNREALRED VERIFIED [mission-mover-occupancy-20261020] Closing obstruction checks only the global ENTITY list, skipping common flag+0x7C bit0x4000. Uses common-object position+0x3C against the originating trigger UID stored at mover+0x314. Does not use capsule extents, trigger enable/NPC/reset/use eligibility, common life, visibility, or collision. Sphere comparison is strict radius > float fast distance (0x5598F0/0x558CC0). Corpses are not scanned here.
char __cdecl rf_mover_trigger_has_active_entity(int a1)
{
  int v3; // [esp+0h] [ebp-Ch]
  int i; // [esp+4h] [ebp-8h]
  float v5; // [esp+8h] [ebp-4h]

  v3 = rf_trigger_find_by_uid(*(_DWORD *)(a1 + 788));
  if ( !v3 )
    return 0;
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
          return 1;
        }
      }
      else
      {
        v5 = rf_vector_fast_distance((const float *)(i + 60), (const float *)(v3 + 60));
        if ( *(float *)(v3 + 120) > (double)v5 )
          return 1;
      }
    }
  }
  return 0;
}

