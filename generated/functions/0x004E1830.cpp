// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E1830 rf_player_has_flags16_mask10
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Assumes player nonNULL; returns AL1 iff DWORD flags+16 has mask0x10, else0. Used in local-player/HUD and shield-damage gates; does not resolve an entity or establish producer meaning of the flag.
bool __cdecl rf_player_has_flags16_mask10(int a1)
{
  return (*(_DWORD *)(a1 + 16) & 0x10) != 0;
}

