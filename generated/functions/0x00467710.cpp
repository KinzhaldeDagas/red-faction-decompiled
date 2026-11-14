// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467710 rf_options_menu_leave_and_save_player_configuration
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Native noarg body;panel14 close dispatcher supplies ignored payload-address and immediate byte,NEITHER read. Clear
// BYTE661FF0;titleXspeed6F6024=-661E60,buttonXspeed6F601C=firstButtonWidth6F6124*close_x_scale,paneXspeed6F6028=-shared open speed. If localPlayer nonNULL,call
// save_configuration_file(player);then clear mainInput6F602C regardless save result. Always animated,even nonzero caller immediate byte;does not force closed coordinates,clear
// paneInput6F6000/current/pendingpane or handle save failure. Stored char return incidental/undefined when playerNULL.
char rf_options_menu_leave_and_save_player_configuration()
{
  char result; // al

  byte_661FF0 = 0;
  unk_6F6024 = -flt_661E60;
  unk_6F601C = (double)unk_6F6124 * rf_main_menu_close_x_speed_scale;
  unk_6F6028 = -rf_ui_open_transition_speed;
  if ( rf_local_fpgun_player )
    result = rf_player_save_configuration_file(rf_local_fpgun_player);
  unk_6F602C = 0;
  return result;
}

