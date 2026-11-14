// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00460550 rf_multiplayer_profile_disable_input_and_schedule_hide
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. Clear inputBYTE6F4850. If currentPane661F8C!=-1,store pendingPane661F90=-1 and profile speed6F4864=-shared open speed. If already current-1,preserve
// pending/velocity (even when another pending value exists). Does not immediately change current pane,commit edited name,reset edit latch or play sound. Native helper may overwrite
// caller's earlier speed write.
void rf_multiplayer_profile_disable_input_and_schedule_hide()
{
  byte_6F4850[0] = 0;
  if ( dword_661F8C != -1 )
  {
    dword_661F90 = -1;
    unk_6F4864 = -rf_ui_open_transition_speed;
  }
}

