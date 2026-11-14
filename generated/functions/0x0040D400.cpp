// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D400 rf_entity_has_jeep_flag
// VERIFIED: Returns true only for a non-null runtime record whose entity-definition flags dword +1828 contains authored flag 0x00400000, named exactly 'jeep' by the active 28-entry entity flag table.
// UNREALRED VERIFIED [general-gap-20260830]: Returns true only when a non-null entity definition carries authored flag 0x00400000, named exactly 'jeep' by the retail flag table.
bool __cdecl rf_entity_has_jeep_flag(int a1)
{
  return a1 && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 0x400000) != 0;
}

