// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040C650 rf_ai_begin_use_speech_to_entity
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI/corpse-carry/inventory/projectile update chains, original field layouts and float constants and native
// signed/x87/stack/callback ABI): Cdecl(required AI block,target entity). Requires owner DWORD+2068 mask0x200 clear, target nonnull, owner humanoid predicate, AI mode2 or4, owner
// DWORD+504 nonzero, speech-playing AL0, and BOTH splitscreen/runtime bytes0. Cancels tracked body action and clears scripted-animation context. Chooses sound from class(+660)
// DWORD+1780 through441340, writes guarded target handle via40BA80(block,target+44), computes target point4010E0 and calls410920(owner,point), discarding ST0. Re-reads AI mode: if4
// calls mode2(-1,-1), secondary-state0, rounds queried sound duration to float32 then arms block+1244 with LOW32 trunc(duration*DOUBLE1000)+500 using wrapping integer addition.
// Always calls replace-speech(owner,sound,0) after these steps, even when chosen sound==-1. No return-status construction or own target handle validity/crouch gate.
void __cdecl rf_ai_begin_use_speech_to_entity(int *a1, int a2)
{
  float duration; // [esp+0h] [ebp-14h]
  float target_point[3]; // [esp+4h] [ebp-10h] BYREF
  int v4; // [esp+10h] [ebp-4h]

  if ( (*(_DWORD *)(*a1 + 2068) & 0x200) == 0
    && a2
    && rf_entity_has_humanoid_flag(*a1)
    && (a1[160] == 2 || a1[160] == 4)
    && *(_DWORD *)(*a1 + 504)
    && !rf_entity_speech_voice_is_playing(*a1)
    && !rf_splitscreen_runtime_active
    && !rf_multiplayer_runtime_mode )
  {
    rf_ai_cancel_tracked_body_action(a1);
    rf_ai_clear_scripted_animation_context(a1);
    v4 = rf_foley_registry_choose_sound_by_index(*(_DWORD *)(*(_DWORD *)(*a1 + 660) + 1780));
    sub_40BA80(a1, *(_DWORD *)(a2 + 44));
    rf_vector3_default_construct_noop(target_point);
    rf_ai_copy_target_point_for_current_movement(a1, a2, target_point);
    sub_410920(*a1, target_point);
    if ( a1[160] == 4 )
    {
      rf_ai_numeric_mode_write(a1, 2, -1, -1);
      rf_ai_secondary_state_write((int)a1, 0);
      duration = rf_sound_query_duration(v4);
      rf_replicator_arm_milliseconds(a1 + 311, (int)(duration * 1000.0) + 500);
    }
    rf_entity_replace_speech_voice(*a1, v4, 0);
  }
}

