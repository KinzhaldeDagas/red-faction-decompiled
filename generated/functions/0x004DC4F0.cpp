// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DC4F0 rf_player_update_environment_voice_50
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Cdecl player. Missing resolved entity returns0 without touching existing voice. Condition requires4362E0(entity) AL EXACT1 (referenced room/environment byte66) AND ORDERED entity armor float56<=0; NaN armor fails condition. If condition true and stored player voice4432 is not playing, plays event50(options0,0.0,1.0), stores returned handle including-1. If condition false and handle!=-1, stops voice and writes raw DWORD-1. Decompiler a1[1108]=NAN is integer handle invalidation, not a floating-point state update. EAX is incidental entity/voice/player/helper bits, not float pointer/status contract.
float *__cdecl rf_player_update_environment_voice_50(float *a1)
{
  float *result; // eax
  bool v2; // [esp+Bh] [ebp-5h]
  float *v3; // [esp+Ch] [ebp-4h]

  v2 = 0;
  result = (float *)rf_entity_resolve_handle(*((_DWORD *)a1 + 5));
  v3 = result;
  if ( result )
  {
    if ( rf_object_cached_room_byte66(result) == 1 )
      v2 = v3[14] <= 0.0;
    if ( v2 )
    {
      result = (float *)rf_gamesound_voice_is_playing(*((_DWORD *)a1 + 1108));
      if ( !result )
      {
        result = (float *)rf_gamesound_play_event(50, 0, 0.0, 1.0);
        *((_DWORD *)a1 + 1108) = result;
      }
    }
    else
    {
      result = a1;
      if ( *((_DWORD *)a1 + 1108) != -1 )
      {
        rf_gamesound_stop_voice_handle(*((_DWORD *)a1 + 1108));
        a1[1108] = NAN;
        return a1;
      }
    }
  }
  return result;
}

