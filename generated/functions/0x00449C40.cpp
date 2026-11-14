// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449C40 rf_geomod_network_history_append
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Cdecl runtime operation100 pointer. Allocates132-byte node, invokes node ctor449D20 if nonnull, then UNCONDITIONALLY copies operation into node+8, appends history tail, increments
// network-history count. Allocation NULL path has no local rejection before copy. Node links0/4 and operation8..107 assigned; six trailing DWORDs108..131 remain uninitialized and are
// not smoke ownership for history nodes. No capacity/quota check or transmission in this function; exact-server admission/begin callers enforce separate policy. Normal return EAX0 is
// incidental from append-loop XOR, not allocated node pointer. Constructor-exception unwind deletes current raw allocation; no rollback of previously appended history.
int __cdecl rf_geomod_network_history_append(float *a1)
{
  char *v2; // [esp+4h] [ebp-1Ch]
  char *v3; // [esp+8h] [ebp-18h]

  v3 = (char *)operator new(0x84u);
  if ( v3 )
    v2 = rf_geomod_operation_node132_construct_noop(v3);
  else
    v2 = nullptr;
  rf_geomod_operation100_assign((float *)v2 + 2, a1);
  *((_DWORD *)v2 + 1) = rf_geomod_network_history_tail;
  *(_DWORD *)v2 = &rf_geomod_network_history_head;
  *rf_geomod_network_history_tail = v2;
  rf_geomod_network_history_tail = v2;
  ++rf_geomod_network_history_count;
  return 0;
}

