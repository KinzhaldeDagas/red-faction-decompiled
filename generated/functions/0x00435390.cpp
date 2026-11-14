// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00435390 rf_entity_select_body_fire_slot_for_stance
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Cdecl(entity,BYTE alternate). Entity DWORD1312==3 and crouched predicate40CED0 true ->slot4. Else DWORD1312==12 AND DWORD1260==1 AND crouched ->slot4. Otherwise
// alternate BYTE EXACT1 returns3; all other BYTE values return2. No slot activation, weapon admission, player lookup or fallback here. Entity pointer not guarded before DWORD1312
// read; uses numeric state selectors without assigning unsupported state names.
int __cdecl rf_entity_select_body_fire_slot_for_stance(int a1, char a2)
{
  if ( *(_DWORD *)(a1 + 1312) == 3 && rf_entity_is_crouched_state810(a1) )
    return 4;
  if ( *(_DWORD *)(a1 + 1312) == 12 && *(_DWORD *)(a1 + 1260) == 1 && rf_entity_is_crouched_state810(a1) )
    return 4;
  if ( a2 == 1 )
    return 3;
  return 2;
}

