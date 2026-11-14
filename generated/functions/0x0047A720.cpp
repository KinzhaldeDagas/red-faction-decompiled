// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A720 rf_level_browser_draw
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, liquid transition lifecycle, native x87 unordered comparisons, stable pointer erase, static runtime ownership and level-browser flow): 
// Cdecl no arguments. Resets fullscreen viewport, sets RGBA(0,255,0,128), draws centered x0x8000 text at y10 'Load Level' and y50 'Press ESC to leave, press Enter to load selected
// level', font global182ABBC,length-1. Calls ui_draw_windows_tooltips_and_drag_preview(NULL), returning delegate. No prior viewport/color restoration.
int rf_level_browser_draw()
{
  rf_renderer_reset_viewport_full_screen();
  rf_render_color_set_rgba8(0, 255, 0, 128);
  rf_font_draw_text_screen(0x8000, 10, "Load Level", -1, dword_182ABBC);
  rf_font_draw_text_screen(0x8000, 50, "Press ESC to leave, press Enter to load selected level", -1, dword_182ABBC);
  return rf_ui_draw_windows_tooltips_and_drag_preview(nullptr);
}

