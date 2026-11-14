// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045FD70 rf_multiplayer_menu_leave_and_commit_name
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Cdecl(ignoredDWORD,immediate lowBYTE);first arg never read. Any nonzero immediate byte ->buttonX=closedX only,without resetting old velocities or sound. Zero
// ->title speed=-661E60,button speed=firstButtonWidth*close_x_speed_scale,play48. Both clear menu inputBYTE6F4868 then commit dirty name460A40. No explicit profile-input
// clear,current/pending-pane reset or character rollback. Return commit delegate/incidental EAX,not uniform close status;immediate path does not itself stop all animation.
int __cdecl rf_multiplayer_menu_leave_and_commit_name(int a1, char a2)
{
  if ( a2 )
  {
    unk_6F4854 = (float)rf_main_menu_closed_x;
  }
  else
  {
    unk_6F4860 = -flt_661E60;
    unk_6F4858 = (double)unk_6F48AC * rf_main_menu_close_x_speed_scale;
    rf_gamesound_play_event(48, 0, 0.0, 1.0);
  }
  unk_6F4868 = 0;
  return rf_multiplayer_profile_commit_dirty_name();
}

