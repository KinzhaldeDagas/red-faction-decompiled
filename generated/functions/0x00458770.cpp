// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00458770 rf_ui_draw_pointer_coordinate_overlay
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments.58AB60 fills local physical mouseX/Y and shared193A03C. Divide signed mouseX by LIVE FLOAT32 scale661E34, mouseY by661E38 via x87 FILD/FDIV
// and605F00 truncation, store signedDWORD logical values. Set RGBA(0,255,0,128). sprintf local32-byte buffer screen: (%d, %d), draw at(0,LIVE
// physicalHeight-10),length-1,fontDWORD182ABBC. Next sprintf panel:  (%d, %d) using wrapped(logicalX-signed661E54,logicalY-signed661E5C); these are fixed panel-origin offsets125,58,
// not live animated panel coordinates. Reread font and physical height, draw at(0,height-20). No zero/nonfinite-scale guard, clamping or viewport reset. Uses unbounded sprintf, but
// fixed formats and signed32 values; stack cookie epilogue. Forwards final drawing residue.
int rf_ui_draw_pointer_coordinate_overlay()
{
  int physical_screen_height; // eax
  int v1; // eax
  int v3; // [esp-4h] [ebp-30h]
  int v4; // [esp-4h] [ebp-30h]
  int v5; // [esp+0h] [ebp-2Ch] BYREF
  int v6; // [esp+4h] [ebp-28h] BYREF
  char Buffer[32]; // [esp+8h] [ebp-24h] BYREF

  rf_mouse_get_absolute_state(&v5, &v6, &unk_193A03C);
  v5 = (int)((double)v5 / rf_ui_scale_x);
  v6 = (int)((double)v6 / rf_ui_scale_y);
  rf_render_color_set_rgba8(0, 255, 0, 128);
  sprintf(Buffer, "screen: (%d, %d)", v5, v6);
  v3 = dword_182ABBC;
  physical_screen_height = rf_renderer_get_physical_screen_height();
  rf_font_draw_text_screen(0, physical_screen_height - 10, (unsigned __int8 *)Buffer, -1, v3);
  sprintf(Buffer, "panel:  (%d, %d)", v5 - rf_main_menu_title_x_lower_bound, v6 - rf_main_menu_title_y);
  v4 = dword_182ABBC;
  v1 = rf_renderer_get_physical_screen_height();
  return rf_font_draw_text_screen(0, v1 - 20, (unsigned __int8 *)Buffer, -1, v4);
}

