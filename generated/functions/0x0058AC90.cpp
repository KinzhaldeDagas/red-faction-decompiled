// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058AC90 rf_mouse_button_snapshot_click_age
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Returns configured double-click interval663F50 minus signed-half-period deadline remaining for SNAPSHOT button.deadline at193A0BC+16*index. Raw timer arithmetic with no initialized/bounds/lock guard or clamp. Does not consume click flag/count or read pending deadline directly.
int __cdecl rf_mouse_button_snapshot_click_age(int a1)
{
  return dword_663F50 - rf_clock_deadline_remaining_signed_half_period(&unk_193A0BC[4 * a1]);
}

