// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F6F50 rf_quicksave_is_allowed
// UNREALRED VERIFIED [save-validation-20261028]: Rejects multiplayer, absent local-player entity, dead resolved local-player entity, clear bit0 of global0x6FC424, training level, global unhide-owner presence, or any active dead entity with flags+2064 mask0x400000. Otherwise returns1. No file I/O or cooldown check. Global-bit meaning remains unproven; predicates0x4DEFC0/0x4DEFF0 resolve player handle+20.
char __thiscall rf_quicksave_is_allowed(void *this)
{
  const char *v2; // eax
  int i; // [esp+0h] [ebp-4h]

  if ( rf_multiplayer_runtime_mode )
    return 0;
  if ( rf_player_has_no_resolved_entity(rf_local_fpgun_player)
    || rf_player_resolved_entity_is_dead(rf_local_fpgun_player) )
  {
    return 0;
  }
  if ( !rf_level_state_bit0_is_set() )
    return 0;
  v2 = rf_string_object_c_str_or_empty(unk_6FC31C);
  if ( rf_level_name_is_training(v2) )
    return 0;
  if ( rf_unhide_global_owner_present() )
    return 0;
  for ( i = dword_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
  {
    if ( (*(_DWORD *)(i + 2064) & 0x400000) != 0 && rf_entity_is_dead(i) )
      return 0;
  }
  return 1;
}

