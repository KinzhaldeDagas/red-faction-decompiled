// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004343A0 rf_entity_detach_first_matching_child
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Thiscall ECX owner, stack(child fullCOMMON handle,LOWBYTE playSound), RET8, canonicalAL0/1. EXACT child handle-1 immediately0; other negative full
// handles allowed. Signed scan re-reads count owner+2252 and stops at FIRST relation childHandleDWORD4 equal input, regardless of key; absent returns0. Unchecked pointers. Clears
// that relation childHandle=-1 BEFORE resolving input as COMMON. Missing/stale input therefore returnsAL0 AFTER reciprocal slot mutation, leaving ownerBYTE1824 and other child/owner
// fields untouched. Resolved child+512=-1, but child+516 slotkey is NOT cleared and prior parent equality is NOT checked. Any nonzero playSound byte chooses variant0 owner class
// DWORD280 and positional event(owner position60,1,shared17F10B0,0); failure/event-1 ignored. Then ownerBYTE1824=0 unconditionally, even nonturret. If child type0-player-pointer
// predicate ANYnonzero, store445740(1) descriptor at child2136, without own lookup validation. ReturnAL1. No velocity/pose reset, owner NULL/array/entry guard, parent rollback,
// search of later duplicate handles or general detach transaction.
char __thiscall rf_entity_detach_first_matching_child(int this, int a2, char a3)
{
  int sound_by_index; // eax
  int v6; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]

  if ( a2 == -1 )
    return 0;
  for ( i = 0; ; ++i )
  {
    if ( i >= rf_receiver_get_first_dword((void *)(this + 2252)) )
      return 0;
    if ( *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(this + 2252), i) + 4) == a2 )
      break;
  }
  *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(this + 2252), i) + 4) = -1;
  v6 = rf_object_resolve_handle(a2);
  if ( !v6 )
    return 0;
  *(_DWORD *)(v6 + 512) = -1;
  if ( a3 )
  {
    sound_by_index = rf_foley_get_sound_by_index(*(_DWORD *)(*(_DWORD *)(this + 660) + 280), 0);
    rf_gamesound_play_positional_event(sound_by_index, (float *)(this + 60), 1.0, (int)&unk_17F10B0, 0);
  }
  *(_BYTE *)(this + 1824) = 0;
  if ( rf_entity_has_player_pointer_if_type0(v6) )
    *(_DWORD *)(v6 + 2136) = sub_445740(1u);
  return 1;
}

