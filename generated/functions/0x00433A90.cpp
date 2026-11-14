// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00433A90 rf_entity_fire_secondary_or_begin_charge
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(entity pointer,LOWBYTE force), heterogeneous EAX/AL, NOT a reliable shot-success result. NULL entity or dead predicate EXACTAL1 returns
// immediately retaining thatAL1; computing entity+672 before this call does not dereference it. ForceBYTE0 requires embedded entity+1212 deadline elapsed ANYnonzero; other force
// bytes bypass this test. Secondary index entity+680 SIGNED<0 invokes433E40(arm500ms/optional failure feedback) and exits. Otherwise ownership403D00(entity+672,index) ANYnonzero
// required: its native signed0<=index<64 plus AI ownership BYTE+396 excludes other indices. Then4391D0 reads shared RESERVE via weapon AmmoID, not loaded clip; signed reserve<=0
// invokes same500ms feedback and exits. This snapshot reserve is never modified locally. Positive reserve with loaded clip0 is not separately rejected here; success later calls the
// clip-or-reserve consumer and may decrement reserve.  Weapon record912000+1360*secondary. ForceBYTE0 AND selected-mode high-parameter predicate(index,0)==EXACTAL1: arm entity+1284
// deadline relative0ms, copy weapon DWORD+1092 to entity+1288 and return that fullDWORD; no projectile/counter/ammo work. Other paths increment wrapped32 tag counter entity+1292.
// Cached world-weapon model50FFA0(index) fullEAX nonzero selects signed count at gameplay class+480, zero selects+456; if counter>=count reset0, with no count>0 or negative-counter
// clamp. No-op local vector/matrix constructors do not initialize their storage. Call422CC0(entity,RE-READ secondary680,localPoint,localMatrix,counter,LOWBYTE0), ignore its
// heterogeneous result. Its no-write failure is not detected and no initialized fallback is supplied. Flinch updater ANYnonzero skips direct aim adjustment; zero resolves current AI
// target1376 as COMMON and any nonNULL target overrides local matrix from unchecked-normalized(target COMMON position60-localPoint), with entity COMMON upHint+84, regardless of cone.
// Missing target preserves prior matrix.  Create ONE projectile51EBB0(secondary,entity fullhandle44,localPoint,localMatrix,0,0). NULL returns fullEAX0, retaining
// counter/transform/flinch prefix changes but skipping playback, decrement and cooldown. Success chooses Foley from PROJECTILE class660 DWORD+352, plays seven-slot object-view sound
// at BY-VALUE localPoint,event,FLOAT1,FLOAT0 without event-1 guard. Silent predicate uses PROJECTILE definition index664; only AL0
// invokes40A810(handle,point,FLOAT40,policyBYTE1,ignored extraDWORD0). Local consume byte is fixed1: calls431EF0(entity,RE-READ secondary680). That helper decrements loaded[weapon]
// ONLY when positive-clip predicate returns EXACTAL1, otherwise unguarded reserve[weapon.AmmoID]; both branches wrap32 then floor signed-negative to0. This may consume reserve and is
// not a loaded-only operation; initial safe reserve gate is not repeated before this re-read consumption. Arms entity+1212 using FTOL2SSE(projectile class FLOAT208*DOUBLE1000), no
// +0.5/intermediate FLOAT store/positive or finite guard.433E90 is then called but its selector435380 always returns-1, so no body action starts. Arms entity+5116 relative0ms.  Final
// local-player-or-related predicate EXACTAL1 invokes related-entry lookup. A missing entry returns fullEAX0 even after projectile success; found entry ends with EAX original entity
// pointer and only an unused local copy of secondary index. Other predicate bytes return incidental predicate register residue. Initial deadAL1, special-field EAX, NULL0 and
// successful-shot pointer/AL0 residues must not be normalized into a uniform Boolean. No primary-slot firing dispatch, authority gate, output-validity check, rollback or
// repeated-projectile loop in this body.
char __cdecl rf_entity_fire_secondary_or_begin_charge(_DWORD *a1, char a2)
{
  int runtime; // eax
  float v4[3]; // [esp-Ch] [ebp-80h] BYREF
  int v5; // [esp+0h] [ebp-74h]
  float v6; // [esp+4h] [ebp-70h]
  float v7; // [esp+8h] [ebp-6Ch]
  int v8; // [esp+14h] [ebp-60h]
  float out_vector[3]; // [esp+18h] [ebp-5Ch] BYREF
  int v10; // [esp+24h] [ebp-50h]
  float v11[9]; // [esp+28h] [ebp-4Ch] BYREF
  int v12; // [esp+4Ch] [ebp-28h]
  float rhs[3]; // [esp+50h] [ebp-24h] BYREF
  char v14; // [esp+5Fh] [ebp-15h]
  int v15; // [esp+60h] [ebp-14h]
  char *v16; // [esp+64h] [ebp-10h]
  _DWORD *v17; // [esp+68h] [ebp-Ch]
  int v18; // [esp+6Ch] [ebp-8h]

  v17 = a1 + 168;
  LOBYTE(runtime) = rf_entity_is_dead((int)a1);
  if ( (unsigned __int8)runtime == 1 )
    return runtime;
  if ( !a2 )
  {
    LOBYTE(runtime) = rf_replicator_has_elapsed(v17 + 135);
    if ( !(_BYTE)runtime )
      return runtime;
  }
  if ( (int)v17[2] < 0 )
    goto LABEL_5;
  LOBYTE(runtime) = sub_403D00((int)v17, v17[2]);
  if ( !(_BYTE)runtime )
    return runtime;
  v14 = 1;
  v18 = sub_4391D0((int)a1, v17[2]);
  if ( v18 <= 0 )
  {
LABEL_5:
    LOBYTE(runtime) = rf_entity_arm_secondary_retry_and_feedback((int)a1);
    return runtime;
  }
  v16 = (char *)&rf_weapon_records + 1360 * v17[2];
  if ( !a2 && rf_weapon_selected_mode_has_high_parameter_flag(v17[2], 0) )
  {
    rf_replicator_arm_milliseconds(a1 + 321, 0);
    runtime = *((_DWORD *)v16 + 273);
    a1[322] = runtime;
    return runtime;
  }
  ++a1[323];
  if ( sub_50FFA0(v17[2]) )
  {
    if ( a1[323] >= rf_receiver_get_first_dword((void *)(a1[165] + 480)) )
      a1[323] = 0;
  }
  else if ( a1[323] >= rf_receiver_get_first_dword((void *)(a1[165] + 456)) )
  {
    a1[323] = 0;
  }
  v15 = 0;
  if ( v14 && v18 <= 0 )
    goto LABEL_27;
  rf_vector3_default_construct_noop(rhs);
  rf_matrix3_construct((char *)v11);
  rf_entity_resolve_firing_transform((float *)a1, a1[170], rhs, v11, a1[323], 0);
  if ( !rf_character_update_damage_flinch_override((int)a1) )
  {
    v10 = rf_object_resolve_handle(a1[344]);
    if ( v10 )
    {
      rf_vector_subtract((const float *)(v10 + 60), out_vector, rhs);
      rf_vector_normalize_reciprocal_sqrt(out_vector);
      rf_orientation_from_forward_and_up_hint(v11, out_vector, (float *)a1 + 21);
    }
  }
  runtime = rf_projectile_create_runtime(v17[2], a1[11], (int)rhs, (int)v11, 0, 0);
  v15 = runtime;
  if ( runtime )
  {
    v12 = rf_foley_choose_random_sound(*(_DWORD *)(*(_DWORD *)(v15 + 660) + 352));
    v7 = 0.0;
    v6 = 1.0;
    v5 = v12;
    rf_vector3_copy_return_destination(v4, rhs);
    rf_sound_event_play_for_object_view((int)a1, v4[0], SLODWORD(v4[1]), SLODWORD(v4[2]), v5, v6, v7);
    if ( !rf_weapon_is_silent(*(_DWORD *)(v15 + 664)) )
    {
      v7 = 0.0;
      rf_ai_propagate_stimulus_to_nearby_entities(a1[11], rhs, 40.0, 1);
    }
    if ( v14 == 1 )
      rf_weapon_decrement_clip_or_reserve_ammo((int)a1, v17[2]);
LABEL_27:
    if ( v15 )
    {
      rf_replicator_arm_milliseconds(v17 + 135, (int)(*(float *)(*(_DWORD *)(v15 + 660) + 208) * 1000.0));
      rf_entity_try_secondary_fire_body_action((int)a1);
      rf_replicator_arm_milliseconds(a1 + 1279, 0);
    }
    LOBYTE(runtime) = rf_entity_matches_local_player_or_related_handle((int)a1);
    if ( (unsigned __int8)runtime == 1 )
    {
      runtime = rf_object_find_local_player_entry_or_related_owner((int)a1);
      v8 = runtime;
      if ( runtime )
        LOBYTE(runtime) = (_BYTE)a1;
    }
  }
  return runtime;
}

