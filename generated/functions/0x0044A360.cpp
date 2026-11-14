// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044A360 rf_geomod_execution_queue_count_get
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Cdecl noargs, returns pending-count DWORD verbatim. Current active operation has already been removed from queue at begin and is not included. No list scan, admission cap,
// network-history count or active flag test.
int rf_geomod_execution_queue_count_get()
{
  return rf_geomod_execution_queue_count;
}

