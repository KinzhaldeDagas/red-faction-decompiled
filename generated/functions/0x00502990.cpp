// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00502990 rf_event_state_delete_saved_identifiers
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] For each supplied32-bit saved id, resolve through0x4BC680 and pass returned common-object pointer directly to rf_object_delete_dispatch. No local null guard, deferred-flag-only path or event-only type restriction. Distinct from typed event restore routines marking E+4 pending-delete.
void __cdecl rf_event_state_delete_saved_identifiers(int a1, int a2)
{
  _DWORD *v2; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < a2; ++i )
  {
    v2 = (_DWORD *)rf_object_find_by_saved_identifier(*(_DWORD *)(a1 + 4 * i));
    rf_object_delete_dispatch(v2);
  }
}

