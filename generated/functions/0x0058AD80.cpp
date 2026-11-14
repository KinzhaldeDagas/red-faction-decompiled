// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058AD80 rf_mouse_get_centering_permission_byte
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Returns raw gate byte193A06E. Cursor-mode frame polling recenters only when both this byte and request gate193A06F are nonzero. No initialized guard or lock.
char rf_mouse_get_centering_permission_byte()
{
  return unk_193A06E;
}

