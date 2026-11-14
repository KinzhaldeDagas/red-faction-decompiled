// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00458590 rf_developer_key_help_render
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Reset full viewport, set RGBA(0,255,0,128), draw Debug Keys at raw screen(0x8000,10),length-1,fontDWORD182ABBC; reset458500 then23 cdecl458530
// rows, including six NUL-string spacer pairs. Fixed labels describe Debug+1/2/3 camera modes,W all weapons,I self invulnerability,K kill self,Shift+K kill robots,Shift+Alt+K kill
// objects,S/A next target animation state/action,Spacebar play target animation,X/Z next first-person gun state/action,Spacebar play first-person action,ai_pause console pause,O
// closest-target cycling,T reticule target. Literal spelling and duplicate Spacebar descriptions preserved. This renderer performs no camera/AI/weapon/target/cheat mutation and does
// not dispatch these keys. No binding lookup/localization or enabled gate; returns final row EAX.
int rf_developer_key_help_render()
{
  rf_renderer_reset_viewport_full_screen();
  rf_render_color_set_rgba8(0, 255, 0, 128);
  rf_font_draw_text_screen(0x8000, 10, "Debug Keys", -1, dword_182ABBC);
  rf_key_help_reset_row_cursor();
  rf_key_help_draw_row("Debug + 1", "First person camera");
  rf_key_help_draw_row("Debug + 2", "Floating camera");
  rf_key_help_draw_row("Debug + 3", "Third person camera");
  rf_key_help_draw_row(&byte_63571A, &byte_635713);
  rf_key_help_draw_row("Debug + W", "All weapons");
  rf_key_help_draw_row("Debug + I", "Make self invlunerable");
  rf_key_help_draw_row(&byte_635725, &byte_63571B);
  rf_key_help_draw_row("Debug + K", "Kill self");
  rf_key_help_draw_row("Debug + Shift + K", "Kill all robots in the level");
  rf_key_help_draw_row("Debug + Shift + Alt + K", "Kill all objects in the level");
  rf_key_help_draw_row(&byte_635727, &byte_635726);
  rf_key_help_draw_row("Debug + S", "Force switch to next animation state (for current target)");
  rf_key_help_draw_row("Debug + A", "Force switch to next animation action (for current target)");
  rf_key_help_draw_row("Debug + Spacebar", "Play current animation action (for current target)");
  rf_key_help_draw_row(&byte_63572E, &byte_63572D);
  rf_key_help_draw_row("Debug + X", "Force switch to next first-person gun animation state");
  rf_key_help_draw_row("Debug + Z", "Force switch to next first-person gun action");
  rf_key_help_draw_row("Debug + Spacebar", "Play current first-person gun animation action");
  rf_key_help_draw_row(&byte_635732, &byte_63572F);
  rf_key_help_draw_row("ai_pause", "(from console) pauses AI");
  rf_key_help_draw_row(&byte_63573B, &byte_635733);
  rf_key_help_draw_row("O", "Target closest object (press again quickly to target next closest)");
  return rf_key_help_draw_row("T", "Target object in reticule");
}

