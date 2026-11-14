// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046B2A0 rf_performance_draw_panel
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Cdecl logical panelX. Store root6F69D4+12=arg. Fill black alpha128 backing at trunc((panelX+105)*scaleX),trunc((panelY+10)*scaleY),scaled
// width,(height-20),integer additions BEFORE scaling;draw panel. Iterate every draw-list6F7840 control virtual0 via ECXthis,NO stack args;decompiler fake receiver/five args are
// leftover locals. No input/active/changed-setting guard,player dereference,options apply,save or color restore;EAX final count residue.
int __cdecl rf_performance_draw_panel(int a1)
{
  int result; // eax
  _DWORD *v2; // eax
  int v3; // [esp+4h] [ebp-20h]
  int v4; // [esp+8h] [ebp-1Ch]
  int v5; // [esp+Ch] [ebp-18h]
  int i; // [esp+10h] [ebp-14h]

  unk_6F69E0 = a1;
  rf_render_color_set_rgba8(0, 0, 0, 128);
  v5 = unk_6F69E0 + 105;
  v4 = unk_6F69E4 + 10;
  v3 = unk_6F69EC - 20;
  rf_renderer_fill_rectangle_clipped(
    (int)((double)(unk_6F69E0 + 105) * rf_ui_scale_x),
    (int)((double)(unk_6F69E4 + 10) * rf_ui_scale_y),
    (int)((double)unk_6F69E8 * rf_ui_scale_x),
    (int)((double)(unk_6F69EC - 20) * rf_ui_scale_y),
    dword_182ABB8);
  rf_ui_panel_render_bitmap(dword_6F69D4);
  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(dword_6F7840);
    if ( i >= result )
      break;
    v2 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F7840, i);
    (**(void (__thiscall ***)(_DWORD, _DWORD, int, int, int))*v2)(*v2, *v2, v3, v4, v5);
  }
  return result;
}

