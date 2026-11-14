// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00435D30 rf_character_update_damage_flinch_override
// UNREALRED VERIFIED [damage-flinch-decode]: Preserves the entity flinch override while that exact action remains active; otherwise resets it to -1.
char __cdecl rf_character_update_damage_flinch_override(int a1)
{
  if ( *(_DWORD *)(a1 + 128) && *(_DWORD *)(a1 + 2088) != -1 )
  {
    if ( rf_entity_body_action_is_active(a1, *(_DWORD *)(a1 + 2088)) )
      return 1;
    *(_DWORD *)(a1 + 2088) = -1;
  }
  return 0;
}

