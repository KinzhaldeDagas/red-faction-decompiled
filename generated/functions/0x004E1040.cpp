// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E1040 rf_player_clear_flags16_bit8
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Assumes player nonNULL; AND DWORD flags+16 with ~8, return player pointer EAX. Used by monitor exit but does not itself invalidate monitor/view target or resolve entity.
int __cdecl rf_player_clear_flags16_bit8(int a1)
{
  *(_DWORD *)(a1 + 16) &= ~8u;
  return a1;
}

