// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00436710 rf_entity_weapon_is_holstered_for_actions
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(entity), canonical AL0/1; NULL false. Attached-use-turret437E30 EXACT AL1 returns0 BEFORE checking
// holster bit; any other returned byte continues. Otherwise entity2064 mask0x800 yieldsAL1 iff set. No inventory/selected-weapon/player/dead/authority validation, state change or
// timer test; this guarded predicate can differ from raw bit reads used by setters.
bool __cdecl rf_entity_weapon_is_holstered_for_actions(int a1)
{
  if ( !a1 )
    return 0;
  if ( rf_entity_has_attached_use_turret(a1) )
    return 0;
  return (*(_DWORD *)(a1 + 2064) & 0x800) != 0;
}

