// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00404BB0 rf_ai_update_idle_speech_deadline
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI weighted-target/mode11/15/16/speech/stimulus chains, original dispatch/float constants and native field
// lifetime and native signed/x87/stack/callback ABI): One AI block. Owner flags+2068 mask1 or+2064 mask0x02000000 suppress. Require humanoid, dead!=EXACT1, block+1240 deadline
// elapsed, target handle+704==-1, mode2/4, and no current speech. Choose441310(class voice index+1780), replace-speech(owner,sound,1) without checking sound/playback success; round
// duration to float32 then rearm+1240 with rand()%30000+LOW32 trunc(duration*DOUBLE1000)+60000. Any-nonzero humanoid/elapsed; explicit exact1 dead. No multiplayer gate or timer reset
// on suppressed paths; return incidental.
char __cdecl rf_ai_update_idle_speech_deadline(int *a1)
{
  char result; // al
  int v2; // esi
  float duration; // [esp+4h] [ebp-8h]
  int v4; // [esp+8h] [ebp-4h]

  result = (char)a1;
  if ( (*(_DWORD *)(*a1 + 2068) & 1) == 0 )
  {
    result = (char)a1;
    if ( ((unsigned int)&unk_2000000 & *(_DWORD *)(*a1 + 2064)) == 0 )
    {
      result = rf_entity_has_humanoid_flag(*a1);
      if ( result )
      {
        result = rf_entity_is_dead(*a1);
        if ( result != 1 )
        {
          result = rf_replicator_has_elapsed(a1 + 310);
          if ( result )
          {
            if ( a1[176] == -1 )
            {
              if ( a1[160] == 2 || (result = (char)a1, a1[160] == 4) )
              {
                result = rf_entity_speech_voice_is_playing(*a1);
                if ( !result )
                {
                  v4 = rf_foley_registry_choose_sound_441310(*(_DWORD *)(*(_DWORD *)(*a1 + 660) + 1780));
                  rf_entity_replace_speech_voice(*a1, v4, 1);
                  duration = rf_sound_query_duration(v4);
                  v2 = rand() % 30000;
                  return rf_replicator_arm_milliseconds(a1 + 310, v2 + (int)(duration * 1000.0) + 60000);
                }
              }
            }
          }
        }
      }
    }
  }
  return result;
}

