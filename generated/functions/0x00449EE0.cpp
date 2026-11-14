// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449EE0 rf_geomod_execution_queue_node_remove_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Cdecl132-byte pending node. Unlinks/clears next0/prev4, loops six pointer slots108+4*i. Each nonnull emitter is destroyed through emitter_destroy (detaches already-live particles
// to continue naturally), then slot zeroed. Raw deletes node, decrements pending count, returns new count EAX. Does not itself invoke/cancel geometry operation, unlink history, or
// free embedded operation fields. Active operation was copied into globals before normal begin-path retirement; emitter destruction here need not kill particles already emitted.
int __cdecl rf_geomod_execution_queue_node_remove_destroy(_DWORD **a1)
{
  int i; // [esp+4h] [ebp-4h]

  *a1[1] = *a1;
  (*a1)[1] = a1[1];
  *a1 = nullptr;
  a1[1] = nullptr;
  for ( i = 0; i < 6; ++i )
  {
    if ( a1[i + 27] )
    {
      rf_particle_emitter_destroy((int)a1[i + 27]);
      a1[i + 27] = nullptr;
    }
  }
  operator delete(a1);
  return --rf_geomod_execution_queue_count;
}

