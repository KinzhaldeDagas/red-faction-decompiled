// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004387E0 rf_entity_selected_weapon_state_bit_is_set
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Cdecl(entity,signed weaponIndex), bool AL. NULL entity or signed index<0 or>31 returns0 before shifting. Otherwise return whether Entity DWORD5160 contains1<<index.
// No weapon-registry count check, body-action query or mutation; index31 is admitted. This bit is replication action bit2 source, distinct from holstered Entity2064mask800.
bool __cdecl rf_entity_selected_weapon_state_bit_is_set(int a1, unsigned int a2)
{
  if ( !a1 )
    return 0;
  if ( a2 < 0x20 )
    return (*(_DWORD *)(a1 + 5160) & (1 << a2)) != 0;
  return 0;
}

