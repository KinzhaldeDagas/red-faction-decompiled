// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045A0D0 rf_main_menu_fade_owned_music
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Load current owned backend voice into EAX; unequal menu-owned handle returns that raw DWORD without action. Equal pushes integer1000 to568C40
// fade helper, cleanup4, forwards its EAX. Equality is the only native guard, including equal sentinel handles; no separate valid/live-handle test, own handle clear or normalized
// result.
int rf_main_menu_fade_owned_music()
{
  int result; // eax

  result = rf_music_owned_backend_voice;
  if ( rf_music_owned_backend_voice == rf_main_menu_music_handle )
    return rf_music_owned_fade(1000);
  return result;
}

