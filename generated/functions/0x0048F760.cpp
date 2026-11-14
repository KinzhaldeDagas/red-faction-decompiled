// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048F760 rf_multiplayer_remove_player_and_mark_object
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, multiplayer session dispatch and deadlines, reliable-peer timeout and acceptance, rename payload ordering, disabled native drawing and wrapped network-id allocation): 
// Cdecl player pointer. Resolves object handleDWORD20; if valid marks object for DEFERRED deletion,does not destroy it immediately. Calls4A04D0(player),then
// player_unlink_close_and_destroy_record(player),returns latter EAX. Player pointer itself unguarded; unresolved handle still proceeds to player cleanup. No own authority/mode
// admission,notification or broadcast.
int __cdecl rf_multiplayer_remove_player_and_mark_object(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_object_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( v2 )
    rf_object_mark_for_deferred_delete(v2);
  rf_network_flush_player_queues(a1);
  return rf_player_unlink_close_and_destroy_record(a1);
}

