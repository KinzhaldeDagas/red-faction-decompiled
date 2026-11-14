// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F16D0 rf_ui_gadget_draw_inset_solid_face
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Args packed RGBA DWORD,inset. Sets color from packed argument bytes;draws solid rectangle at gadget absolute position+inset,size(width-2*inset,height-2*inset),render flag0x182ABB8. No clamping or color restore;returns rectangle draw result.
int __thiscall rf_ui_gadget_draw_inset_solid_face(_DWORD *this, int a2, int a3)
{
  int v3; // eax
  int v4; // eax
  int v6; // [esp-10h] [ebp-14h]
  int v7; // [esp-Ch] [ebp-10h]
  int v8; // [esp-8h] [ebp-Ch]
  int v9; // [esp-4h] [ebp-8h]

  rf_render_color_set_packed_rgba8((unsigned __int8 *)&a2);
  v9 = dword_182ABB8;
  v8 = *(this + 6) - 2 * a3;
  v7 = *(this + 5) - 2 * a3;
  v3 = rf_ui_gadget_absolute_y(this, 0);
  v6 = a3 + v3;
  v4 = rf_ui_gadget_absolute_x(this, 0);
  return rf_renderer_fill_rectangle_clipped(a3 + v4, v6, v7, v8, v9);
}

