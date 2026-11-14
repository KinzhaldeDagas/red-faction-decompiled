// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B65F0 rf_multiplayer_apply_remote_charge_kill_payload36
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled action packet15/16/20/28/36/46/47 registry, consumed source arguments, ownership, reload ordering and
// projectile traversal): Recovered4B65F0..4B66BB,lastRET4B66BA; descriptor36 remote_charge_kill. Cdecl payload DWORD0 owner-server-ID and raw BYTE4 action;source ignored,no
// length/runtime/server gate. Map owner to local handle then entity-resolve (possiblyNULL). Walk global projectile list911F74 to sentinel911CE8, next652. For EACH projectile whose
// registryID664==global remote-charge ID911C78 AND ownerDWORD48==mapped handle: nonzero action AND resolved owner entity ->call437A50(ownerEntity); else mark THIS projectile for
// deferred deletion. Mapping-1 is not rejected, so owner-1 nodes can match when mapping fails. Nonzero/resolved branch calls helper once PER matching charge; helper itself walks all
// owned classflag40 projectiles and sets float668=-1, not immediate deletion. No saved-next-before-callback, sender ownership, alive/duplication check or stop-after-first.
// Zero/nonresolved path uses deferred-delete flag, actual destruction elsewhere.
void __cdecl rf_multiplayer_apply_remote_charge_kill_payload36(const unsigned __int8 *payload)
{
  int v1; // [esp+4h] [ebp-14h]
  int v2; // [esp+8h] [ebp-10h]
  int i; // [esp+Ch] [ebp-Ch]
  unsigned __int8 v4; // [esp+17h] [ebp-1h]

  v4 = payload[4];
  v2 = rf_replication_server_id_to_local_handle(*(_DWORD *)payload);
  v1 = rf_entity_resolve_handle(v2);
  for ( i = dword_911F74; (_UNKNOWN *)i != &unk_911CE8; i = *(_DWORD *)(i + 652) )
  {
    if ( *(_DWORD *)(i + 664) == dword_911C78 && *(_DWORD *)(i + 48) == v2 )
    {
      if ( v4 && v1 )
        rf_entity_mark_owned_flag40_projectiles(v1);
      else
        rf_object_mark_for_deferred_delete(i);
    }
  }
}

