// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00405570 rf_ai_mode11_track_target_and_fire
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI weighted-target/mode11/15/16/speech/stimulus chains, original dispatch/float constants and native field
// lifetime and native signed/x87/stack/callback ABI): One AI block, mode11 secondary9 callback. Resolve COMMON target+704. Missing OR deadline+676 elapsed EXACT1 ->guarded target
// setter-1, stop selected weapon(owner handle,block+4), write secondary8; does NOT reset those two deadlines here. Otherwise angular4024E0(owner,target)==EXACT1 sets local accepted1
// and runs4025D0 probes. Every other AL forces BYTE+669=0, and arms+676 for1000ms only if disarmed. Motion test: nonentity target type!=0 requires ordered
// length(velocity+324)>DOUBLE0.1. Type0 resolves ENTITY then436440 latest timestamp, no second null guard; timestamp roundedfloat32 and global seconds minus it compared without extra
// float store, ordered delta<DOUBLE0.3. Motion AND local angular acceptance1 ->copy retained-entity-point/common-position helper,410920(owner,point), arm block+672 with1500ms then
// reset+676. Afterwards, +672 elapsed EXACT1 stops selected firing, arms+676 with3000ms if angular accepted else500ms, resets+672. Finally if +672 is armed EXACT1 calls401670(block);
// expiration of +676 is rechecked only on next handler entry. No independent owner dead/role gate; incidental return.
char __cdecl rf_ai_mode11_track_target_and_fire(int *a1)
{
  char result; // al
  float target_point[3]; // [esp+0h] [ebp-1Ch] BYREF
  float v3; // [esp+Ch] [ebp-10h]
  float *v4; // [esp+10h] [ebp-Ch]
  bool v5; // [esp+16h] [ebp-6h]
  char v6; // [esp+17h] [ebp-5h]
  int v7; // [esp+18h] [ebp-4h]

  v7 = rf_object_resolve_handle(a1[176]);
  if ( v7 && !rf_replicator_has_elapsed(a1 + 169) )
  {
    v6 = 0;
    if ( sub_4024E0(*a1, v7) )
    {
      v6 = 1;
      rf_ai_refresh_target_collision_and_corridor_probes(a1, v7);
    }
    else
    {
      *((_BYTE *)a1 + 669) = 0;
      if ( !rf_replicator_is_armed(a1 + 169) )
        rf_replicator_arm_milliseconds(a1 + 169, 1000);
    }
    v5 = 0;
    if ( *(_DWORD *)(v7 + 36) )
    {
      v5 = rf_vector3_length((float *)(v7 + 324)) > 0.1;
    }
    else
    {
      v4 = (float *)rf_entity_resolve_handle(*(_DWORD *)(v7 + 44));
      v3 = rf_entity_latest_activity_timestamp(v4);
      v5 = *(float *)&dword_6FC428 - v3 < 0.3;
    }
    if ( v5 && v6 == 1 )
    {
      rf_vector3_default_construct_noop(target_point);
      rf_object_copy_entity_vector7D4_or_position(v7, target_point);
      sub_410920(*a1, target_point);
      rf_replicator_arm_milliseconds(a1 + 168, 1500);
      rf_replicator_reset(a1 + 169);
    }
    if ( rf_replicator_has_elapsed(a1 + 168) )
    {
      rf_entity_stop_weapon_firing(*(_DWORD *)(*a1 + 44), a1[1]);
      if ( v6 )
        rf_replicator_arm_milliseconds(a1 + 169, 3000);
      else
        rf_replicator_arm_milliseconds(a1 + 169, 500);
      rf_replicator_reset(a1 + 168);
    }
    result = rf_replicator_is_armed(a1 + 168);
    if ( result == 1 )
      return rf_ai_dispatch_selected_primary_weapon_action(a1);
  }
  else
  {
    sub_40BA80(a1, -1);
    rf_entity_stop_weapon_firing(*(_DWORD *)(*a1 + 44), a1[1]);
    return rf_ai_secondary_state_write((int)a1, 8);
  }
  return result;
}

