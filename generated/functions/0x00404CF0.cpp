// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00404CF0 rf_ai_update_nearby_holstered_player_speech
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI weighted-target/mode11/15/16/speech/stimulus chains, original dispatch/float constants and native field
// lifetime and native signed/x87/stack/callback ABI): One AI block. Requires owner+2068 mask0x200 clear, global entity681E38 nonnull, owner+2064 mask0x01000000 set, global entity
// holstered predicate nonzero, mode2/4, humanoid, not dead (any nonzero rejects), no active speech. If block deadline+1248 DISARMED and squared COMMON-position distance
// ordered<DOUBLE4, arm rand()%4000+6000ms and return. Otherwise test elapsed; true resets+1248 BEFORE second distance check. Second ordered distance<4 is required; equal/greater/NaN
// exits with timer reset. On admission cancel body action/context, choose4413D0(class voice index), resolve global handle as COMMON object with no second null guard, compute
// movement-dependent target point4010E0, call410920 discardingST0, arm look deadline+1256 for500ms and copy point into block+1260. Re-read mode: if4 request mode2(-1,-1), secondary0,
// arm block+1244 with LOW32 trunc(float32(sound duration)*DOUBLE1000)+500. Always replace-speech(owner,sound,0), including-1. No separate authority/runtime admission; timers are
// wrapped milliseconds, distance squared4 means radius2.
void __cdecl rf_ai_update_nearby_holstered_player_speech(int *a1)
{
  int v1; // eax
  float copy_result[3]; // [esp+0h] [ebp-24h] BYREF
  float duration; // [esp+Ch] [ebp-18h]
  float source[3]; // [esp+10h] [ebp-14h] BYREF
  int v5; // [esp+1Ch] [ebp-8h]
  int v6; // [esp+20h] [ebp-4h]

  if ( (*(_DWORD *)(*a1 + 2068) & 0x200) == 0
    && dword_681E38
    && ((unsigned int)&unk_1000000 & *(_DWORD *)(*a1 + 2064)) != 0
    && rf_entity_weapon_is_holstered_for_actions(dword_681E38)
    && (a1[160] == 2 || a1[160] == 4)
    && rf_entity_has_humanoid_flag(*a1)
    && !rf_entity_is_dead(*a1)
    && !rf_entity_speech_voice_is_playing(*a1) )
  {
    if ( rf_replicator_is_armed(a1 + 312)
      || rf_vector_distance_squared((const float *)(*a1 + 60), (const float *)(dword_681E38 + 60)) >= 4.0 )
    {
      if ( rf_replicator_has_elapsed(a1 + 312) )
      {
        rf_replicator_reset(a1 + 312);
        if ( rf_vector_distance_squared((const float *)(*a1 + 60), (const float *)(dword_681E38 + 60)) < 4.0 )
        {
          rf_ai_cancel_tracked_body_action(a1);
          rf_ai_clear_scripted_animation_context(a1);
          v6 = rf_foley_registry_choose_sound_4413D0(*(_DWORD *)(*(_DWORD *)(*a1 + 660) + 1780));
          v5 = rf_object_resolve_handle(*(_DWORD *)(dword_681E38 + 44));
          rf_vector3_default_construct_noop(source);
          rf_ai_copy_target_point_for_current_movement(a1, v5, source);
          sub_410920(*a1, source);
          rf_replicator_arm_milliseconds(a1 + 314, 500);
          rf_vector_copy((float *)a1 + 315, copy_result, source);
          if ( a1[160] == 4 )
          {
            rf_ai_numeric_mode_write(a1, 2, -1, -1);
            rf_ai_secondary_state_write((int)a1, 0);
            duration = rf_sound_query_duration(v6);
            rf_replicator_arm_milliseconds(a1 + 311, (int)(duration * 1000.0) + 500);
          }
          rf_entity_replace_speech_voice(*a1, v6, 0);
        }
      }
    }
    else
    {
      v1 = rand();
      rf_replicator_arm_milliseconds(a1 + 312, v1 % 4000 + 6000);
    }
  }
}

