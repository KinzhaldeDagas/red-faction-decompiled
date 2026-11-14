// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453CA0 rf_extras_menu_select_previous
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments. Wrapped32 decrement selection6F1DAC FIRST. JNS tests sign of wrapped result, so only
// sign-bit-set results read firstDWORD focus-list count6F1F24 and store count-1 with32-bit wrap. Nonnegative results, including INT_MIN-1 wrappingINT_MAX, are retained without
// upper-bound check. Empty list can leave-1. Always568050(event40,group0,FLOAT0,FLOAT1), forwardEAX. No disabled-item skipping, focus repair, positive-count/active validation or
// normalized status.
int rf_extras_menu_select_previous()
{
  if ( --dword_6F1DAC < 0 )
    dword_6F1DAC = rf_receiver_get_first_dword(&unk_6F1F24) - 1;
  return rf_gamesound_play_event(40, 0, 0.0, 1.0);
}

