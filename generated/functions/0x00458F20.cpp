// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00458F20 rf_ui_debug_build_overlay_disabled
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Reserves110-byte local area, saves stack security cookie, then UNCONDITIONALLY jumps458F33->459013 to cookie verification605EE4 and epilogue.
// No reachable debug-build formatting, drawing, color changes or build-number test. The intervening sprintf/font/rectangle code is unreachable from ordinary entry and is not a menu
// overlay effect. Cookie verification can still fail; not a literal one-instruction no-op. PlainRET and no meaningful application result.
void rf_ui_debug_build_overlay_disabled()
{
  ;
}

