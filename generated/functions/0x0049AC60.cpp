// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049AC60 rf_multiplayer_apply_suicide_callback20
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled action packet15/16/20/28/36/46/47 registry, consumed source arguments, ownership, reload ordering and
// projectile traversal): Recovered49AC60..49ACBA,lastRET49ACB9; descriptor20 suicide. Cdecl(unusedPayload,sourceEndpoint). No payload reads or own runtime/authority gate. Find player
// by SOURCE endpoint, then resolve its handle+20 as entity. If either missing return. Write entity float52 exactly-1000.0 from original6318B8, then entityBYTE624=player.net4608
// networkID BYTE20 (net pointer unguarded). No alive test, normal damage arithmetic, armor check, immediate destruction call or source-ID field; source chooses affected owner. Later
// death processing is separate. Local sender49ABB0 emits empty payload packet20 only in client runtime.
void __cdecl rf_multiplayer_apply_suicide_callback20(const unsigned __int8 *payload, const void *source)
{
  _DWORD *v2; // [esp+0h] [ebp-8h]
  int v3; // [esp+4h] [ebp-4h]

  v2 = rf_player_find_by_network_endpoint((int)source);
  if ( v2 )
  {
    v3 = rf_entity_resolve_handle(v2[5]);
    if ( v3 )
    {
      *(float *)(v3 + 52) = -1000.0;
      *(_BYTE *)(v3 + 624) = *(_BYTE *)(v2[1152] + 20);
    }
  }
}

