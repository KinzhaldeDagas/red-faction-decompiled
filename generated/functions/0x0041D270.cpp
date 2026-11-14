// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041D270 rf_corpse_initialize_list_count_register_shutdown
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Resets corpse intrusive head/tail to sentinel0x681AF8, sets global count0x681AF0=0, registers no-op shutdown hook0x41D2B0 with atexit, returns atexit result. Does not destroy preexisting records; repeated initialization loses links and resets count independently of allocated corpses.
int rf_corpse_initialize_list_count_register_shutdown()
{
  rf_corpse_list_head = &unk_681AF8;
  unk_681D88 = &unk_681AF8;
  unk_681AF0 = 0;
  return atexit(rf_corpse_shutdown_hook_noop);
}

