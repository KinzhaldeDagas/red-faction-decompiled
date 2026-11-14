// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00466590 rf_host_menu_begin_close_animation
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Noarg. Set buttonX speed6F5E40=firstButtonWidth*close_x_speed_scale,titleX speed6F5E48=-661E60,paneX speed6F5E4C=-shared open_vertical_speed;play48. No
// input/pending pane/position mutation,persistence or runtime teardown here. Shared speed named vertical drives pane X in draw routine.
int rf_host_menu_begin_close_animation()
{
  unk_6F5E40 = (double)unk_6F5EFC * rf_main_menu_close_x_speed_scale;
  unk_6F5E48 = -flt_661E60;
  unk_6F5E4C = -rf_ui_open_transition_speed;
  return rf_gamesound_play_event(48, 0, 0.0, 1.0);
}

