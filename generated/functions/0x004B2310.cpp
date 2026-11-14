// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B2310 rf_client_apply_trigger_activate_payload15
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled action packet15/16/20/28/36/46/47 registry, consumed source arguments, ownership, reload ordering and
// projectile traversal): Recovered4B2310..4B23BD,lastRET4B23BC; original descriptor15 trigger_activate. Cdecl payload, source extra word ignored; no length. Only runtime1 authority
// EXACT0. Read trigger-level-ID DWORD0 and activator-server-ID DWORD4; map activator to local handle (including possible-1), find trigger by32-bit level ID. Missing trigger no
// action. Found: set_forward_enabled (clears trigger flag10) BEFORE commit_activation(trigger,mappedActivator,0,1). Delegate may reject key/admission after forward flag cleared;
// result ignored, no rollback. No own source binding, payload bound, activator existence/death check or repeated-trigger suppression. Sender2210 uses the same two-DWORD8-byte payload
// in11-byte unreliable envelope.
void __cdecl rf_client_apply_trigger_activate_payload15(const unsigned __int8 *payload)
{
  int v1; // [esp+0h] [ebp-10h]
  int v2; // [esp+4h] [ebp-Ch]
  int v3; // [esp+8h] [ebp-8h]

  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    v2 = *(_DWORD *)payload;
    v3 = rf_replication_server_id_to_local_handle(*((_DWORD *)payload + 1));
    v1 = rf_trigger_find_by_level_id32(v2);
    if ( v1 )
    {
      rf_trigger_set_forward_enabled(v1);
      rf_trigger_commit_activation(v1, v3, 0, 1);
    }
  }
}

