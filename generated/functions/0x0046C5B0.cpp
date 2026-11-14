// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046C5B0 rf_gameplay_draw_panel_and_priority_rows
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Cdecl logical panelX. Store root6F7BDC+12;fill black alpha128 backing at scaled(panelX+105,panelY+10,width,height-20),integer sums before
// scale/truncation;draw panel. For i0..<visibleRows6F7B68 while signed i+scroll6F7B84<count6F7B7C,draw row46BBF0(i+scroll,i). No negative-scroll admission here;row routine validates
// physical indices/player/weaponID after highlight. Iterate every draw-list6F8320 control virtual0 ECXthis/NO stack args;decompiler five apparent args false. No active/paneInput
// gate,swap,save or color restore;EAX final list-count residue.
int __cdecl rf_gameplay_draw_panel_and_priority_rows(int a1)
{
  int result; // eax
  _DWORD *v2; // eax
  int v3; // [esp+4h] [ebp-24h]
  int v4; // [esp+8h] [ebp-20h]
  int v5; // [esp+Ch] [ebp-1Ch]
  int i; // [esp+14h] [ebp-14h]
  int j; // [esp+14h] [ebp-14h]

  unk_6F7BE8 = a1;
  rf_render_color_set_rgba8(0, 0, 0, 128);
  v5 = unk_6F7BE8 + 105;
  v4 = unk_6F7BEC + 10;
  v3 = unk_6F7BF4 - 20;
  rf_renderer_fill_rectangle_clipped(
    (int)((double)(unk_6F7BE8 + 105) * rf_ui_scale_x),
    (int)((double)(unk_6F7BEC + 10) * rf_ui_scale_y),
    (int)((double)unk_6F7BF0 * rf_ui_scale_x),
    (int)((double)(unk_6F7BF4 - 20) * rf_ui_scale_y),
    dword_182ABB8);
  rf_ui_panel_render_bitmap(dword_6F7BDC);
  for ( i = 0; i < unk_6F7B68 && i + dword_6F7B84 < unk_6F7B7C; ++i )
    rf_gameplay_priority_draw_weapon_row(i + dword_6F7B84, i);
  for ( j = 0; ; ++j )
  {
    result = rf_receiver_get_first_dword(dword_6F8320);
    if ( j >= result )
      break;
    v2 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F8320, j);
    (**(void (__thiscall ***)(_DWORD, _DWORD, int, int, int))*v2)(*v2, *v2, v3, v4, v5);
  }
  return result;
}

