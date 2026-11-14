// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046EF60 rf_ui_modal_render
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): If modal active BYTE6F8C84 is zero, returns without drawing. Otherwise renders pause backing(1,1.0), sets black alpha128, fills bottom-image inset rectangle using
// trunc((absoluteX/Y+10)*axisScale), trunc((width/height-20)*axisScale), draws bottom/top images, then invokes each draw-list control virtual0 only when its BYTE9 is nonzero. Virtual
// calls use ECX=this with ZERO explicit arguments; decompiler extra draw parameters are residue. No input dispatch, callback active recheck, control updates or color restore.
int rf_ui_modal_render()
{
  int result; // eax
  _DWORD *v1; // eax
  int v2; // [esp+8h] [ebp-24h]
  int v3; // [esp+Ch] [ebp-20h]
  int v4; // [esp+10h] [ebp-1Ch]
  int v5; // [esp+14h] [ebp-18h]
  int i; // [esp+18h] [ebp-14h]
  int v7; // [esp+1Ch] [ebp-10h]

  result = unk_6F8C84;
  if ( unk_6F8C84 )
  {
    rf_pause_overlay_backing_render(1, 1.0);
    rf_render_color_set_rgba8(0, 0, 0, 128);
    v5 = rf_ui_control_absolute_x(dword_6F8E28) + 10;
    v7 = (int)((double)v5 * rf_ui_scale_x);
    v4 = rf_ui_control_absolute_y(dword_6F8E28) + 10;
    v3 = unk_6F8E3C - 20;
    v2 = unk_6F8E40 - 20;
    rf_renderer_fill_rectangle_clipped(
      v7,
      (int)((double)v4 * rf_ui_scale_y),
      (int)((double)(unk_6F8E3C - 20) * rf_ui_scale_x),
      (int)((double)(unk_6F8E40 - 20) * rf_ui_scale_y),
      dword_182ABB8);
    rf_ui_panel_render_bitmap(dword_6F8E28);
    rf_ui_panel_render_bitmap(dword_6F8F04);
    for ( i = 0; ; ++i )
    {
      result = rf_receiver_get_first_dword(unk_6F8F30);
      if ( i >= result )
        break;
      if ( *(_BYTE *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8F30, i) + 9) )
      {
        v1 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8F30, i);
        (**(void (__thiscall ***)(_DWORD, _DWORD, int, int, int, int))*v1)(*v1, *v1, v2, v3, v4, v5);
      }
    }
  }
  return result;
}

