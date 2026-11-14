// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00458290 rf_frontend_help_render_selected_page
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Snapshot raw DWORD6F2998: exact0 calls4582E0 Game Keys help, exact1 calls458590 Developer Keys help, all other values skip page draw. Always
// afterwards58CFC0(x8000,y470,literal Use Arrow Keys To Cycle Through Help Screens,fontID-1,renderMode LIVE182ABBC), caller cleanup20, forwards helperEAX. No page clamp/default
// substitution, viewport reset, color restore or binding/input changes in this wrapper. Labels describe controls rather than implementing them.
int rf_frontend_help_render_selected_page()
{
  if ( dword_6F2998 )
  {
    if ( dword_6F2998 == 1 )
      rf_developer_key_help_render();
  }
  else
  {
    rf_game_key_help_render();
  }
  return rf_font_draw_text_screen(0x8000, 470, "Use Arrow Keys To Cycle Through Help Screens", -1, dword_182ABBC);
}

