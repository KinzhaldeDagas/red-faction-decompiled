// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1780 rf_ui_gadget_draw_raised_face
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Args palette pointer,thickness. Absolute position;fill inset rectangle using palette+8,then bevel helper0x5F1490(x,y,w,h,palette+0,palette+4,thickness,0). No extent guard/color restore. Returns bevel result;edge-order reversed by sunken variant.
int __thiscall rf_ui_gadget_draw_raised_face(int *this, unsigned __int8 *a2, int a3)
{
  int v5; // [esp+4h] [ebp-8h]
  int v6; // [esp+8h] [ebp-4h]

  v5 = rf_ui_gadget_absolute_x(this, 0);
  v6 = rf_ui_gadget_absolute_y(this, 0);
  rf_render_color_set_packed_rgba8(a2 + 8);
  rf_renderer_fill_rectangle_clipped(a3 + v5, a3 + v6, *(this + 5) - 2 * a3, *(this + 6) - 2 * a3, dword_182ABB8);
  return rf_ui_draw_beveled_rect_edges(v5, v6, *(this + 5), *(this + 6), a2, a2 + 4, a3, 0);
}

