// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B6A60 rf_download_panel_frame
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, packet registry/function recovery, kill/download routing, native CRC/UI/startup and original geometry
// constants and native signed/x87/stack/callback ABI): Recovered [4B6A60,4B6A6F). No args consumed. Calls progress-overlay draw4B6AC0 FIRST, then input poll4B6A70 once. Escape
// teardown therefore follows that frame display. Does not tick transfer engine, query completion, block in a loop or reset tracked slot in this body.
void __cdecl rf_download_panel_frame()
{
  rf_download_draw_progress_overlay();
  rf_download_panel_poll_input();
}

