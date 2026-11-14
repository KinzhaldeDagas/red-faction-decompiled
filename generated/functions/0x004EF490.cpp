// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EF490 rf_undercover_cancel_local_pending_fpgun_transition
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, thermal renderer x87 branches, native stack aliases, localization pool writes and skin-profile selection): No arguments. Calls empty player transition hook with global local player, writes its DWORD3968=-1, then disarms timestamp member3972 using rf_replicator_reset and forwards its member pointer in EAX. No own local-player NULL check or other transition/model cleanup.
_DWORD *rf_undercover_cancel_local_pending_fpgun_transition()
{
  rf_fpgun_cancel_transition_hook_noop(rf_local_fpgun_player);
  *(_DWORD *)(rf_local_fpgun_player + 3968) = -1;
  return rf_replicator_reset((_DWORD *)(rf_local_fpgun_player + 3972));
}

