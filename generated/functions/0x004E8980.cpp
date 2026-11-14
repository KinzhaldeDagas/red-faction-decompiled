// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E8980 rf_fpgun_sway_is_eligible
// UNREALRED VERIFIED [fpgun-state-decode]: Gates sway on owner, settings, weapon identity, and inactive reload/custom actions.
bool __cdecl rf_fpgun_sway_is_eligible(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  if ( a1 != rf_local_fpgun_player )
    return 0;
  v2 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( !v2 )
    return 0;
  if ( !*(_BYTE *)(a1 + 3895) )
    return 0;
  if ( *(_DWORD *)(v2 + 676) == rf_weapon_index_grenade
    || *(_DWORD *)(v2 + 676) == dword_911C78
    || *(_DWORD *)(v2 + 676) == unk_911C88 )
  {
    return 0;
  }
  return !rf_fpgun_action_is_active(a1, 8u)
      && !rf_fpgun_action_is_active(a1, 0xAu)
      && !rf_fpgun_action_is_active(a1, 0xBu);
}

