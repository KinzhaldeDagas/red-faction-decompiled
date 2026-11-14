// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453990 rf_endgame_render_background_and_scrolled_centered_text
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments. Only SIGNED bitmapDWORD661DD0>=0 calls576450(handle,&localWidth,&localHeight),
// ignores status, then572180(handle,dest0,0,CURRENT physicalWidth,CURRENT physicalHeight,source0,0,localWidth,localHeight,flip0,0,mode187CD34). Height queried before width due native
// push order; raw handle reread for blit. Negative handle skips ONLY background block. No own decoded-frame/dimension validation.  Then query physical heights H1,H2, compute
// signed32_wrap(H1-2*trunc(H2/8)); query physicalWidth W; query height H3 and trunc(H3/8). Call571A30(viewportLeft0,top=trunc(H3/8),widthW,height=H1-2*trunc(H2/8)), preserving three
// distinct height samples and native signed32 arithmetic. Set renderRGBA(255,255,255,192). Convert current F32 scrollY6F158C through605F00 (native truncation helper) and
// draw58CFC0(centerX0x8000,convertedY,text6F1598,fontCURRENT6F1588,modeCURRENT182ABBC). No additional fade, y-range, clipping/finite guard or blank-text gate. Viewport/current
// color/font/pen side effects are left in place, no restore. Full EAX is final font-draw value/residue, no canonical success.
int rf_endgame_render_background_and_scrolled_centered_text()
{
  int physical_screen_width; // eax
  int v1; // esi
  int v2; // eax
  int physical_screen_height; // [esp-20h] [ebp-2Ch]
  int v5; // [esp-14h] [ebp-20h]
  int v6; // [esp-10h] [ebp-1Ch]
  int v7; // [esp-8h] [ebp-14h]
  int v8; // [esp-4h] [ebp-10h]
  int v9; // [esp-4h] [ebp-10h]
  int v10; // [esp+4h] [ebp-8h] BYREF
  int v11; // [esp+8h] [ebp-4h] BYREF

  if ( dword_661DD0 >= 0 )
  {
    rf_bitmap_get_resolved_dimensions(dword_661DD0, &v10, &v11);
    v8 = unk_187CD34;
    v6 = v11;
    v5 = v10;
    physical_screen_height = rf_renderer_get_physical_screen_height();
    physical_screen_width = rf_renderer_get_physical_screen_width();
    rf_bitmap_blit_subrectangle_backend_dispatch(
      dword_661DD0,
      0,
      0,
      physical_screen_width,
      physical_screen_height,
      0,
      0,
      v5,
      v6,
      0,
      0,
      v8);
  }
  v1 = rf_renderer_get_physical_screen_height();
  v9 = v1 - 2 * (rf_renderer_get_physical_screen_height() / 8);
  v7 = rf_renderer_get_physical_screen_width();
  v2 = rf_renderer_get_physical_screen_height();
  rf_renderer_set_viewport_and_relative_clip(0, v2 / 8, v7, v9);
  rf_render_color_set_rgba8(255, 255, 255, 192);
  return rf_font_draw_text_screen(0x8000, (int)unk_6F158C, (unsigned __int8 *)byte_6F1598, dword_6F1588, dword_182ABBC);
}

