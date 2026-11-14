// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B6A90 rf_download_panel_handle_key
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, packet registry/function recovery, kill/download routing, native CRC/UI/startup and original geometry
// constants and native signed/x87/stack/callback ABI): cdecl FULL-DWORD key. Only EXACT1 (Escape) calls multiplayer_runtime_teardown(), then request_panel_immediate(2,0). Other keys
// do nothing. Does not modify/consume key slot, cancel only one slot, check transfer progress or mask modifiers. Native callback receives key by value; existing absent stored type
// retained. EAX incidental key/delegate result.
int __cdecl rf_download_panel_handle_key(int a1)
{
  int result; // eax

  result = a1;
  if ( a1 == 1 )
  {
    rf_multiplayer_runtime_teardown();
    return rf_ui_request_panel_immediate(2, 0);
  }
  return result;
}

