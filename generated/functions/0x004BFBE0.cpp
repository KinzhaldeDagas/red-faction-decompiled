// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BFBE0 rf_trigger_collision_pair_filter
// UNREALRED VERIFIED [trigger-inside-time-20261021] Physical pair creation excludes flag4 auto triggers, NPC policy0 without player flag, policy3 with player flag, and the policy4 entity/use-vehicle case. These pair filters precede the common timer query and must not be represented as common-query failures for unrelated actors.
char __cdecl rf_trigger_collision_pair_filter(int a1, _DWORD *a2)
{
  int v3; // [esp+0h] [ebp-4h]

  if ( rf_trigger_is_auto(a1) )
    return 0;
  v3 = *(_DWORD *)(a1 + 708);
  if ( v3 )
  {
    if ( v3 == 3 )
    {
      if ( rf_object_has_player_flag((int)a2) )
        return 0;
    }
    else if ( v3 == 4 && !a2[9] && !rf_object_is_use_vehicle(a2) )
    {
      return 0;
    }
  }
  else if ( !rf_object_has_player_flag((int)a2) )
  {
    return 0;
  }
  return 1;
}

