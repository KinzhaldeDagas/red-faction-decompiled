// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417700 rf_monitor_list_initialize_and_register_shutdown
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Resets intrusive monitor sentinel head/tail at 0x6807E4/0x6807E8 to &0x6807E4 and registers monitor-record destruction 0x417640 with atexit. Returns atexit result. No destruction of old records or repeated-init guard.
int rf_monitor_list_initialize_and_register_shutdown()
{
  dword_6807E4 = &dword_6807E4;
  unk_6807E8 = &dword_6807E4;
  return atexit(rf_monitor_destroy_all_records);
}

