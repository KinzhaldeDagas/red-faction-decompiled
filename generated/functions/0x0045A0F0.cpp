// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045A0F0 rf_main_menu_stop_owned_music
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Loads current owned music backend voice into EAX and compares with menu-owned handle. Unequal returns that loaded DWORD without helper call or
// stores. Equal calls568C10 owned reset/stop, forwarding its EAX. Equality is the ONLY guard here, including equality of sentinel values; no separate live-handle test or menu-handle
// clear in this wrapper. Backend reset/stop validation is delegated.
int rf_main_menu_stop_owned_music()
{
  int result; // eax

  result = rf_music_owned_backend_voice;
  if ( rf_music_owned_backend_voice == rf_main_menu_music_handle )
    return rf_music_owned_reset_and_stop();
  return result;
}

