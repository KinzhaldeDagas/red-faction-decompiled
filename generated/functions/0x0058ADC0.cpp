// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058ADC0 rf_mouse_enable_centering_request
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Sets secondary centering request gate193A06F=1. Recentering still requires permission gate193A06E and cursor polling mode. No immediate cursor operation or initialized guard.
void rf_mouse_enable_centering_request()
{
  unk_193A06F = 1;
}

