// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045D180 rf_multiplayer_setup_draw_panel_and_level_rows
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Cdecl logical panelX. Set RGBA(0,0,0,128),fill scaled
// rectangle((x+105),(parentY6F2D1C+10),parentWidth6F2D20,(parentHeight6F2D24-20)) with all conversions truncTowardZero and backend182ABB8. Store parentX6F2D18=x AFTER fill;draw
// parent46FD70,then every draw-list6F3788 control via vtable0/ECXthis,without own state/null checks. For visible ordinal0..<visibleRows6F2CF0,stop at
// signed(scroll+ordinal)>=filteredCount;draw row45B8A0(scroll+ordinal,ordinal). No lower-bound check on scroll+ordinal here. Query467350 AL at end;zero clears editLatch6F2D01,nonzero
// preserves. Does not update selection/scroll,restore color or send. Return incidental AL/upper EAX state,not draw count.
int __cdecl rf_multiplayer_setup_draw_panel_and_level_rows(int a1)
{
  _DWORD *v1; // eax
  int v2; // esi
  int result; // eax
  int i; // [esp+14h] [ebp-14h]
  int j; // [esp+14h] [ebp-14h]

  rf_render_color_set_rgba8(0, 0, 0, 128);
  rf_renderer_fill_rectangle_clipped(
    (int)((double)(a1 + 105) * rf_ui_scale_x),
    (int)((double)(unk_6F2D1C + 10) * rf_ui_scale_y),
    (int)((double)unk_6F2D20 * rf_ui_scale_x),
    (int)((double)(unk_6F2D24 - 20) * rf_ui_scale_y),
    dword_182ABB8);
  unk_6F2D18 = a1;
  rf_ui_panel_render_bitmap(dword_6F2D0C);
  for ( i = 0; i < rf_receiver_get_first_dword(dword_6F3788); ++i )
  {
    v1 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F3788, i);
    (**(void (__thiscall ***)(_DWORD))*v1)(*v1);
  }
  for ( j = 0; j < unk_6F2CF0; ++j )
  {
    v2 = dword_6F2D04 + j;
    if ( v2 >= rf_receiver_get_first_dword(dword_6F2DC4) )
      break;
    rf_multiplayer_level_list_draw_row(dword_6F2D04 + j, j);
  }
  LOBYTE(result) = rf_host_menu_pane_input_byte_get();
  if ( !(_BYTE)result )
    unk_6F2D01 = 0;
  return result;
}

