// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449E40 rf_geomod_execution_queue_global_init
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Cdecl noargs process init. Self-links execution queue sentinel, count0, elapsed FLOAT6EDE4C=0, BYTE execution-active=0; registers exit wrapper449E90 with atexit and returns atexit
// status. Does not destroy preexisting queued nodes/emitters before overwriting links, or reset terrain-operation phase, history list or admission count. Active is a BYTE write, not
// clearing its whole enclosing DWORD.
int rf_geomod_execution_queue_global_init()
{
  rf_geomod_execution_queue_head = &rf_geomod_execution_queue_head;
  rf_geomod_execution_queue_tail = &rf_geomod_execution_queue_head;
  rf_geomod_execution_queue_count = 0;
  unk_6EDE4C = 0.0;
  LOBYTE(rf_geomod_execution_active) = 0;
  return atexit(rf_geomod_execution_queue_exit_cleanup);
}

