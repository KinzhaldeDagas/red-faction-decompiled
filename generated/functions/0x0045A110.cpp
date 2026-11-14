// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045A110 rf_ui_draw_mars_background_if_zero_flag
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Cdecl rawBYTE flag. Zero lowBYTE calls scrolling Mars background then side bars/overlays; any nonzero byte skips both.
// Native MOVZX reads only argumentBYTE,not full DWORD. No own runtime/pause/render admission, color restoration or other state writes. Called from main-menu layout/draw4597C7. EAX
// zero-extended flag or final drawing-call residue,not a defined success status; original ABI preserved.
int __cdecl rf_ui_draw_mars_background_if_zero_flag(unsigned __int8 a1)
{
  int result; // eax

  result = a1;
  if ( !a1 )
  {
    rf_ui_draw_scrolling_mars_background();
    return rf_ui_draw_side_bars_and_overlays();
  }
  return result;
}

