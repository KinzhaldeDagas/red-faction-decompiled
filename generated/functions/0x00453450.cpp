// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453450 rf_endgame_panel_initialize_text_font_bitmap_and_deadline
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments. Query physical screen height570F70 TWICE: compute
// signed32_wrap(firstHeight-2*truncTowardZero(secondHeight/8)), using native signed division-by8 sequence and wrapped shift/subtraction; storeF32 at scrollY6F158C. Do not replace
// with0.75*one cached height. Call4534F0 endgame text loader BEFORE font choice. Query physical width570F60: SIGNED width>640 selects fontDWORD88E438, otherwise fontDWORD663050,
// storing6F1588. Measure loaded text6F1598 via58C130(widthOut6F1D98,heightOut6F1594,text6F1598,maxBytes-1,chosenFont). Loader wrapping already used font-1/default, independently of
// this later font choice.  Unconditionally load 'demo-gameover.tga' with574E90(name,-1,0), overwrite global bitmap661DD0 with raw result; no prior handle release or cache gate.
// Then55F1F0(this=deadline6F1DA0,offset1000ms) arms against UNPAUSED wrapped clock663E94, distinct from game-clock663E90. Forward setter's path-dependent EAX residue, not bool. No
// zero/negative size or text/bitmap validation, mouse/music initialization, pause/authority admission or rollback.
int rf_endgame_panel_initialize_text_font_bitmap_and_deadline()
{
  int physical_screen_height; // esi

  physical_screen_height = rf_renderer_get_physical_screen_height();
  unk_6F158C = (float)(physical_screen_height - 2 * (rf_renderer_get_physical_screen_height() / 8));
  rf_endgame_load_all_matching_localized_wrapped_text();
  if ( rf_renderer_get_physical_screen_width() > 640 )
    dword_6F1588 = rf_hud_countdown_font;
  else
    dword_6F1588 = dword_663050;
  rf_font_measure_text_extent(dword_6F1D98, &dword_6F1594, (unsigned __int8 *)byte_6F1598, -1, dword_6F1588);
  dword_661DD0 = rf_bitmap_load_with_optional_mipmap_generation("demo-gameover.tga", (void *)0xFFFFFFFF, 0);
  return rf_clock_deadline_set_wrapped_offset((int *)&unk_6F1DA0, 1000);
}

