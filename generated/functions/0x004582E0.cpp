// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004582E0 rf_game_key_help_render
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Reset full viewport, set current color RGBA(0,255,0,128), draw literal Game Keys at raw screen(0x8000,10),length-1,fontDWORD182ABBC. Reset
// shared row cursor458500 and make26 calls458530, including five blank spacer rows whose two strings begin NUL in original PE. Fixed retail rows: Run Forward/A,Run
// Backward/Z,Sneak/Shift hold,Jump/Spacebar,Crouch/C; Turn Left/Right KEYPAD4/6,Look Up/Down8/2,Slide Left/Right1/3,Slide Up/Down(flying only)+/Enter,Bank Left/Right(flying
// only)7/9;Toggle Walk/Fly Backspace;Fire Ctrl/Mouse1,Alternate Fire Mouse2,Reload R,Holster H,Cycle To Next Weapon comma;12mm1,Sniper Rifle2,Rocket Launcher3;Use Enter (literal
// bytes AT6358A8 are Use, not a pointer table);Console Tilde. Rows are descriptive fixed text: no input handling, binding lookup or movement-state mutation. Calls cdecl and cleans8
// for each row; forwards final row EAX without normalization.
int rf_game_key_help_render()
{
  rf_renderer_reset_viewport_full_screen();
  rf_render_color_set_rgba8(0, 255, 0, 128);
  rf_font_draw_text_screen(0x8000, 10, "Game Keys", -1, dword_182ABBC);
  rf_key_help_reset_row_cursor();
  rf_key_help_draw_row("Run Forward", "A");
  rf_key_help_draw_row("Run Backward", "Z");
  rf_key_help_draw_row("Sneak", "Shift (hold down)");
  rf_key_help_draw_row("Jump", "Spacebar");
  rf_key_help_draw_row("Crouch", "C");
  rf_key_help_draw_row(&byte_6356DB, &byte_6356DA);
  rf_key_help_draw_row("Turn Left/Right", "KEYPAD 4/6");
  rf_key_help_draw_row("Look Up/Down", "KEYPAD 8/2");
  rf_key_help_draw_row("Slide Left/Right", "KEYPAD 1/3");
  rf_key_help_draw_row("Slide Up/Down (flying only)", "KEYPAD +/Enter");
  rf_key_help_draw_row("Bank Left/Right (flying only)", "KEYPAD 7/9");
  rf_key_help_draw_row(&byte_6356DF, &byte_6356DE);
  rf_key_help_draw_row("Toggle Walk/Fly", "Backspace");
  rf_key_help_draw_row(&byte_6356EF, &byte_6356EE);
  rf_key_help_draw_row("Fire", "Ctrl, Mouse 1");
  rf_key_help_draw_row("Alternate Fire", "Mouse 2");
  rf_key_help_draw_row("Reload", "R");
  rf_key_help_draw_row("Holster", "H");
  rf_key_help_draw_row("Cycle To Next Weapon", ",");
  rf_key_help_draw_row(&byte_6356FE, &byte_6356FD);
  rf_key_help_draw_row("12mm", "1");
  rf_key_help_draw_row("Sniper Rifle", "2");
  rf_key_help_draw_row("Rocket Launcher", "3");
  rf_key_help_draw_row(&byte_635712, &byte_6356FF);
  rf_key_help_draw_row((const char *)&off_6358A8, "Enter");
  return rf_key_help_draw_row("Console", "Tilde");
}

