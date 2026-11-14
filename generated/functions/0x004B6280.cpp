// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B6280 rf_server_apply_reload_request_payload47
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled action packet15/16/20/28/36/46/47 registry, consumed source arguments, ownership, reload ordering and
// projectile traversal): Recovered4B6280..4B630A,lastRET4B6309; descriptor47 reload_request. Cdecl(payload,sourceEndpoint). Require runtime1 authority EXACT1, then READ raw
// payloadDWORD0 into dead local/cursor before source lookup; its VALUE is not used to select entity or reload weapon. Thus even unknown source reads four payload bytes; no length
// guard. Find player by SOURCE endpoint, resolve current entity from player+20; if both exist call weapon_reload_request(entity,0,0). No own client fpgun/throttle/death/weapon/ammo
// check, response serialization or success check; delegate owns reload admission/authoritative commit. No meaningful callback return.
void __cdecl rf_server_apply_reload_request_payload47(const unsigned __int8 *payload, const void *source)
{
  _DWORD *v2; // [esp+4h] [ebp-Ch]
  int v3; // [esp+Ch] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v2 = rf_player_find_by_network_endpoint((int)source);
    if ( v2 )
    {
      v3 = rf_entity_resolve_handle(v2[5]);
      if ( v3 )
        rf_weapon_reload_request(v3, 0, 0);
    }
  }
}

