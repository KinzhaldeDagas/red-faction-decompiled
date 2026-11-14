// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00491820 rf_respawn_register_name_cleanup_at_exit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Cdecl no arguments. Registers491840 via atexit,returns registration result. Does not clear names/count immediately or prevent duplicate registration. Invoked by multiplayer process
// initializer.
int rf_respawn_register_name_cleanup_at_exit()
{
  return atexit(rf_respawn_clear_all_slot_names);
}

