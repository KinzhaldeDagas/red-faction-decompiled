// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E1020 rf_player_set_flags16_bit8
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Assumes player nonNULL; OR DWORD flags+16 with mask8, return player pointer EAX. No other fields or view target updates; broader producer meaning not assigned.
int __cdecl rf_player_set_flags16_bit8(int a1)
{
  *(_DWORD *)(a1 + 16) |= 8u;
  return a1;
}

