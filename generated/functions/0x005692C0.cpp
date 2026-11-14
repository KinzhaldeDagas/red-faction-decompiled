// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005692C0 rf_sound_frontend_shutdown
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, sound wrapper ABI, triangle/plane interval tests, strict sphere overlap and retail SAT coefficients): Calls5C0020 backend shutdown,then unconditionally clears frontend ready byte1808960. No readiness guard here and no direct resource-count or frontend-slot reset. No semantic return value.
void rf_sound_frontend_shutdown()
{
  rf_sound_backend_shutdown();
  rf_sound_system_ready[0] = 0;
}

