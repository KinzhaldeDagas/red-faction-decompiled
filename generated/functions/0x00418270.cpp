// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00418270 rf_physical_debris_list_init
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Resets physical-debris intrusive list head/tail to its sentinel and registers no-op shutdown hook 0x4182A0 with atexit, returning atexit status. Does NOT reset physical-debris count or destroy existing records; repeated initialization loses old links while count can remain stale.
int rf_physical_debris_list_init()
{
  rf_physical_debris_list_head = &rf_physical_debris_list_sentinel;
  rf_physical_debris_list_tail = &rf_physical_debris_list_sentinel;
  return atexit(rf_physical_debris_shutdown_hook_noop);
}

