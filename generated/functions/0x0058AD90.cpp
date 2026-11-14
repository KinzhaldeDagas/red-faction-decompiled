// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058AD90 rf_mouse_set_centering_permission_byte
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Stores caller raw byte at193A06E and returns it. Does not normalize, warp cursor, call ShowCursor or change secondary request gate.
char __cdecl rf_mouse_set_centering_permission_byte(char a1)
{
  unk_193A06E = a1;
  return a1;
}

