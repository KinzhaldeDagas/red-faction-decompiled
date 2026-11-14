// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00404900 rf_ai_play_target_acquisition_speech
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI weighted-target/mode11/15/16/speech/stimulus chains, original dispatch/float constants and native field
// lifetime and native signed/x87/stack/callback ABI): Cdecl(AI block,new candidate HANDLE). Requires shared deadline6663DC elapsed, humanoid, dead!=EXACT1, primary selected
// index+4!=-1, attached-use-vehicle!=EXACT1. Sound starts-1. New candidate ENTITY flags+2000 mask0x10000 and owner secondary flags+2068 mask0x200 clear ->441280(class voice
// index+1780); if resulting sound==-1 and same owner mask clear fallback441250. Even silence or no valid sound still replace-speech(owner,sound,0), propagate40A810(RETAINED block
// target+704,owner common+60,10.0f,LOWBYTE1,extra0), query duration(sound), arm OWNER+1860 with LOW32 trunc(float32(duration)*1000+0.5)+250, then shared6663DC with rand()%4000+LOW32
// trunc(float32(duration)*1000)+6000. Retained propagation handle may differ from new candidate parameter because404740 commits target afterwards. Timer integer additions wrap, no
// clamp/playback-success check. Any-nonzero timer/humanoid predicates, exact1 dead/vehicle veto. EAX/AL path-dependent.
char __cdecl rf_ai_play_target_acquisition_speech(int *a1, int a2)
{
  char result; // al
  int v3; // esi
  float duration; // [esp+10h] [ebp-Ch]
  int v5; // [esp+14h] [ebp-8h]
  int v6; // [esp+18h] [ebp-4h]

  result = rf_replicator_has_elapsed(&dword_6663DC);
  if ( result )
  {
    result = rf_entity_has_humanoid_flag(*a1);
    if ( result )
    {
      result = rf_entity_is_dead(*a1);
      if ( result != 1 && a1[1] != -1 )
      {
        result = rf_entity_has_attached_use_vehicle(*a1);
        if ( result != 1 )
        {
          v5 = -1;
          v6 = rf_entity_resolve_handle(a2);
          if ( v6 && (*(_DWORD *)(v6 + 2000) & 0x10000) != 0 && (*(_DWORD *)(*a1 + 2068) & 0x200) == 0 )
            v5 = rf_foley_registry_choose_sound_441280(*(_DWORD *)(*(_DWORD *)(*a1 + 660) + 1780));
          if ( v5 == -1 && (*(_DWORD *)(*a1 + 2068) & 0x200) == 0 )
            v5 = rf_foley_registry_choose_sound_441250(*(_DWORD *)(*(_DWORD *)(*a1 + 660) + 1780));
          rf_entity_replace_speech_voice(*a1, v5, 0);
          rf_ai_propagate_stimulus_to_nearby_entities(a1[176], *a1 + 60, 10.0, 1);
          duration = rf_sound_query_duration(v5);
          rf_replicator_arm_milliseconds((int *)(*a1 + 1860), (int)(duration * 1000.0 + 0.5) + 250);
          v3 = rand() % 4000;
          return rf_replicator_arm_milliseconds(&dword_6663DC, v3 + (int)(duration * 1000.0) + 6000);
        }
      }
    }
  }
  return result;
}

