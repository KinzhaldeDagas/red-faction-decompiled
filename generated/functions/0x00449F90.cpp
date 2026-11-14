// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449F90 rf_geomod_execution_queue_level_init
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Cdecl noargs. Clears execution-active BYTE, clears pending nodes/emitters, explicitly self-links queue sentinel, resolves template names exactly 'geomod smoke' and 'geomod smoke in
// driller', stores their ids including-1, sets pending count0. Returns second lookup id, not Boolean status. Does not reset elapsed6EDE4C, terrain phase, network-history count or
// saved admission count. Smoke creation later requires BOTH ids!=-1 even if only one template would be selected.
int rf_geomod_execution_queue_level_init()
{
  int result; // eax

  LOBYTE(rf_geomod_execution_active) = 0;
  rf_geomod_execution_queue_clear();
  rf_geomod_execution_queue_head = &rf_geomod_execution_queue_head;
  rf_geomod_execution_queue_tail = &rf_geomod_execution_queue_head;
  rf_geomod_smoke_template = rf_particle_emitter_definition_find_name("geomod smoke");
  result = rf_particle_emitter_definition_find_name("geomod smoke in driller");
  rf_geomod_driller_smoke_template = result;
  rf_geomod_execution_queue_count = 0;
  return result;
}

