// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449E90 rf_geomod_execution_queue_exit_cleanup
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Cdecl atexit wrapper; invokes execution_queue_clear and returns. No independent active/phase/history reset or emitter resource unloading beyond per-node clear delegates.
void __cdecl rf_geomod_execution_queue_exit_cleanup()
{
  rf_geomod_execution_queue_clear();
}

