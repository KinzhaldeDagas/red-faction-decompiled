// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B6080 rf_server_apply_select_weapon_request_payload28
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled action packet15/16/20/28/36/46/47 registry, consumed source arguments, ownership, reload ordering and
// projectile traversal): Recovered4B6080..4B610E,lastRET4B610D; descriptor28 select_weapon_request. Cdecl(payload,sourceEndpoint), both consumed. Require runtime1 authority EXACT1
// FIRST, find player by source, resolve current handle+20 as entity. Missing owner/entity skips payload read. Then read raw weaponDWORD0 and invoke6000(player,entity,weapon). No own
// bounds, current-weapon/death checks or response here; helper maps special ownership alias and tests inventory. Source binding is real here, unlike ID-addressed use/team callbacks.
// No payload-length validation or meaningful return.
void __cdecl rf_server_apply_select_weapon_request_payload28(const unsigned __int8 *payload, const void *source)
{
  int v2; // [esp+0h] [ebp-10h]
  _DWORD *v3; // [esp+8h] [ebp-8h]

  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v3 = rf_player_find_by_network_endpoint((int)source);
    if ( v3 )
    {
      v2 = rf_entity_resolve_handle(v3[5]);
      if ( v2 )
        rf_player_apply_owned_network_weapon_selection((int)v3, v2, *(_DWORD *)payload);
    }
  }
}

