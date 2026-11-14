// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BCF40 rf_object_is_player_associated
// UNREALRED VERIFIED [mission-startup-20261020] Trigger policy3/4 uses this broader player association predicate, including the player entity referenced owner. Unreal direct character control currently represents only the direct-player case; generic attached vehicle common ownership remains separate.
// UNREALRED VERIFIED [combat-ammo-roles-pickups-20261111]: Playerassociation: nullfalse; commonflag+7Cbit8=>true, otherwise scanALLplayerentries87C324 and resolveentry+20; compare resolvedEntity+200 against candidateUID+44. Broader than actorcontrol role/directplayer flag. Exactrelatedfield meaning is not generalized here to arbitrary Unreal attachment.
// UNREALRED VERIFIED [original-target-player-association-20261112]: Exact nullable-COMMON predicate used by402160: null0; COMMON7Cbit8 ->AL1. Otherwise traverse player record ring87C324, resolve record+20 as ENTITY fullhandle; if resolved entity generic COMMON+200 parent/slot owner FULLhandle equals candidate COMMON+44, returnAL1. No match0. NOT simply player-record1430 presence or IsPlayerControlled. Generic434200 writes child+200=owner+44 and reciprocal slot metadata for arbitrary COMMON children; constructor auto-turret head attachment is one producer. Vehicle/use classification is a consumer, not the sole ownership meaning. MP player-list lifecycle is independent from native entity-list68211C.
char __cdecl rf_object_is_player_associated(int a1)
{
  _DWORD *v2; // [esp+0h] [ebp-Ch]
  int v3; // [esp+4h] [ebp-8h]
  _DWORD *i; // [esp+8h] [ebp-4h]

  if ( !a1 )
    return 0;
  if ( (*(_DWORD *)(a1 + 124) & 8) != 0 )
    return 1;
  for ( i = (_DWORD *)dword_87C324; i; i = v2 )
  {
    v3 = rf_entity_resolve_handle(i[5]);
    if ( v3 && *(_DWORD *)(v3 + 512) == *(_DWORD *)(a1 + 44) )
      return 1;
    if ( *i == dword_87C324 )
      v2 = nullptr;
    else
      v2 = (_DWORD *)*i;
  }
  return 0;
}

