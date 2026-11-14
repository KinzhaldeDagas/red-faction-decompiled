// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B6A40 rf_download_panel_initialize
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, packet registry/function recovery, kill/download routing, native CRC/UI/startup and original geometry
// constants and native signed/x87/stack/callback ABI): Recovered [4B6A40,4B6A4F). No args consumed. Writes ONLY tracked download slotDWORD7B4DE4=-1; does not cancel/release prior
// slot, initialize transfer engine, set filename or draw.
void __cdecl rf_download_panel_initialize()
{
  dword_7B4DE4 = -1;
}

