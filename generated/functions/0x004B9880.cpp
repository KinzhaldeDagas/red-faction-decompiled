// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B9880 rf_object_physics_should_simulate
// UNREALRED VERIFIED [mission-unhide-20261020] Object physics admission rejects common inactive and sets common0x800000 on the relevant early path; inactivity is not death. UE integration suppresses actor/controller/movement tick and collision while retaining velocity for inactivity alone; explicit preview-world pause retains its existing immediate-stop contract.
char __cdecl rf_object_physics_should_simulate(int a1)
{
  int first_dword; // [esp+8h] [ebp-4h]

  if ( !rf_physics_state_is_enabled(a1 + 136) )
  {
    *(_DWORD *)(a1 + 124) |= (unsigned int)&unk_800000;
    return 0;
  }
  if ( rf_object_has_respawn_inactive_flag(a1) )
  {
    *(_DWORD *)(a1 + 124) |= (unsigned int)&unk_800000;
    return 0;
  }
  if ( *(_DWORD *)(a1 + 512) != -1 && (*(_DWORD *)(a1 + 124) & 0x100) == 0 )
  {
    *(_DWORD *)(a1 + 124) |= (unsigned int)&unk_800000;
    return 0;
  }
  if ( !*(_DWORD *)(a1 + 36) && (*(_DWORD *)(a1 + 2068) & 0x40) != 0 )
  {
    *(_DWORD *)(a1 + 124) |= (unsigned int)&unk_800000;
    return 0;
  }
  if ( rf_entity_matches_local_player_or_related_handle(a1) )
    return 1;
  if ( ((unsigned int)&unk_800000 & *(_DWORD *)(a1 + 424)) != 0 )
  {
    *(_DWORD *)(a1 + 424) &= ~0x800000u;
    *(_DWORD *)(a1 + 124) |= (unsigned int)&unk_800000;
    return 0;
  }
  first_dword = rf_receiver_get_first_dword((void *)a1);
  if ( !first_dword )
    return 1;
  if ( *(_BYTE *)(first_dword + 352) || *(_DWORD *)(a1 + 36) == 2 || *(float *)(a1 + 52) <= 0.0 )
    return 1;
  if ( *(_DWORD *)(a1 + 36) )
    goto LABEL_34;
  if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active || *(int *)(a1 + 2068) < 0 )
    return 1;
  if ( *(_DWORD *)(a1 + 1312) == 3 && *(int *)(a1 + 1416) > 0
    || *(_DWORD *)(a1 + 1312) == 10
    || *(_DWORD *)(a1 + 1312) == 7 && *(int *)(a1 + 1416) > 0 )
  {
    return 1;
  }
  if ( rf_point_nearest_live_player_distance_float((float *)(a1 + 60)) < 900.0 )
    return 1;
LABEL_34:
  *(_DWORD *)(a1 + 124) |= (unsigned int)&unk_800000;
  return 0;
}

