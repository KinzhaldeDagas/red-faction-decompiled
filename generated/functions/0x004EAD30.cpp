// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EAD30 rf_player_set_pending_weapon_and_disarm_timer184
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Assumes player nonNULL; assign supplied DWORD unchanged to pending weapon player3968; disarm timestamp at player184 via55F020 and return delegate EAX. No weapon validation, mesh assignment, action dispatch or disarm of separate fpgun timestamp3972.
_DWORD *__cdecl rf_player_set_pending_weapon_and_disarm_timer184(int a1, int a2)
{
  *(_DWORD *)(a1 + 3968) = a2;
  return rf_replicator_reset((_DWORD *)(a1 + 184));
}

