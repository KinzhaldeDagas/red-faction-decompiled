// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00455370 rf_save_list_a_animate_and_draw
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Both animated channels are X, proved by stores to panel+12 and recursive absolute-X helper46FC70; +16 is Y. Integrate x87 velocity*frameDelta+old position,
// store FLOAT32, clamp only strict ordered under/overshoot and clear that velocity; equality retains velocity and unordered NaN passes through. Signed integer bounds are FILD.
// Convert each position via605F00. Title6F1FA4 uses current6F1F8C/velocity6F1F90, bounds signed661E64..6F29C4, writes6F1FB0; draw title46FD70 and label6F2388. Body6F2014 uses
// current6F1F84/velocity6F1F94, bounds661E58..6F29C8, writes6F2020. Set RGBA(0,0,0,128); draw black physical rectangle
// trunc((bodyX+10)*scaleX),trunc((bodyY+10)*scaleY),trunc(width*scaleX),trunc((height-20)*scaleY), using live182ABB8; integer offsets wrap32 before FILD. Draw body. Signed row
// i0..<visible6F1F80, candidate=offset6F1F9C+i wrapped; only candidate<LIVE record count6F21AC guards454B50(candidate,i), with no nonnegative test. Render each element in6F228C using
// LIVE count,416F70 and virtualslot0 ECX receiver; native pushes NO explicit virtual-call arguments, contrary to garbage pseudocode parameters. Finally458AA0, forwarding residue. No
// ready/null/cycle guard or normalized result.
int rf_save_list_a_animate_and_draw()
{
  _DWORD *v0; // eax
  int v2; // [esp+4h] [ebp-24h]
  int v3; // [esp+8h] [ebp-20h]
  int v4; // [esp+Ch] [ebp-1Ch]
  int v5; // [esp+10h] [ebp-18h]
  int i; // [esp+14h] [ebp-14h]
  int j; // [esp+14h] [ebp-14h]

  rf_renderer_reset_viewport_full_screen();
  rf_ui_draw_scrolling_mars_background();
  unk_6F1F8C = unk_6F1F90 * rf_frame_delta_seconds + unk_6F1F8C;
  if ( unk_6F1F8C >= (double)dword_661E64 )
  {
    if ( unk_6F1F8C > (double)unk_6F29C4 )
    {
      unk_6F1F90 = 0.0;
      unk_6F1F8C = (float)unk_6F29C4;
    }
  }
  else
  {
    unk_6F1F90 = 0.0;
    unk_6F1F8C = (float)dword_661E64;
  }
  unk_6F1FB0 = (int)unk_6F1F8C;
  rf_ui_panel_render_bitmap(dword_6F1FA4);
  rf_ui_label_render((int)&unk_6F2388);
  unk_6F1F84 = unk_6F1F94 * rf_frame_delta_seconds + unk_6F1F84;
  if ( unk_6F1F84 >= (double)dword_661E58 )
  {
    if ( unk_6F1F84 > (double)unk_6F29C8 )
    {
      unk_6F1F94 = 0.0;
      unk_6F1F84 = (float)unk_6F29C8;
    }
  }
  else
  {
    unk_6F1F94 = 0.0;
    unk_6F1F84 = (float)dword_661E58;
  }
  unk_6F2020 = (int)unk_6F1F84;
  rf_render_color_set_rgba8(0, 0, 0, 128);
  v4 = unk_6F2020 + 10;
  v3 = unk_6F2024 + 10;
  v2 = unk_6F202C - 20;
  rf_renderer_fill_rectangle_clipped(
    (int)((double)(unk_6F2020 + 10) * rf_ui_scale_x),
    (int)((double)(unk_6F2024 + 10) * rf_ui_scale_y),
    (int)((double)unk_6F2028 * rf_ui_scale_x),
    (int)((double)(unk_6F202C - 20) * rf_ui_scale_y),
    dword_182ABB8);
  rf_ui_panel_render_bitmap(dword_6F2014);
  for ( i = 0; i < unk_6F1F80; ++i )
  {
    v5 = i + dword_6F1F9C;
    if ( v5 >= rf_receiver_get_first_dword(dword_6F21AC) )
      break;
    rf_save_list_a_draw_record_row(v5, i);
  }
  for ( j = 0; j < rf_receiver_get_first_dword(&unk_6F228C); ++j )
  {
    v0 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(&unk_6F228C, j);
    (**(void (__thiscall ***)(_DWORD, _DWORD, int, int, int))*v0)(*v0, *v0, v2, v3, v4);
  }
  return rf_ui_draw_side_bars_and_overlays();
}

