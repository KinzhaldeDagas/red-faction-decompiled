// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004590D0 rf_main_menu_start_music
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one filename pointer slot. Calls4460D0; only returned AL exactly1 rejects, returns AL0 and does not change menu music handle. Every other byte proceeds
// to568A20(filename,float1). Zero full EAX from playback helper copies current owned backend voice into menu handle; nonzero writes menu handle-1. Both attempted-play paths return
// AL1, including helper failure; this is not playback-success Boolean. No filename validation or filename table lookup in this wrapper, upper EAX not normalized.
char __cdecl rf_main_menu_start_music(int a1)
{
  if ( rf_ui_get_raw_panel_byte6E6D94() == 1 )
    return 0;
  if ( rf_music_play_owned_filename(a1, 1.0) )
    rf_main_menu_music_handle = -1;
  else
    rf_main_menu_music_handle = rf_music_owned_backend_voice;
  return 1;
}

