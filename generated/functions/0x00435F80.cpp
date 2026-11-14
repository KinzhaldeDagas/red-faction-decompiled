// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00435F80 rf_entity_try_jump_launch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(entity), void; NULL exits. Require438050 movement-index1/2 predicate ANY nonzero, OR current descriptor
// entity2136 DWORD4==EXACT4 with438FD0 AL0 (runtime2064 mask0x2000 clear). Reject crouched40CED0 ANY nonzero, attached-use-vehicle436A80 EXACT AL1, or43CAA0 ANY nonzero (current
// descriptor category2), in that order; preserve this later category2 veto after initial1/2 admission. No own changes before admission. Load FLOAT jump scalar681E1C; if437FD0
// index4/7 ANY nonzero, factor=round32(DOUBLE1.25-(DOUBLE0.10000000149011612-frameDeltaSeconds)*DOUBLE(-0.3500000238418579)/DOUBLE0.0833333358168602), then
// launch=round32(oldLaunch*factor); x87 expression has no intermediate FLOAT store before factor. This later predicate does not broaden initial movement admission. Only ORDERED old
// vertical velocity entity328<0 adds launch and roundsFLOAT32; old velocity>=0 OR UNORDERED REPLACES with launch, so old NaN can be overwritten. OR entity2064 bit2,
// then4356E0(entity) selects fall descriptor and sets physics424 bit1; return ignored. Lookup class660 DWORD288 Foley variant0 through446F60, then568050(event,DWORD0,FLOAT0,FLOAT1),
// ignoring event/voice failures; no event-1 guard. Final store current pause-gated FLOAT seconds clock6FC428 into entity1972 after descriptor/audio calls. Native reuses the
// fall-selector argument slot as sound-gain FLOAT; no incoming x87 argument or missing cleanup. No finite/height/delta clamp, status result, own authority/death gate or rollback
// after velocity/flags commit.
void __cdecl rf_entity_try_jump_launch(int a1)
{
  int sound_by_index; // eax
  float v2; // [esp+8h] [ebp-8h]
  float v3; // [esp+Ch] [ebp-4h]

  if ( a1
    && (rf_entity_movement_is_index1_or2(a1)
     || *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 4 && !rf_entity_runtime_flags810_has_mask2000(a1))
    && !rf_entity_is_crouched_state810(a1)
    && !rf_entity_has_attached_use_vehicle(a1)
    && !rf_entity_movement_descriptor_kind_is2(a1) )
  {
    v3 = unk_681E1C;
    if ( rf_entity_movement_is_index4_or7(a1) )
    {
      v2 = 1.25 - (0.1000000014901161 - rf_frame_delta_seconds) * -0.3500000238418579 / 0.0833333358168602;
      v3 = v3 * v2;
    }
    if ( *(float *)(a1 + 328) >= 0.0 )
      *(float *)(a1 + 328) = v3;
    else
      *(float *)(a1 + 328) = *(float *)(a1 + 328) + v3;
    *(_DWORD *)(a1 + 2064) |= 2u;
    rf_entity_select_fall_movement_descriptor((_DWORD *)a1);
    sound_by_index = rf_foley_get_sound_by_index(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 288), 0);
    rf_gamesound_play_event(sound_by_index, 0, 0.0, 1.0);
    *(float *)(a1 + 1972) = *(float *)&dword_6FC428;
  }
}

