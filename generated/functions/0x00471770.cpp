// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00471770 rf_ui_slider_render
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall slider. Scales knobWH44/48; computes ratio=(currentFLOAT52-min64)/(max68-min64) in x87 and stores binary32 BEFORE position arithmetic,
// without zero/finite/clamp guard. Sets white. OrientationBYTE40 ANY nonzero: x=trunc(absX*scaleX), y=trunc((absY+(trackHeight24-knobHeight48)*ratio)*scaleY); zero analogous
// horizontal travel(trackWidth20-knobWidth44), fixed absY. Valid normal handle56 blits full knob dimensions with style187CD34. Focus8 AND enabled9 AND valid selected handle60 draws
// overlay at identical knob rect/style182ABA8. Each blit12args; no track background, callback, state mutation or final color change. Draw travel subtracts knob size, unlike pointer
// updater471930 denominator FULL track dimension.
int __thiscall rf_ui_slider_render(int this)
{
  int result; // eax
  int v3; // [esp+1Ch] [ebp-14h]
  int v4; // [esp+20h] [ebp-10h]
  float v5; // [esp+24h] [ebp-Ch]
  int v6; // [esp+28h] [ebp-8h]
  int v7; // [esp+2Ch] [ebp-4h]

  v6 = (int)((double)*(int *)(this + 44) * rf_ui_scale_x);
  v7 = (int)((double)*(int *)(this + 48) * rf_ui_scale_y);
  v5 = (*(float *)(this + 52) - *(float *)(this + 64)) / (*(float *)(this + 68) - *(float *)(this + 64));
  rf_render_color_set_rgba8(255, 255, 255, 255);
  if ( *(_BYTE *)(this + 40) )
  {
    v4 = (int)((double)rf_ui_control_absolute_x((_DWORD *)this) * rf_ui_scale_x);
    v3 = (int)(((double)rf_ui_control_absolute_y((_DWORD *)this)
              + (double)(*(_DWORD *)(this + 24) - *(_DWORD *)(this + 48)) * v5)
             * rf_ui_scale_y);
  }
  else
  {
    v4 = (int)(((double)rf_ui_control_absolute_x((_DWORD *)this)
              + (double)(*(_DWORD *)(this + 20) - *(_DWORD *)(this + 44)) * v5)
             * rf_ui_scale_x);
    v3 = (int)((double)rf_ui_control_absolute_y((_DWORD *)this) * rf_ui_scale_y);
  }
  if ( *(int *)(this + 56) >= 0 )
    rf_bitmap_blit_subrectangle_backend_dispatch(
      *(_DWORD *)(this + 56),
      v4,
      v3,
      v6,
      v7,
      0,
      0,
      *(_DWORD *)(this + 44),
      *(_DWORD *)(this + 48),
      0,
      0,
      unk_187CD34);
  result = *(unsigned __int8 *)(this + 8);
  if ( *(_BYTE *)(this + 8) && *(_BYTE *)(this + 9) )
  {
    result = this;
    if ( *(int *)(this + 60) >= 0 )
      return rf_bitmap_blit_subrectangle_backend_dispatch(
               *(_DWORD *)(this + 60),
               v4,
               v3,
               v6,
               v7,
               0,
               0,
               *(_DWORD *)(this + 44),
               *(_DWORD *)(this + 48),
               0,
               0,
               unk_182ABA8);
  }
  return result;
}

