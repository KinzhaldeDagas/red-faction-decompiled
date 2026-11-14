// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044CA20 rf_hud_world_target_registry_add
// UNREALRED VERIFIED [hud-world-targets] Appends object UID, owning trigger UID, reset red deadline, and clear occlusion byte to one 16-byte record while the fixed count is below 32.
int __cdecl rf_hud_world_target_registry_add(int a1, int a2)
{
  int result; // eax

  if ( rf_hud_world_target_count < 32 )
  {
    rf_replicator_reset(&rf_hud_world_target_red_deadlines[4 * rf_hud_world_target_count]);
    rf_hud_world_target_object_uids[4 * rf_hud_world_target_count] = a1;
    rf_hud_world_target_trigger_uids[4 * rf_hud_world_target_count] = a2;
    rf_hud_world_target_occlusion_bytes[16 * rf_hud_world_target_count++] = 0;
    return a2;
  }
  return result;
}

