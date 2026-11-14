// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B1F50 rf_tracker_clear_pending_control_state
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tracker packet widths, signed endpoint counts, fixed pools, DNS/clock gates, receive ABI and team-score byte
// semantics): Recovered4B1F50..4B1F6A,lastRET4B1F69. Noarg; initialized7B4DB8==0 returns without changes. Otherwise exactly DWORD7B2624=0. Does not clear list-query/registration
// flags, queue, initialized bit, send cancellation or reset timestamps; different from existing21B0 helper which also sets registration-active1 and last-seconds-100. No semantic
// return.
void __cdecl rf_tracker_clear_pending_control_state()
{
  if ( dword_7B4DB8 )
    dword_7B2624 = 0;
}

