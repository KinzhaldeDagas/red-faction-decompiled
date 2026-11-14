// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004706F0 rf_ui_edit_render
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall edit. Sets tint240 when focus8 AND enabled9, otherwise192 (disabled still draws). Re-measures inline text+64 with stored font+100
// into+56/+60, clamps measured width+56 to[0,widthLimit+96], clears bitmap+44 and redraws text at offsets+48/+52 without handle guard. Ticks shared caret400ms timer regardless focus;
// draws underscore at(originX+clampedWidth,originY) only when focus8,enabled9,caret6F9118 all nonzero. Physical destinationXY=trunc((absoluteXY+textOrigin)*axisScale);
// destinationWH=trunc((logicalWH-textOrigin)*axisScale), but sourceWH remains FULL logicalWH with sourceoffset0. Blits12 arguments/style187CD34. No horizontal scrolling, old-resource
// change, active modal check or color restore.
int __thiscall rf_ui_edit_render(int this)
{
  int v3; // [esp+24h] [ebp-10h]
  int v4; // [esp+28h] [ebp-Ch]

  if ( *(_BYTE *)(this + 8) && *(_BYTE *)(this + 9) )
    rf_render_color_set_rgba8(240, 240, 240, 255);
  else
    rf_render_color_set_rgba8(192, 192, 192, 255);
  rf_font_measure_text_extent(
    (_DWORD *)(this + 56),
    (_DWORD *)(this + 60),
    (unsigned __int8 *)(this + 64),
    strlen((const char *)(this + 64)),
    *(_DWORD *)(this + 100));
  rf_integer_clamp_in_place((_DWORD *)(this + 56), 0, *(_DWORD *)(this + 96));
  rf_bitmap_clear_all_locked_texture_tile_bytes(*(_DWORD *)(this + 44));
  rf_font_draw_text_into_bitmap(
    *(_DWORD *)(this + 48),
    *(_DWORD *)(this + 52),
    *(_DWORD *)(this + 44),
    (const char *)(this + 64),
    *(_DWORD *)(this + 100));
  rf_ui_caret_blink_tick();
  if ( *(_BYTE *)(this + 8) && *(_BYTE *)(this + 9) && byte_6F9118[0] )
    rf_font_draw_text_into_bitmap(
      *(_DWORD *)(this + 56) + *(_DWORD *)(this + 48),
      *(_DWORD *)(this + 52),
      *(_DWORD *)(this + 44),
      "_",
      *(_DWORD *)(this + 100));
  v4 = (int)((double)(*(_DWORD *)(this + 48) + rf_ui_control_absolute_x((_DWORD *)this)) * rf_ui_scale_x);
  v3 = (int)((double)(*(_DWORD *)(this + 52) + rf_ui_control_absolute_y((_DWORD *)this)) * rf_ui_scale_y);
  return rf_bitmap_blit_subrectangle_backend_dispatch(
           *(_DWORD *)(this + 44),
           v4,
           v3,
           (int)((double)(*(_DWORD *)(this + 20) - *(_DWORD *)(this + 48)) * rf_ui_scale_x),
           (int)((double)(*(_DWORD *)(this + 24) - *(_DWORD *)(this + 52)) * rf_ui_scale_y),
           0,
           0,
           *(_DWORD *)(this + 20),
           *(_DWORD *)(this + 24),
           0,
           0,
           unk_187CD34);
}

