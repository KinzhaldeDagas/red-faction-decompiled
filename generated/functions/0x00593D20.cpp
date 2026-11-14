// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593D20 rf_window_get_active_byte
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Returns raw activity byte1BC2134. Verified window-message writer handles WM_ACTIVATE6 (low word1 or2 sets1, other values0) and WM_ACTIVATEAPP28 (nonzero wParam sets1, zero0). Getter does not poll OS focus or normalize the stored byte. Cursor-warp helper gates its API calls on this result.
char rf_window_get_active_byte()
{
  return unk_1BC2134;
}

