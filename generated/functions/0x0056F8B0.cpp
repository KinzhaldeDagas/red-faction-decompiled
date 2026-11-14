// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056F8B0 rf_console_draw_colored_text_overlay
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): cdecl(x,y,text,RGBApointer). Sets packed render color from pointer,then calls screen font draw with fontID-1 and global renderMode182ABBC. Returns underlying incidental EAX;no text copy,markup parsing,capacity check or global console visibility gate.
int __cdecl rf_console_draw_colored_text_overlay(int a1, int a2, unsigned __int8 *a3, unsigned __int8 *a4)
{
  rf_render_color_set_packed_rgba8(a4);
  return rf_font_draw_text_screen(a1, a2, a3, -1, dword_182ABBC);
}

