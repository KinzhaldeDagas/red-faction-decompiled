// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00405800 rf_ai_mode15_acquire_or_track_target
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI weighted-target/mode11/15/16/speech/stimulus chains, original dispatch/float constants and native field
// lifetime and native signed/x87/stack/callback ABI): One AI block, central mode15 callback. Resolve COMMON target+704. Existing: if BYTE+669==0, float32 squared COMMON-position
// distance ordered>400 calls guarded target clear-1 and locally suppresses rest EVEN if clear rejected; equality/NaN retain. Otherwise410920(owner,target COMMON+60) then4025D0
// probes. No scan timer test on existing-target branch. Missing: ALWAYS405330 yaw sweep, then require+732 deadline elapsed EXACT1 and owner DWORD+504!=1; only then rearm scan
// deadline from difficulty table (owner504==1 leaves expired timer untouched). Replacement predicate EXACT1 ->402160(owner,30.0f,extra unused difficulty+2); result!=-1 calls guarded
// setter then forcesBYTE+669=1 regardless of setter acceptance. Extra effects require global entity681E38 nonnull and its full handle==candidate. If AI flags+1328 mask0x400000 clear,
// choose441250 even if later silenced; owner+2068 mask0x200 then forces sound=-1. Speech-body predicate EXACT1 uses replace-speech(owner,sound,0); other AL positional
// event(sound,owner COMMON+60,1.0,ADDRESS17F10B0,0), even sound-1. Regardless of mask0x400000, then405A60 peer propagation and mission-event lookup using block+1228; found enclosing
// event DWORD+656==46 activates via ECX=event, stack(-1,-1,1). No direct mission activation for other target candidates or existing-target path; no authority gate.
void __cdecl rf_ai_mode15_acquire_or_track_target(int *a1)
{
  float v1; // [esp+Ch] [ebp-1Ch]
  char v2; // [esp+13h] [ebp-15h]
  int v3; // [esp+18h] [ebp-10h]
  int *v4; // [esp+1Ch] [ebp-Ch]
  int v5; // [esp+20h] [ebp-8h]
  int v6; // [esp+24h] [ebp-4h]

  v6 = rf_object_resolve_handle(a1[176]);
  if ( v6 )
  {
    v2 = 1;
    if ( !*((_BYTE *)a1 + 669) )
    {
      v1 = rf_vector_distance_squared((const float *)(*a1 + 60), (const float *)(v6 + 60));
      if ( v1 > 400.0 )
      {
        sub_40BA80(a1, -1);
        v2 = 0;
      }
    }
    if ( v2 == 1 )
    {
      sub_410920(*a1, (const float *)(v6 + 60));
      rf_ai_refresh_target_collision_and_corridor_probes(a1, v6);
    }
  }
  else
  {
    rf_ai_update_authored_yaw_sweep(a1);
    if ( rf_replicator_has_elapsed(a1 + 183) && *(_DWORD *)(*a1 + 504) != 1 )
    {
      rf_replicator_arm_milliseconds(a1 + 183, dword_661274[dword_6612A4]);
      if ( rf_ai_should_seek_replacement_target(a1) )
      {
        v5 = rf_ai_choose_weighted_target_handle((const float *)*a1, 30.0);
        if ( v5 != -1 )
        {
          sub_40BA80(a1, v5);
          *((_BYTE *)a1 + 669) = 1;
          if ( dword_681E38 )
          {
            if ( *(_DWORD *)(dword_681E38 + 44) == v5 )
            {
              if ( (a1[332] & 0x400000) == 0 )
              {
                v3 = rf_foley_registry_choose_sound_441250(*(_DWORD *)(*(_DWORD *)(*a1 + 660) + 1780));
                if ( (*(_DWORD *)(*a1 + 2068) & 0x200) != 0 )
                  v3 = -1;
                if ( rf_entity_admits_speech_body_actions(*a1) )
                  rf_entity_replace_speech_voice(*a1, v3, 0);
                else
                  rf_gamesound_play_positional_event(v3, (float *)(*a1 + 60), 1.0, (int)&unk_17F10B0, 0);
              }
              rf_ai_propagate_target_to_linked_entities(a1);
              v4 = (int *)rf_mission_event_find_by_uid(a1[307]);
              if ( v4 )
              {
                if ( v4[164] == 46 )
                  rf_mission_event_activate(v4, -1, -1, 1);
              }
            }
          }
        }
      }
    }
  }
}

