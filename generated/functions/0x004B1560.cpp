// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B1560 rf_multiplayer_get_team1_score_byte
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tracker packet widths, signed endpoint counts, fixed pools, DNS/clock gates, receive ABI and team-score byte
// semantics): Noarg. Return raw BYTE7B2609 in AL without initializing highEAX. No normalization, admission or side effects.
char rf_multiplayer_get_team1_score_byte()
{
  return unk_7B2609;
}

