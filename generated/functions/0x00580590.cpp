// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580590 rf_volume_system_initialize
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Calls one-time math table initializer567600,releases owned pointer-array backing18CCFF4,registers cleanup5805C0 with atexit,and returns atexit result. Does not individually delete volume objects before release;intended initialization path,not safe replacement for populated-system reset. Does not release active-list backing here.
int rf_volume_system_initialize()
{
  rf_initialize_sqrt_rsqrt_lookup_tables_once();
  rf_pointer_array_release_storage((void **)unk_18CCFF4);
  return atexit(rf_volume_system_atexit_cleanup);
}

