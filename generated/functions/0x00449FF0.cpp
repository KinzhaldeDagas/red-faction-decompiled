// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449FF0 rf_geomod_execution_queue_update
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Cdecl float delta_seconds; return EAX incidental. If world solid NULL, clears pending queue and returns without clearing execution-active or advancing phase. Otherwise FIRST
// processes all six nonnull smoke emitters of EVERY pending node, walking next after callbacks. Adds delta to elapsed FLOAT6EDE4C, but has no elapsed threshold or pause gate
// controlling execution.
// When active BYTE nonzero, calls operation_step ONCE; AL0 clears active, nonzero leaves it. Does not begin next queued operation in that same call, even if step just completed. When
// inactive and queue nonempty: saves head, elapsed=0, active=1, calls operation_begin(node+8), then immediately remove_destroy(node), freeing node and all six smoke emitters BEFORE
// first terrain phase step (which occurs on a later update). Thus pending count excludes active operation; smoke ownership is tied to waiting nodes. No waiting for operation
// completion before node retirement. Empty inactive queue does no begin/step, elapsed still accumulates.
int __cdecl rf_geomod_execution_queue_update(float a1)
{
  int result; // eax
  int j; // [esp+0h] [ebp-8h]
  _DWORD *i; // [esp+4h] [ebp-4h]
  _DWORD **v4; // [esp+4h] [ebp-4h]

  if ( !rf_world_solid )
    return rf_geomod_execution_queue_clear();
  result = rf_geomod_execution_queue_head;
  for ( i = (_DWORD *)rf_geomod_execution_queue_head; i != &rf_geomod_execution_queue_head; i = (_DWORD *)*i )
  {
    for ( j = 0; j < 6; ++j )
    {
      if ( i[j + 27] )
        rf_particle_emitter_process(i[j + 27]);
      result = j + 1;
    }
  }
  unk_6EDE4C = unk_6EDE4C + a1;
  if ( (_BYTE)rf_geomod_execution_active )
  {
    result = rf_geomod_operation_step();
    if ( !(_BYTE)result )
      LOBYTE(rf_geomod_execution_active) = 0;
  }
  else if ( (_DWORD *)rf_geomod_execution_queue_head != &rf_geomod_execution_queue_head )
  {
    v4 = (_DWORD **)rf_geomod_execution_queue_head;
    unk_6EDE4C = 0.0;
    LOBYTE(rf_geomod_execution_active) = 1;
    rf_geomod_operation_begin(rf_geomod_execution_queue_head + 8);
    return rf_geomod_execution_queue_node_remove_destroy(v4);
  }
  return result;
}

