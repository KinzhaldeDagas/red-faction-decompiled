// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E2710 rf_player_score_record_clear_words2_4_and_byte6
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Assumes player and score-record pointer+44 nonNULL. Zero WORD+2,WORD+4 and BYTE+6 in that order; firstWORD+0 and other bytes untouched. Return player pointer EAX. Called from split-screen match initialization; no full-record memset or allocation.
int __cdecl rf_player_score_record_clear_words2_4_and_byte6(int a1)
{
  *(_WORD *)(*(_DWORD *)(a1 + 44) + 2) = 0;
  *(_WORD *)(*(_DWORD *)(a1 + 44) + 4) = 0;
  *(_BYTE *)(*(_DWORD *)(a1 + 44) + 6) = 0;
  return a1;
}

