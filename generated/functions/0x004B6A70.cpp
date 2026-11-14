// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B6A70 rf_download_panel_poll_input
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, packet registry/function recovery, kill/download routing, native CRC/UI/startup and original geometry
// constants and native signed/x87/stack/callback ABI): No arguments. Calls ui_poll_and_dispatch_event(handler4B6A90,0), TWO explicit stack arguments with8-byte caller cleanup; not a
// one-argument call despite saved decompiler prototype. One poll per call, no loop, rendering, slot update or progress clamp. Return is delegate residue.
char rf_download_panel_poll_input()
{
  return rf_ui_poll_and_dispatch_event(rf_download_panel_handle_key);
}

