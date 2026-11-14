// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D300 rf_entity_has_turret_flag
// VERIFIED: Returns true only for a non-null runtime record whose entity-definition flags dword +1828 contains authored flag 0x00002000, named exactly 'turret' by the active 28-entry entity flag table.
// UNREALRED VERIFIED [general-gap-20260830]: Returns true only when a non-null entity definition carries authored flag 0x00002000, named exactly 'turret' by the retail flag table.
bool __cdecl rf_entity_has_turret_flag(int a1)
{
  return a1 && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 0x2000) != 0;
}

