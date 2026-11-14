// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E6DD0 rf_fpgun_weapon_transition_blocks_fire
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player configuration packing/file I/O, fpgun type records and parser ECX/stack ABI): Only input player equal global local-fpgun pointer can pass; unequal returns AL0. Does NOT independently reject NULL when both pointersNULL: immediately reads pending DWORD player+3968. Any pending value other than EXACT-1 returnsAL1, including other invalid negative/out-of-range indices. Otherwise semantic action6 draw AL EXACT1 or action7 holster AL EXACT1 returns1; else0. Action helper resolves selected mesh/named animation and tests nonzero remaining time; no direct active-state flag, elapsed deadline or pending index bounds check here. Preserves existing descriptive name and refines prior valid-index wording.
bool __cdecl rf_fpgun_weapon_transition_blocks_fire(int a1)
{
  if ( a1 != rf_local_fpgun_player )
    return 0;
  if ( *(_DWORD *)(a1 + 3968) != -1 )
    return 1;
  if ( rf_fpgun_action_is_active(a1, 6u) )
    return 1;
  return rf_fpgun_action_is_active(a1, 7u);
}

