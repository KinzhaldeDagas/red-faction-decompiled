// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00457600 rf_save_list_b_animate_and_draw
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Both animated channels are X, proved by stores to panel+12 and recursive absolute-X helper46FC70; +16 is Y. Integrate x87 velocity*frameDelta+old position,
// store FLOAT32, clamp only strict ordered under/overshoot and clear that velocity; equality retains velocity and unordered NaN passes through. Signed integer bounds are FILD.
// Convert each position via605F00. Native all158 instructions/600 bytes independently paired with455370 after explicit globals and row-callee mapping. Title6F2434 uses
// current6F23D8/velocity6F23DC, bounds signed661E64..6F29C4, writes6F2440; draw46FD70 and label6F2958. Body6F24A4 uses current6F23CC/velocity6F23E0, bounds661E58..6F29C8,
// writes6F24B0. Black physical rectangle uses bodyX+10,bodyY6F24B4+10,width6F24B8,height6F24BC-20, respective scales, wrapped integer offsets and truncation,
// RGBA(0,0,0,128),live182ABB8; then body draw. Signed rows i0..<visible6F23C8, candidate=offset6F23E8+i wrapped; only candidate<LIVE count6F26AC guards456C90(candidate,i), NO lower
// bound. Render LIVE6F28A8 elements via416F70 and virtualslot0 with ECX receiver and NO pushed arguments. Finally458AA0 forwards residue. No interaction/readiness gate or null/cycle
// protection.
int rf_save_list_b_animate_and_draw()
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
  unk_6F23D8 = unk_6F23DC * rf_frame_delta_seconds + unk_6F23D8;
  if ( unk_6F23D8 >= (double)dword_661E64 )
  {
    if ( unk_6F23D8 > (double)unk_6F29C4 )
    {
      unk_6F23DC = 0.0;
      unk_6F23D8 = (float)unk_6F29C4;
    }
  }
  else
  {
    unk_6F23DC = 0.0;
    unk_6F23D8 = (float)dword_661E64;
  }
  unk_6F2440 = (int)unk_6F23D8;
  rf_ui_panel_render_bitmap(dword_6F2434);
  rf_ui_label_render((int)&unk_6F2958);
  unk_6F23CC = unk_6F23E0 * rf_frame_delta_seconds + unk_6F23CC;
  if ( unk_6F23CC >= (double)dword_661E58 )
  {
    if ( unk_6F23CC > (double)unk_6F29C8 )
    {
      unk_6F23E0 = 0.0;
      unk_6F23CC = (float)unk_6F29C8;
    }
  }
  else
  {
    unk_6F23E0 = 0.0;
    unk_6F23CC = (float)dword_661E58;
  }
  unk_6F24B0 = (int)unk_6F23CC;
  rf_render_color_set_rgba8(0, 0, 0, 128);
  v4 = unk_6F24B0 + 10;
  v3 = unk_6F24B4 + 10;
  v2 = unk_6F24BC - 20;
  rf_renderer_fill_rectangle_clipped(
    (int)((double)(unk_6F24B0 + 10) * rf_ui_scale_x),
    (int)((double)(unk_6F24B4 + 10) * rf_ui_scale_y),
    (int)((double)unk_6F24B8 * rf_ui_scale_x),
    (int)((double)(unk_6F24BC - 20) * rf_ui_scale_y),
    dword_182ABB8);
  rf_ui_panel_render_bitmap(dword_6F24A4);
  for ( i = 0; i < unk_6F23C8; ++i )
  {
    v5 = i + dword_6F23E8;
    if ( v5 >= rf_receiver_get_first_dword(dword_6F26AC) )
      break;
    rf_save_list_b_draw_record_row(v5, i);
  }
  for ( j = 0; j < rf_receiver_get_first_dword(&unk_6F28A8); ++j )
  {
    v0 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(&unk_6F28A8, j);
    (**(void (__thiscall ***)(_DWORD, _DWORD, int, int, int))*v0)(*v0, *v0, v2, v3, v4);
  }
  return rf_ui_draw_side_bars_and_overlays();
}

