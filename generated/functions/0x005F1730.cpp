// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1730 rf_ui_gadget_draw_bevel_edges
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thiscall args topLeftRGBA,bottomRightRGBA,thickness,inset. Gets absolute x/y,width20,height24,forwards all to rf_ui_draw_beveled_rect_edges0x5F1490. No fill,guard or render-state restore;return forwarded/incidental.
int __thiscall rf_ui_gadget_draw_bevel_edges(int *this, unsigned __int8 *a2, unsigned __int8 *a3, int a4, int a5)
{
  int v5; // eax
  int v7; // [esp-1Ch] [ebp-20h]
  int v8; // [esp-18h] [ebp-1Ch]
  int v9; // [esp-14h] [ebp-18h]

  v9 = *(this + 6);
  v8 = *(this + 5);
  v7 = rf_ui_gadget_absolute_y(this, 0);
  v5 = rf_ui_gadget_absolute_x(this, 0);
  return rf_ui_draw_beveled_rect_edges(v5, v7, v8, v9, a2, a3, a4, a5);
}

