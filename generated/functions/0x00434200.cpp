// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00434200 rf_entity_associate_child_with_last_slot_key
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Thiscall ECX owner, stack(child fullCOMMON handle,slot key), RET8, canonicalAL0/1 only. Signed i=0..<firstDWORD(owner+2252) count re-read each test;
// unchecked pointer-array element yields relation record with keyDWORD0,childHandleDWORD4. Scans ALL entries, retaining LAST index whose key equals supplied key; no early
// break/free-slot search. No match returns0. ONLY selected last match childHandle==EXACT-1 admits, even if an earlier same-key entry is free. Resolve supplied child as COMMON(any
// type), missing returns0. No parent-state/self/cycle/authority/health test. Commit in order child+512=owner fullhandle44, child+516=suppliedkey, selected relation+4=supplied child
// handle. Then choose explicit Foley variant0 from owner class660 DWORD276 and play positional(event,owner position60,FLOAT1,shared17F10B0,0), ignoring result/event-1. Child-handle
// direct-player predicate EXACTAL1 AND owner authored turret predicate ANYnonzero sets ownerBYTE1824=1; other cases preserve it. Zero child vectors324 then336. If child
// type0-player-pointer predicate ANYnonzero, store445740(10) movement descriptor into child2136; lookup may fall back0/mutate shared selection, no result guard. ReturnAL1 regardless
// of sound/descriptor outcome. No owner/array/entry pointers guarded, previous owner detached, existing child key cleared, physics transform/snap or rollback.
char __thiscall rf_entity_associate_child_with_last_slot_key(int this, int a2, int a3)
{
  int sound_by_index; // eax
  int v6; // [esp+10h] [ebp-Ch]
  int v7; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  v7 = -1;
  for ( i = 0; i < rf_receiver_get_first_dword((void *)(this + 2252)); ++i )
  {
    if ( **(_DWORD **)sub_552200((_DWORD *)(this + 2252), i) == a3 )
      v7 = i;
  }
  if ( v7 == -1 )
    return 0;
  if ( *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(this + 2252), v7) + 4) != -1 )
    return 0;
  v6 = rf_object_resolve_handle(a2);
  if ( !v6 )
    return 0;
  *(_DWORD *)(v6 + 512) = *(_DWORD *)(this + 44);
  *(_DWORD *)(v6 + 516) = a3;
  *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(this + 2252), v7) + 4) = a2;
  sound_by_index = rf_foley_get_sound_by_index(*(_DWORD *)(*(_DWORD *)(this + 660) + 276), 0);
  rf_gamesound_play_positional_event(sound_by_index, (float *)(this + 60), 1.0, (int)&unk_17F10B0, 0);
  if ( rf_object_handle_has_direct_player_flag(a2) && rf_entity_has_turret_flag(this) )
    *(_BYTE *)(this + 1824) = 1;
  rf_vector3_zero_return_destination((float *)(v6 + 324));
  rf_vector3_zero_return_destination((float *)(v6 + 336));
  if ( rf_entity_has_player_pointer_if_type0(v6) )
    *(_DWORD *)(v6 + 2136) = sub_445740(0xAu);
  return 1;
}

