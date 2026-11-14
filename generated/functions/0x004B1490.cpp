// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B1490 rf_multiplayer_clear_two_team_score_bytes
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tracker packet widths, signed endpoint counts, fixed pools, DNS/clock gates, receive ABI and team-score byte
// semantics): Noarg. Exactly two byte stores:7B2608=0 then7B2609=0. No runtime/authority/mode gate, packet send, player-score/CTF-object reset or return status. Adjacent team
// setters/getters/incrementers use these same bytes.
void rf_multiplayer_clear_two_team_score_bytes()
{
  unk_7B2608 = 0;
  unk_7B2609 = 0;
}

