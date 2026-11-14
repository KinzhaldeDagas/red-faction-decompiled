// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045A130 rf_ui_draw_saving_overlay
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Noarg. Copy original ten bytes "Saving..." plus NUL into stack string. Set render RGBA(0,0,0,128),get physical height then
// width,fill clipped rectangle(0,0,width,height,global182ABB8). Then set RGBA(255,255,255,255),draw fixed text at(300,200) with limit-1 and font/global182ABBC. No localization,
// coordinate scaling/centering, previous-color restore or actual save operation in this body. Called by player render view44459F; drawing helper's nominal return remains incidental.
// Cookie check preserved.
int rf_ui_draw_saving_overlay()
{
  int physical_screen_width; // eax
  int physical_screen_height; // [esp-8h] [ebp-18h]
  int v3; // [esp-4h] [ebp-14h]
  char v4[12]; // [esp+0h] [ebp-10h] BYREF

  strcpy(v4, "Saving...");
  rf_render_color_set_rgba8(0, 0, 0, 128);
  v3 = dword_182ABB8;
  physical_screen_height = rf_renderer_get_physical_screen_height();
  physical_screen_width = rf_renderer_get_physical_screen_width();
  rf_renderer_fill_rectangle_clipped(0, 0, physical_screen_width, physical_screen_height, v3);
  rf_render_color_set_rgba8(255, 255, 255, 255);
  return rf_font_draw_text_screen(300, 200, (unsigned __int8 *)v4, -1, dword_182ABBC);
}

