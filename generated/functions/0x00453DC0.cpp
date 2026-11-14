// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453DC0 rf_extras_menu_integrate_x_positions_and_render
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments. Reset full viewport571C20, draw scrolling background4589C0. FIRST integrate titlebar
// X: F32(velocity6F1DBC*frameDeltaSeconds663EC8 + position6F1DB8), no intermediate productF32 store. Only ORDERED position<signed integer min661E64(PE125) clamps toF32(min) and
// zeroes velocity; else only ORDERED position>signed integer6F29C4 clamps toF32(max)/velocity0. Equality andNaN preserve position/velocity; no bound sorting/finite/delta validation.
// Truncate final titlebarX via605F00 into control6F1E54+12 (6F1E60), render titlebar then label6F1F40. SECOND integrate button X similarly into6F1DB0 using velocity6F1DB4; first
// ordered>open bound signed661E44(PE11) clamps/zeroes velocity, else ordered<closed bound signed6F29A0 clamps/zeroes. Equality/NaN do not clamp. Truncate once, write SAME integer to
// four button X DWORDs6F1E8C,6F1E1C,6F1ED4,6F1DD4. Then signed loop0..<LIVE firstDWORD count6F1F0C, unchecked inline-slot accessor416F70, virtual+0 for every current control with
// ECX=this and NO explicit arguments; extra pointer/X in pseudocode is a virtual-signature artifact. Re-read count/slot across callbacks; no parent disabled/NULL/cycle/count-capacity
// guard. Finally458AA0 side bars/overlays, rawEAX. Both channels are X, not vertical motion; no active/readiness/input gate, motion completion event or restoration of renderer state.
int rf_extras_menu_integrate_x_positions_and_render()
{
  _DWORD *v0; // eax
  int v2; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  rf_renderer_reset_viewport_full_screen();
  rf_ui_draw_scrolling_mars_background();
  unk_6F1DB8 = unk_6F1DBC * rf_frame_delta_seconds + unk_6F1DB8;
  if ( unk_6F1DB8 >= (double)dword_661E64 )
  {
    if ( unk_6F1DB8 > (double)unk_6F29C4 )
    {
      unk_6F1DBC = 0.0;
      unk_6F1DB8 = (float)unk_6F29C4;
    }
  }
  else
  {
    unk_6F1DBC = 0.0;
    unk_6F1DB8 = (float)dword_661E64;
  }
  unk_6F1E60 = (int)unk_6F1DB8;
  rf_ui_panel_render_bitmap(dword_6F1E54);
  rf_ui_label_render((int)&unk_6F1F40);
  unk_6F1DB0 = unk_6F1DB4 * rf_frame_delta_seconds + unk_6F1DB0;
  if ( unk_6F1DB0 <= (double)rf_main_menu_open_x )
  {
    if ( unk_6F1DB0 < (double)rf_main_menu_closed_x )
    {
      unk_6F1DB4 = 0.0;
      unk_6F1DB0 = (float)rf_main_menu_closed_x;
    }
  }
  else
  {
    unk_6F1DB4 = 0.0;
    unk_6F1DB0 = (float)rf_main_menu_open_x;
  }
  v2 = (int)unk_6F1DB0;
  unk_6F1E8C = v2;
  unk_6F1E1C = v2;
  unk_6F1ED4 = v2;
  unk_6F1DD4 = v2;
  for ( i = 0; i < rf_receiver_get_first_dword(&unk_6F1F0C); ++i )
  {
    v0 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(&unk_6F1F0C, i);
    (**(void (__thiscall ***)(_DWORD, _DWORD, int))*v0)(*v0, *v0, v2);
  }
  return rf_ui_draw_side_bars_and_overlays();
}

