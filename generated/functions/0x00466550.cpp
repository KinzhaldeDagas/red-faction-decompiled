// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00466550 rf_host_menu_begin_open_animation
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Noarg. Set buttonX speed6F5E40=firstButtonWidth6F5EFC*shared open_x_speed_scale (x87->binary32),titleX speed6F5E48=661E60;play49(0,0.0,1.0). Does not set
// positions,paneX speed,input flags or focus. Builder supplies them. Return sound residue.
int rf_host_menu_begin_open_animation()
{
  unk_6F5E40 = (double)unk_6F5EFC * rf_main_menu_open_x_speed_scale;
  unk_6F5E48 = flt_661E60;
  return rf_gamesound_play_event(49, 0, 0.0, 1.0);
}

