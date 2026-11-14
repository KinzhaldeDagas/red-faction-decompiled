// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449B20 rf_geomod_history_initialize_ring_and_register_cleanup
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments, full EAX from CRT atexit registration. Store history-next/head DWORD6EDDC0=sentinelADDRESS6EDDC0 and
// history-prev/tail DWORD6EDDC4=same sentinel, then countDWORD6EDDB8=0. XOR EAX,EAX/JNZ back-edge is never taken. Register449B60 withatexit, forwarding registration status and
// ignoring failure for state rollback. Does not walk/delete existing nodes or their payloads before resetting links/count; repeated calls reset ring and register another cleanup. No
// execution-queue/Boolean-phase/cutter registry mutation or admission guard in this initializer.
int rf_geomod_history_initialize_ring_and_register_cleanup()
{
  rf_geomod_network_history_head = &rf_geomod_network_history_head;
  rf_geomod_network_history_tail = &rf_geomod_network_history_head;
  rf_geomod_network_history_count = 0;
  return atexit(rf_geomod_history_atexit_clear_adapter);
}

