// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E8930 rf_fpgun_draw_or_holster_action_is_active
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player configuration packing/file I/O, fpgun type records and parser ECX/stack ABI): Unequal global local-fpgun pointer returnsAL0; otherwise holster slot7 AL EXACT1 then draw slot6 AL EXACT1 returns1, else0. No independent NULL guard for globalNULL/inputNULL, no pending-weapon3968 check (unlike6DD0), no state-machine resident test or own timer/mesh changes. Delegated action resolution may resolve selected mesh.
bool __cdecl rf_fpgun_draw_or_holster_action_is_active(int a1)
{
  if ( a1 != rf_local_fpgun_player )
    return 0;
  if ( rf_fpgun_action_is_active(a1, 7u) )
    return 1;
  return rf_fpgun_action_is_active(a1, 6u);
}

