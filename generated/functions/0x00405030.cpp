// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00405030 sub_405030
// UNREALRED VERIFIED [combat-panic-20261104]: Speech gate: notEntityFlags2 bit200,mode17or7,humanoid,alive,AI+4E4 elapsed; mode7 additionally selectedprimary!=-1 or movement-vector length>=.1. Select persona Panic441460 for17/Flee4412E0 for7, stop existing speech BEFORE replacement, replace(selected,0), query selected duration.17: duration>.1 arms truncatedseconds*1000 else3000.7: rand()%3000 +truncdurationms+10000. This is a retained entity speech channel, not generic pain/death or HUD persona audio.
// UNREALRED VERIFIED [combat-entity-speech-20261111]: AI speech cadence is separate AI+4E4, armed0 by4033C0. Gates: Entity+814 bit200 clear, mode17/7, humanoid,alive,elapsed. Mode7 gate uses AI+4 SELECTED PRIMARY WEAPON ID (Entity+2A4), not target; if selected==-1 require length(AI+500)>=float0.1. Select persona Panic441460 for17/Flee4412E0 for7, query existing playback, stop only if playing, call replacement(selected,0) including selected-1, then query duration separately. Finite17 duration>float0.1 arms trunc(double(duration)*1000), else3000. Mode7 draws rand()%3000 after duration query and adds truncdurationms+10000. Native404F90 calls route update then this regardless route result; only lifetime/provider failure is a host boundary, not native no-route.
void __cdecl sub_405030(int *a1)
{
  int v1; // esi
  float duration; // [esp+4h] [ebp-8h]
  int v3; // [esp+8h] [ebp-4h]

  if ( (*(_DWORD *)(*a1 + 2068) & 0x200) == 0
    && (a1[160] == 17 || a1[160] == 7)
    && (a1[160] != 7 || a1[1] != -1 || rf_vector3_length((float *)a1 + 320) >= 0.1000000014901161)
    && rf_entity_has_humanoid_flag(*a1)
    && !rf_entity_is_dead(*a1)
    && rf_replicator_has_elapsed(a1 + 313) )
  {
    if ( a1[160] == 17 )
      v3 = sub_441460(*(_DWORD *)(*(_DWORD *)(*a1 + 660) + 1780));
    else
      v3 = sub_4412E0(*(_DWORD *)(*(_DWORD *)(*a1 + 660) + 1780));
    if ( rf_entity_speech_voice_is_playing(*a1) )
      rf_entity_stop_speech_voice(*a1);
    rf_entity_replace_speech_voice(*a1, v3, 0);
    duration = rf_sound_query_duration(v3);
    if ( a1[160] == 17 )
    {
      if ( duration > 0.1000000014901161 )
        rf_replicator_arm_milliseconds(a1 + 313, (int)(duration * 1000.0));
      else
        rf_replicator_arm_milliseconds(a1 + 313, 3000);
    }
    else
    {
      v1 = rand() % 3000;
      rf_replicator_arm_milliseconds(a1 + 313, v1 + (int)(duration * 1000.0) + 10000);
    }
  }
}

