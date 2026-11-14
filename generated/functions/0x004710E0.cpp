// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004710E0 rf_ui_image_button_draw
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall button. Sets white; scales absoluteXY and logicalWH with x87 truncation per axis. Valid normal bitmap+40 draws full logical source/physical
// destination with style187CD34. Focus8 AND enabled9 optionally draws valid selected bitmap+44 with style182ABA8, then label tint240 regardless selected validity; else enabled
// tint192, disabled96. Valid label surface+48 draws FULL logicalWH at SAME controlXY, not text-origin offsets (label was rasterized in place), style187CD34. Every blit has12 explicit
// arguments. Restores white RGBA255 at end. Disabled controls still draw; no state mutation/callback.
char __thiscall rf_ui_image_button_draw(int this)
{
  int v3; // [esp+Ch] [ebp-10h]
  int v4; // [esp+10h] [ebp-Ch]
  int v5; // [esp+14h] [ebp-8h]
  int v6; // [esp+18h] [ebp-4h]

  rf_render_color_set_rgba8(255, 255, 255, 255);
  v4 = (int)((double)rf_ui_control_absolute_x((_DWORD *)this) * rf_ui_scale_x);
  v3 = (int)((double)rf_ui_control_absolute_y((_DWORD *)this) * rf_ui_scale_y);
  v5 = (int)((double)*(int *)(this + 20) * rf_ui_scale_x);
  v6 = (int)((double)*(int *)(this + 24) * rf_ui_scale_y);
  if ( *(int *)(this + 40) >= 0 )
    rf_bitmap_blit_subrectangle_backend_dispatch(
      *(_DWORD *)(this + 40),
      v4,
      v3,
      v5,
      v6,
      0,
      0,
      *(_DWORD *)(this + 20),
      *(_DWORD *)(this + 24),
      0,
      0,
      unk_187CD34);
  if ( *(_BYTE *)(this + 8) && *(_BYTE *)(this + 9) )
  {
    if ( *(int *)(this + 44) >= 0 )
      rf_bitmap_blit_subrectangle_backend_dispatch(
        *(_DWORD *)(this + 44),
        v4,
        v3,
        v5,
        v6,
        0,
        0,
        *(_DWORD *)(this + 20),
        *(_DWORD *)(this + 24),
        0,
        0,
        unk_182ABA8);
    rf_render_color_set_rgba8(240, 240, 240, 255);
  }
  else if ( *(_BYTE *)(this + 9) )
  {
    rf_render_color_set_rgba8(192, 192, 192, 255);
  }
  else
  {
    rf_render_color_set_rgba8(96, 96, 96, 255);
  }
  if ( *(int *)(this + 48) >= 0 )
    rf_bitmap_blit_subrectangle_backend_dispatch(
      *(_DWORD *)(this + 48),
      v4,
      v3,
      v5,
      v6,
      0,
      0,
      *(_DWORD *)(this + 20),
      *(_DWORD *)(this + 24),
      0,
      0,
      unk_187CD34);
  return rf_render_color_set_rgba8(255, 255, 255, 255);
}

