// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044CA90 rf_hud_world_target_registry_remove
// UNREALRED VERIFIED [hud-world-targets] Removes the first matching object UID by compacting every remaining 16-byte target record in stable order.
int __cdecl rf_hud_world_target_registry_remove(int a1)
{
  int result; // eax
  int j; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < rf_hud_world_target_count; ++i )
  {
    if ( rf_hud_world_target_object_uids[4 * i] == a1 )
    {
      for ( j = i; ; ++j )
      {
        result = rf_hud_world_target_count - 1;
        if ( j >= rf_hud_world_target_count - 1 )
          break;
        rf_hud_world_target_object_uids[4 * j] = rf_hud_world_target_object_uids[4 * j + 4];
        rf_hud_world_target_trigger_uids[4 * j] = rf_hud_world_target_trigger_uids[4 * j + 4];
        rf_hud_world_target_red_deadlines[4 * j] = rf_hud_world_target_red_deadlines[4 * j + 4];
        rf_hud_world_target_occlusion_bytes[16 * j] = rf_hud_world_target_occlusion_bytes[16 * j + 16];
      }
      --rf_hud_world_target_count;
      return result;
    }
    result = i + 1;
  }
  return result;
}

