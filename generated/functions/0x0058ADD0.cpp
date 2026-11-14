// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058ADD0 rf_mouse_disable_centering_request
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Sets secondary centering request gate193A06F=0. Does not change permission gate, cached cursor, relative deltas or Windows visibility.
void rf_mouse_disable_centering_request()
{
  unk_193A06F = 0;
}

