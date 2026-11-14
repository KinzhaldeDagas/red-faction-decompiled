// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DC5C0 rf_player_should_use_fpgun_presentation
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Cdecl player. Missing resolved entity returnsfalse. Attached-vehicle predicate AL !=EXACT1 returns true. For EXACT1, permits only nonzero439070(entity): resolved attached entity must be jeep and seat-entry1 occupant UID equals current entity UID44. No own health, weapon, monitor, turret, body, custom-action or player NULL check. This selects fpgun-versus-cockpit presentation, not general action eligibility.
bool __cdecl rf_player_should_use_fpgun_presentation(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( !v2 )
    return 0;
  return !rf_entity_has_attached_use_vehicle(v2) || rf_entity_is_parent_jeep_relation1(v2);
}

