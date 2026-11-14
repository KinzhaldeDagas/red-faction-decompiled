// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044CB80 rf_hud_world_target_arm_red_deadline
// UNREALRED VERIFIED [hud-world-targets] Finds a target by object UID and arms its embedded red-bracket deadline from a caller-provided millisecond duration.
int __cdecl rf_hud_world_target_arm_red_deadline(int a1, int a2)
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_hud_world_target_count; ++i )
  {
    if ( rf_hud_world_target_object_uids[4 * i] == a1 )
      return rf_replicator_arm_milliseconds(&rf_hud_world_target_red_deadlines[4 * i], a2);
    result = i + 1;
  }
  return result;
}

