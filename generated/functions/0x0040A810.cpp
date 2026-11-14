// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040A810 rf_ai_propagate_stimulus_to_nearby_entities
// UNREALRED VERIFIED [ai-target-commit-20261029] This propagated stimulus path calls0x40BA80 then continues scripted/action/mode/route handling without interpreting its return as a bool. Do not globally suppress all native reaction side effects merely because a target write was rejected. Complete native stimulus/peer transition parity remains a separate dependency from host callback invalidation.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI weighted-target/mode11/15/16/speech/stimulus chains, original dispatch/float constants and native field
// lifetime and native signed/x87/stack/callback ABI): Four consumed cdecl args(target HANDLE,stimulus point pointer,radius FLOAT,LOWBYTE policy); fifth extra caller slot ignored by
// native body. Pause BYTE6663D1==EXACT1 exits. Ordered radius>shared FLOAT6663CC records new shared radius and proceeds; otherwise shared deadline6663E0 must be elapsed, then clears
// shared radius0 and proceeds WITHOUT recording input radius. Resolves target COMMON object, arms shared deadline750ms, resolves target again for source-room comparison. Walk entity
// list next+652, excluding first resolved pointer. Reject inactive EXACT1; require mode2/4, entity+2000 masks0x40000000/0x800 clear, nonplayer-sentient/runtime-enabled predicate, no
// turret flag, no stationary-class predicate, DWORD+504!=2. Require selected weapon+676==global911CE0 OR cached room exists with BYTE room+352 nonzero. Special-weapon shortcut SKIPS
// assigning local cached-room variable; later source-room comparison may therefore use uninitialized/prior-candidate room value. Nonnull second resolved source whose cached room
// equals that local value and policy ANY nonzero changes STACK radius argument to1000.0f, persisting for all later candidates even different rooms. Fast distance to stimulus
// roundedfloat32 admits radius>=distance OR UNORDERED. Entity+2000 mask0x800000 suppresses admitted candidate. Then guarded target setter, clear scripted-animation context and cancel
// body action execute WITHOUT interpreting target setter return. Mode4 requests mode2(-1,-1) and arms entity+1916 inclusive5000..8000ms. If weapon!=-1 AND policy==EXACT1: normalize
// stimulus-minus-common-position, dot facing+2040; ordered dot>=entity threshold+2112 marks FOV accepted. Missing FOV OR any-nonzero geometry obstruction(entity+2004,stimulus,3,NULL)
// leads to position-copy entity+1772, mode6(-1,-1),secondary12 and entity+1232 timer500ms, EXCEPT DWORD+504==0 and entity DWORD+1856==2 skips these later writes while preserving
// prior effects. If weapon==-1 AND policy==EXACT1 instead calls40AC80(entityAI,target,random FLOAT10..20). Other nonzero policy values may enlarge radius but do not enter either
// exact1 reaction branch. No own dead, authority, team-match, source-point-null or finite admission. Return incidental. Preserve mutable-radius lifetime, uninitialized/prior room and
// partial side effects.
char __cdecl rf_ai_propagate_stimulus_to_nearby_entities(int a1, float *lhs, float a3, char a4)
{
  void *v4; // eax
  int first_dword; // eax
  float v7; // [esp+4h] [ebp-38h]
  float copy_result[3]; // [esp+8h] [ebp-34h] BYREF
  char v9; // [esp+17h] [ebp-25h]
  float out_vector[3]; // [esp+18h] [ebp-24h] BYREF
  float v11; // [esp+24h] [ebp-18h]
  int v12; // [esp+28h] [ebp-14h]
  void *v13; // [esp+2Ch] [ebp-10h]
  void *i; // [esp+30h] [ebp-Ch]
  float v15; // [esp+34h] [ebp-8h]
  void *v16; // [esp+38h] [ebp-4h]

  LOBYTE(v4) = byte_6663D1;
  if ( byte_6663D1 != 1 )
  {
    if ( flt_6663CC < (double)a3 )
    {
      flt_6663CC = a3;
LABEL_6:
      v13 = (void *)rf_object_resolve_handle(a1);
      rf_replicator_arm_milliseconds(&dword_6663E0, 750);
      v4 = (void *)rf_object_resolve_handle(a1);
      v16 = v4;
      for ( i = (void *)unk_68211C; ; i = v4 )
      {
        if ( i == &unk_681E90 )
          return (char)v4;
        if ( i != v13
          && !rf_object_has_respawn_inactive_flag((int)i)
          && (*((_DWORD *)i + 328) == 2 || *((_DWORD *)i + 328) == 4)
          && (*((_DWORD *)i + 500) & 0x40000000) == 0
          && rf_entity_is_nonplayer_sentient_or_runtime_enabled((int)i)
          && !rf_entity_has_turret_flag((int)i)
          && !sub_40D380((int)i)
          && (*((_DWORD *)i + 500) & 0x800) == 0
          && *((_DWORD *)i + 126) != 2
          && (*((_DWORD *)i + 169) == unk_911CE0 || (v12 = rf_receiver_get_first_dword(i)) != 0 && *(_BYTE *)(v12 + 352)) )
        {
          if ( v16 )
          {
            first_dword = rf_receiver_get_first_dword(v16);
            if ( first_dword == v12 )
            {
              if ( a4 )
                a3 = 1000.0;
            }
          }
          v15 = rf_vector_fast_distance(lhs, (const float *)i + 15);
          if ( a3 >= (double)v15 && ((unsigned int)&unk_800000 & *((_DWORD *)i + 500)) == 0 )
          {
            sub_40BA80((int *)i + 168, a1);
            rf_ai_clear_scripted_animation_context((_DWORD *)i + 168);
            rf_ai_cancel_tracked_body_action((_DWORD *)i + 168);
            if ( *((_DWORD *)i + 328) == 4 )
            {
              rf_ai_numeric_mode_write((_DWORD *)i + 168, 2, -1, -1);
              rf_timestamp_arm_random_inclusive_milliseconds((int *)i + 479, 5000, 8000);
            }
            if ( *((_DWORD *)i + 169) != -1 && a4 == 1 )
            {
              v9 = 0;
              rf_vector_subtract(lhs, out_vector, (const float *)i + 15);
              rf_vector_normalize_reciprocal_sqrt(out_vector);
              v11 = rf_vector_dot((float *)i + 510, out_vector);
              if ( *((float *)i + 528) <= (double)v11 )
                v9 = 1;
              if ( !v9 || rf_geometry_segment_is_obstructed((int)i + 2004, (int)lhs, 3, 0) )
              {
                if ( !*((_DWORD *)i + 126) && *((_DWORD *)i + 464) == 2 )
                  goto LABEL_7;
                rf_vector_copy((float *)i + 443, copy_result, lhs);
                rf_ai_numeric_mode_write((_DWORD *)i + 168, 6, -1, -1);
                rf_ai_secondary_state_write((int)i + 672, 12);
                rf_replicator_arm_milliseconds((int *)i + 308, 500);
              }
            }
            if ( *((_DWORD *)i + 169) == -1 && a4 == 1 )
            {
              v7 = rf_random_float_range(10.0, 20.0);
              sub_40AC80((int *)i + 168, a1, v7);
            }
          }
        }
LABEL_7:
        v4 = *((void **)i + 163);
      }
    }
    LOBYTE(v4) = rf_replicator_has_elapsed(&dword_6663E0);
    if ( (_BYTE)v4 )
    {
      flt_6663CC = 0.0;
      goto LABEL_6;
    }
  }
  return (char)v4;
}

