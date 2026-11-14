// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B1550 rf_multiplayer_get_team0_score_byte
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tracker packet widths, signed endpoint counts, fixed pools, DNS/clock gates, receive ABI and team-score byte
// semantics): Noarg. Load raw BYTE7B2608 into AL and return; no EAX zero/sign extension, runtime/mode gate or mutation. Caller must interpret native byte result, not assume high24
// EAX bits cleared.
char rf_multiplayer_get_team0_score_byte()
{
  return unk_7B2608;
}

