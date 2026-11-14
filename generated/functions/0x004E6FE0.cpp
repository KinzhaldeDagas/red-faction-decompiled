// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E6FE0 rf_fpgun_request_reload_action
// UNREALRED VERIFIED [fpgun-action-dispatch]: Performs explicit idle cleanup and dispatches reload when admitted.
int __cdecl rf_fpgun_request_reload_action(int a1)
{
  int result; // eax
  int v2; // [esp+8h] [ebp-8h]
  int v3; // [esp+Ch] [ebp-4h]

  result = a1;
  if ( a1 == rf_local_fpgun_player )
  {
    result = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
    v3 = result;
    if ( result )
    {
      rf_player_reset_alt_zoom_state(a1);
      sub_4E71A0(a1);
      result = rf_entity_weapon_is_holstered_for_actions(v3);
      if ( (unsigned __int8)result != 1 )
      {
        rf_fpgun_cleanup_idle_actions(a1);
        rf_fpgun_dispatch_semantic_action(a1, 8u);
        sub_4EBD20(a1);
        v2 = (int)rf_random_float_range(6000.0, 8000.0);
        return rf_replicator_arm_milliseconds((int *)(a1 + 3976), v2);
      }
    }
  }
  return result;
}

