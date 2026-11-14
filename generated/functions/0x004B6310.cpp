// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B6310 rf_client_apply_reload_payload46
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled action packet15/16/20/28/36/46/47 registry, consumed source arguments, ownership, reload ordering and
// projectile traversal): Recovered4B6310..4B6469,lastRET4B6468; descriptor46 reload. Cdecl payload,source extra word ignored,no length. Only runtime1 authority EXACT0. Read four raw
// DWORDs: serverEntityHandle0,weapon4,reserve8,magazine12. Map server handle then entity-resolve; missing returns. If CURRENT entity weapon676>=0 call
// stop_weapon_firing(entity.handle44,currentWeapon), independent of incoming weapon. Call weapon_reload_request(entity,1,1) for presentation BEFORE received stores, ignore result.
// Then install staged reserve5036,magazine5032,reload weapon5040, regardless incoming weapon validity. Only signed incoming weapon>=0 admits live arrays: entity
// magazineDWORD(812+4*weapon)=receivedMagazine; ammo-index DWORD at912024+1360*weapon then entity reserveDWORD(684+4*ammoIndex)=receivedReserve. No upper weapon/ammo-index bound,
// source-ID ownership, ammo clamp or presentation-success dependency here. Negative weapon skips live writes but remains staged. Old raw-region/no-owner instruction note updated to
// recovered definition; all original bytes preserved.
void __cdecl rf_client_apply_reload_payload46(const unsigned __int8 *payload)
{
  int v1; // [esp+0h] [ebp-18h]
  _DWORD *v2; // [esp+4h] [ebp-14h]
  int v3; // [esp+Ch] [ebp-Ch]
  int v4; // [esp+10h] [ebp-8h]
  int v5; // [esp+14h] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    v1 = *((_DWORD *)payload + 1);
    v5 = *((_DWORD *)payload + 2);
    v3 = *((_DWORD *)payload + 3);
    v4 = rf_replication_server_id_to_local_handle(*(_DWORD *)payload);
    v2 = (_DWORD *)rf_entity_resolve_handle(v4);
    if ( v2 )
    {
      if ( (int)v2[169] >= 0 )
        rf_entity_stop_weapon_firing(v2[11], v2[169]);
      rf_weapon_reload_request((int)v2, 1, 1);
      v2[1259] = v5;
      v2[1258] = v3;
      v2[1260] = v1;
      if ( v1 >= 0 )
      {
        v2[v1 + 203] = v3;
        v2[dword_912024[340 * v1] + 171] = v5;
      }
    }
  }
}

