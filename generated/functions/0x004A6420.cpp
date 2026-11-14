// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A6420 rf_multiplayer_log_uptime_tick
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl NO arguments; prior saved double@ST0 input is false. Requires FILE7B1530 nonnull. Computes SIGNED64 difference time64(NULL)-sign_extend(last DWORD662BE0); only if
// strictly>2520 seconds calls no-argument uptime logger, then reads time64 again and stores LOW32 in checkpoint662BE0. Exactly2520 skips; negative64 difference skips. No update when
// log disabled/not due, no missed-interval catchup, no incoming x87 data use. Caller-cleaned RET; corrected prototype void(void).
void __cdecl rf_multiplayer_log_uptime_tick()
{
  if ( MEMORY[0x7B1530] )
  {
    if ( rf_crt_time64_forward(nullptr) - dword_662BE0 > 2520 )
    {
      rf_multiplayer_log_uptime();
      dword_662BE0 = rf_crt_time64_forward(nullptr);
    }
  }
}

