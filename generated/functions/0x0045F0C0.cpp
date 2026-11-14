// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045F0C0 rf_multiplayer_rules_draw_panel
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): Cdecl logical panelX. Set RGBA(0,0,0,128),fill scaled rectangle((x+105),(parentY6F3ED4+10),parentWidth6F3ED8,(parentHeight6F3EDC-20)) using truncTowardZero and
// renderer182ABB8. Store parentX6F3ED0=x AFTER fill,draw parent46FD70,then iterate draw-list6F4298 count via native getter and call EVERY control vtable0 withECX=this and NO stack
// args. Decompiler's apparent5-argument virtual call is false:stale locals are not arguments. No own NULL/state guards,color restore,focus/input update or gameplay-rule apply. Return
// final draw-list count residue,not success.
int __cdecl rf_multiplayer_rules_draw_panel(int a1)
{
  int result; // eax
  _DWORD *v2; // eax
  int v3; // [esp+4h] [ebp-20h]
  int v4; // [esp+8h] [ebp-1Ch]
  int v5; // [esp+Ch] [ebp-18h]
  int i; // [esp+10h] [ebp-14h]

  rf_render_color_set_rgba8(0, 0, 0, 128);
  v5 = a1 + 105;
  v4 = unk_6F3ED4 + 10;
  v3 = unk_6F3EDC - 20;
  rf_renderer_fill_rectangle_clipped(
    (int)((double)(a1 + 105) * rf_ui_scale_x),
    (int)((double)(unk_6F3ED4 + 10) * rf_ui_scale_y),
    (int)((double)unk_6F3ED8 * rf_ui_scale_x),
    (int)((double)(unk_6F3EDC - 20) * rf_ui_scale_y),
    dword_182ABB8);
  unk_6F3ED0 = a1;
  rf_ui_panel_render_bitmap(dword_6F3EC4);
  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(dword_6F4298);
    if ( i >= result )
      break;
    v2 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F4298, i);
    (**(void (__thiscall ***)(_DWORD, _DWORD, int, int, int))*v2)(*v2, *v2, v3, v4, v5);
  }
  return result;
}

