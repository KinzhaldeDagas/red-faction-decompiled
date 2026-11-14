// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004292E0 rf_entity_selected_weapon_ready_admit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(entity pointer), canonical AL0/1, no own state writes. NULL returns0. Entity2064 mask0x10 immediately returns1, bypassing every later
// weapon/player/state/dead/ready test. Otherwise40B6D0(entity AI+672) ANY nonzero selected-weapon/association predicate required; zero returns0. Player-association4BCF40 EXACT AL1
// immediately returns1, including its related-owner case, with no authority/local-only inference. Other values continue: entity state1312==EXACT7 OR16 rejects; AI flags entity2000
// mask4 rejects. If entity2000 mask2 set, call dead433F60; AL0 immediately admits1, ANY nonzero falls through. With mask2 clear, dead predicate is not called. Remaining cases return1
// only ready-bit helper40B7F0(AI+672)==EXACT AL1; otherAL returns0. Thus death is not an unconditional veto and ready can admit dead records. No ammo quantity, weapon-index range,
// ownership, target visibility or timer test in this wrapper.
bool __cdecl rf_entity_selected_weapon_ready_admit(_DWORD *a1)
{
  if ( !a1 )
    return 0;
  if ( (a1[516] & 0x10) != 0 )
    return 1;
  if ( !sub_40B6D0(a1 + 168) )
    return 0;
  if ( rf_object_is_player_associated((int)a1) == 1 )
    return 1;
  if ( a1[328] == 7 )
    return 0;
  if ( a1[328] == 16 )
    return 0;
  if ( (a1[500] & 4) != 0 )
    return 0;
  if ( (a1[500] & 2) == 0 || rf_entity_is_dead((int)a1) )
    return rf_ai_is_ready_flag_set((int)(a1 + 168));
  return 1;
}

