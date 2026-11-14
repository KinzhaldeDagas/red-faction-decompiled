// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046D710 rf_audio_draw_panel
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Cdecl logical panelX. Store root6F8514+12. Fill black alpha128 backing at trunc((panelX+105)*scaleX),trunc((panelY+65)*scaleY),scaled
// width/(height-75),integer sums before scaling;draw panel. Iterate every draw-list6F88C4 control virtual0 ECXthis/NO stack args (decompiler five-arg form false). No
// active/paneInput/channel gain apply,player check,save or color restore;EAX final count residue. Audio backing Y65/height-75 differs from other options panels Y10/height-20.
int __cdecl rf_audio_draw_panel(int a1)
{
  int result; // eax
  _DWORD *v2; // eax
  int v3; // [esp+4h] [ebp-20h]
  int v4; // [esp+8h] [ebp-1Ch]
  int v5; // [esp+Ch] [ebp-18h]
  int i; // [esp+10h] [ebp-14h]

  unk_6F8520 = a1;
  rf_render_color_set_rgba8(0, 0, 0, 128);
  v5 = unk_6F8520 + 105;
  v4 = unk_6F8524 + 65;
  v3 = unk_6F852C - 75;
  rf_renderer_fill_rectangle_clipped(
    (int)((double)(unk_6F8520 + 105) * rf_ui_scale_x),
    (int)((double)(unk_6F8524 + 65) * rf_ui_scale_y),
    (int)((double)unk_6F8528 * rf_ui_scale_x),
    (int)((double)(unk_6F852C - 75) * rf_ui_scale_y),
    dword_182ABB8);
  rf_ui_panel_render_bitmap(dword_6F8514);
  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(dword_6F88C4);
    if ( i >= result )
      break;
    v2 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F88C4, i);
    (**(void (__thiscall ***)(_DWORD, _DWORD, int, int, int))*v2)(*v2, *v2, v3, v4, v5);
  }
  return result;
}

