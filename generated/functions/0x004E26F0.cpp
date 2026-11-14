// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E26F0 rf_player_score_record_add_word4
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Assumes player and score-record pointer at+44 nonNULL. Sign-extend record WORD+4, add DWORD argument, store LOW16 back to+4; modular16-bit arithmetic, no saturation. Returns player pointer EAX. Two CTF497430 callers add1 immediately after player_add_frags(player,4); no mouse/input interpretation.
int __cdecl rf_player_score_record_add_word4(int a1, __int16 a2)
{
  *(_WORD *)(*(_DWORD *)(a1 + 44) + 4) += a2;
  return a1;
}

