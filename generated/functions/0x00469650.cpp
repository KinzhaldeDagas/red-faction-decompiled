// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00469650 rf_controls_draw_panel
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Cdecl logical panelX. Set root6F632C+12=arg;fill black alpha128 backing at scaled(panelX+105,panelY+10,width,height-20),integer sums before
// scaling/truncation;draw panel. For i0..<visibleRows and signed i+scroll<actionCount,draw row468960(i+scroll,i),no negative-scroll/index guard. Iterate EVERY draw-list6F68C0 control
// virtual0 with ECXthis and NO stack args;decompiler's five apparent args are leftover local values,not native ABI. No active/paneInput/capture gate,playerNULL check,save or color
// restore. EAX final list-count residue.
int __cdecl rf_controls_draw_panel(int a1)
{
  int result; // eax
  _DWORD *v2; // eax
  int v3; // [esp+4h] [ebp-24h]
  int v4; // [esp+8h] [ebp-20h]
  int v5; // [esp+Ch] [ebp-1Ch]
  int i; // [esp+14h] [ebp-14h]
  int j; // [esp+14h] [ebp-14h]

  unk_6F6338 = a1;
  rf_render_color_set_rgba8(0, 0, 0, 128);
  v5 = unk_6F6338 + 105;
  v4 = unk_6F633C + 10;
  v3 = unk_6F6344 - 20;
  rf_renderer_fill_rectangle_clipped(
    (int)((double)(unk_6F6338 + 105) * rf_ui_scale_x),
    (int)((double)(unk_6F633C + 10) * rf_ui_scale_y),
    (int)((double)unk_6F6340 * rf_ui_scale_x),
    (int)((double)(unk_6F6344 - 20) * rf_ui_scale_y),
    dword_182ABB8);
  rf_ui_panel_render_bitmap(dword_6F632C);
  for ( i = 0; i < unk_6F62A8 && i + dword_6F62B8 < dword_6F62AC; ++i )
    rf_controls_draw_action_binding_row(i + dword_6F62B8, i);
  for ( j = 0; ; ++j )
  {
    result = rf_receiver_get_first_dword(unk_6F68C0);
    if ( j >= result )
      break;
    v2 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F68C0, j);
    (**(void (__thiscall ***)(_DWORD, _DWORD, int, int, int))*v2)(*v2, *v2, v3, v4, v5);
  }
  return result;
}

