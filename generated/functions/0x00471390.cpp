// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00471390 rf_ui_checkbox_render
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall checkbox. White tint; scales absoluteXY/logicalWH. If normal handle+40>=0 draws base/style187CD34. If checked BYTE72 nonzero draws checked
// handle+68 with style182ABA8 WITHOUT handle-validity or enabled/focus guard. If focus8 AND enabled9 AND selected handle+44>=0, draws selection/style182ABA8 and tints
// label(255,128,128,255); OTHERWISE tint(128,0,0,255), including focused-enabled with invalid selected image. Recomputes labelXY from absoluteXY+origin52/56; blits label handle+48
// UNCONDITIONALLY with measured extents60/64, scaled destination, style187CD34. No toggle/callback, label-handle check or white restore.
int __thiscall rf_ui_checkbox_render(int this)
{
  int v3; // [esp+14h] [ebp-10h]
  int v4; // [esp+14h] [ebp-10h]
  int v5; // [esp+18h] [ebp-Ch]
  int v6; // [esp+18h] [ebp-Ch]
  int v7; // [esp+1Ch] [ebp-8h]
  int v8; // [esp+20h] [ebp-4h]

  rf_render_color_set_rgba8(255, 255, 255, 255);
  v5 = (int)((double)rf_ui_control_absolute_x((_DWORD *)this) * rf_ui_scale_x);
  v3 = (int)((double)rf_ui_control_absolute_y((_DWORD *)this) * rf_ui_scale_y);
  v7 = (int)((double)*(int *)(this + 20) * rf_ui_scale_x);
  v8 = (int)((double)*(int *)(this + 24) * rf_ui_scale_y);
  if ( *(int *)(this + 40) >= 0 )
    rf_bitmap_blit_subrectangle_backend_dispatch(
      *(_DWORD *)(this + 40),
      v5,
      v3,
      v7,
      v8,
      0,
      0,
      *(_DWORD *)(this + 20),
      *(_DWORD *)(this + 24),
      0,
      0,
      unk_187CD34);
  if ( *(_BYTE *)(this + 72) )
    rf_bitmap_blit_subrectangle_backend_dispatch(
      *(_DWORD *)(this + 68),
      v5,
      v3,
      v7,
      v8,
      0,
      0,
      *(_DWORD *)(this + 20),
      *(_DWORD *)(this + 24),
      0,
      0,
      unk_182ABA8);
  if ( *(_BYTE *)(this + 8) && *(_BYTE *)(this + 9) && *(int *)(this + 44) >= 0 )
  {
    rf_bitmap_blit_subrectangle_backend_dispatch(
      *(_DWORD *)(this + 44),
      v5,
      v3,
      v7,
      v8,
      0,
      0,
      *(_DWORD *)(this + 20),
      *(_DWORD *)(this + 24),
      0,
      0,
      unk_182ABA8);
    rf_render_color_set_rgba8(255, 128, 128, 255);
  }
  else
  {
    rf_render_color_set_rgba8(128, 0, 0, 255);
  }
  v6 = (int)((double)(*(_DWORD *)(this + 52) + rf_ui_control_absolute_x((_DWORD *)this)) * rf_ui_scale_x);
  v4 = (int)((double)(*(_DWORD *)(this + 56) + rf_ui_control_absolute_y((_DWORD *)this)) * rf_ui_scale_y);
  return rf_bitmap_blit_subrectangle_backend_dispatch(
           *(_DWORD *)(this + 48),
           v6,
           v4,
           (int)((double)*(int *)(this + 60) * rf_ui_scale_x),
           (int)((double)*(int *)(this + 64) * rf_ui_scale_y),
           0,
           0,
           *(_DWORD *)(this + 60),
           *(_DWORD *)(this + 64),
           0,
           0,
           unk_187CD34);
}

