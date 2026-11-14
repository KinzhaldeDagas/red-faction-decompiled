// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00421980 rf_entity_weapon_pose_update_admitted
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Cdecl(entity pointer), explicit canonical AL0/1, upper EAX not uniform; no incoming ST0. First requires global BYTE661510 ANY nonzero and
// nonnull entity. Player-flag predicate4BB430 ANY nonzero uses player branch: player-view-monitor4E0700(entity+5168) ANY nonzero rejects; skips all nonplayer
// target/movement/body-state tests below.  Nonplayer requires entity DWORD+1376 (AI+704 full retained target handle)!=-1. Fast-length558CC0(vector+324) ST0 ORDERED>DOUBLE0.1
// AND438010(entity) ANY nonzero rejects; equality/NaN skips that first438010 call. Native438010 tests movement descriptor entity+2136 DWORD+4 equal1 or5. Then
// body-state438750(entity,13) EXACT AL1 rejects, otherwise tests body-state15 and ANY nonzero rejects. Numeric entity DWORD+1364 (AI secondary)==1 calls438010 again and rejects
// any-nonzero, independently of first length gate. Entity DWORD+676 primary weapon==-1 rejects. Resolves retained target as COMMON full handle; missing/stale resolution is ALLOWED.
// Resolved target: fabs(entity FLOAT positionY+64 - target FLOAT+64) rounds float32, is copied through second float32 local, and ORDERED value<DOUBLE1 rejects; equal/greater/NaN
// passes. No X/Z or full-distance test.  Both branches then reject primary weapon DWORD+676 equal global DWORD911C80; carrying-body437B40 ANY nonzero; respawn-inactive40D190 EXACT
// AL1. Require body-action admission40D280 and humanoid40D150, both ANY nonzero. Dead433F60 EXACT AL1 rejects, else calls damage-flinch-update435D30 and rejects EXACT AL1. This
// predicate call may clear a stale flinch override even when final admission later fails. Finally439070(entity) ANY nonzero rejects: native resolves attachment entity+512 as ENTITY,
// requires jeep class flag, and compares unchecked attachment array(+2252) element1 DWORD+4 against entity full handle+44. All tests short-circuit in this order; final AL1 only if
// none rejects. No own storage writes, target acquisition, ammo/range/ownership validation or normalization of arbitrary predicate bytes.
bool __cdecl rf_entity_weapon_pose_update_admitted(int a1)
{
  float v2; // [esp+0h] [ebp-Ch]
  int v3; // [esp+8h] [ebp-4h]

  if ( !byte_661510 )
    return 0;
  if ( !a1 )
    return 0;
  if ( rf_object_has_player_flag(a1) )
  {
    if ( rf_player_view_target_is_monitor(*(_DWORD *)(a1 + 5168)) )
      return 0;
  }
  else
  {
    if ( *(_DWORD *)(a1 + 1376) == -1 )
      return 0;
    if ( rf_vector_fast_length((float *)(a1 + 324)) > 0.1 && sub_438010(a1) )
      return 0;
    if ( rf_entity_body_state_is_resident(a1, 13) || rf_entity_body_state_is_resident(a1, 15) )
      return 0;
    if ( *(_DWORD *)(a1 + 1364) == 1 && sub_438010(a1) )
      return 0;
    if ( *(_DWORD *)(a1 + 676) == -1 )
      return 0;
    v3 = rf_object_resolve_handle(*(_DWORD *)(a1 + 1376));
    if ( v3 )
    {
      v2 = fabs(*(float *)(a1 + 64) - *(float *)(v3 + 64));
      if ( v2 < 1.0 )
        return 0;
    }
  }
  if ( *(_DWORD *)(a1 + 676) == unk_911C80 )
    return 0;
  if ( rf_entity_is_carrying_body(a1) )
    return 0;
  if ( rf_object_has_respawn_inactive_flag(a1) )
    return 0;
  if ( rf_entity_admits_speech_body_actions(a1) && rf_entity_has_humanoid_flag(a1) )
    return !rf_entity_is_dead(a1)
        && rf_character_update_damage_flinch_override(a1) != 1
        && !rf_entity_is_parent_jeep_relation1(a1);
  return 0;
}

