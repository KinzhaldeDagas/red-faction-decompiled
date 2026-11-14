// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00402840 rf_ai_no_local_player_object_available
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): No arguments, explicit AL0/1. Splitscreen BYTE==0 returns whether global entity pointer681E38==NULL,
// without resolving its handle or checking type/death/active state. ANY nonzero splitscreen byte instead examines EXACTLY player-entry slots0 and1, ignoring global local-player-entry
// count and681E38. A nonnull slot whose DWORD+20 handle resolves to ANY common object returnsAL0 immediately; nonnull slot with stale/unresolved handle continues. If neither slot
// supplies a resolved object returnsAL1. Uses COMMON resolver40CE70, not ENTITY resolver or monitor/view fallback. Runtime-mode byte is not read, and no globals are changed. Upper
// EAX is not uniformly canonicalized on split-screen paths.
bool rf_ai_no_local_player_object_available()
{
  int i; // [esp+4h] [ebp-4h]

  if ( !rf_splitscreen_runtime_active )
    return dword_681E38 == 0;
  for ( i = 0; i < 2; ++i )
  {
    if ( rf_local_player_entries[i] && rf_object_resolve_handle(*(_DWORD *)(rf_local_player_entries[i] + 20)) )
      return 0;
  }
  return 1;
}

