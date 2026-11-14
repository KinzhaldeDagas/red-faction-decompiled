// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459520 rf_main_menu_begin_open_transition
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. FILD signed DWORD6F2A6C, multiply stored open-X scale and store binary32 X velocity. Copies opening titlebar-X float into titlebar-X velocity
// without negation. Calls568050(event49,0,float0,float1), caller cleanup16, forwards EAX. No current-position initialization or interaction-active write; contrast closing459060
// solely in scale/titlebar-X sign/event.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Axis correction verified against native coordinate helpers46FC70/46FCA0 and title initialization: animated title field6F2C8C is receiver6F2C80+12, X.
// Current6F29D8 and velocity6F2A08 are title X; title Y at+16 remains a separate constructor coordinate. Shared661E50 is an opening transition speed, not a universal vertical speed.
// Prior detailed contract retained with corrected axes.
int rf_main_menu_begin_open_transition()
{
  rf_main_menu_x_velocity = (double)unk_6F2A6C * rf_main_menu_open_x_speed_scale;
  rf_main_menu_title_x_velocity = rf_ui_open_transition_speed;
  return rf_gamesound_play_event(49, 0, 0.0, 1.0);
}

