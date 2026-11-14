// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F15F0 rf_ui_draw_raised_rect
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl x,y,w,h,palette,thickness. Sets color paletteRGBA+8,draws inset solid rectangle(x+t,y+t,w-2t,h-2t) with global solid flag;then draws bevel edges via0x5F1490(x,y,w,h,palette+0,palette+4,thickness,0). Does not validate sizes,restore color or set/reset clipping;return bevel helper result.
int __cdecl rf_ui_draw_raised_rect(int a1, int a2, int a3, int a4, unsigned __int8 *a5, int a6)
{
  rf_render_color_set_packed_rgba8(a5 + 8);
  rf_renderer_fill_rectangle_clipped(a6 + a1, a6 + a2, a3 - 2 * a6, a4 - 2 * a6, dword_182ABB8);
  return rf_ui_draw_beveled_rect_edges(a1, a2, a3, a4, a5, a5 + 4, a6, 0);
}

