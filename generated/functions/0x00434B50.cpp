// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00434B50 rf_entity_try_play_vehicle_impact_foley
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion dispatch, buffered pose consumers, contact effects, selector filtering and x87 unordered branches): Cdecl(entity,soundPosition). Admits squared velocity324>=2240^2*float0.2 OR unordered: native compares threshold against speed then AH41/JNZ. Requires saved voice5240 notplaying;then ONLY ORDERED dot(common forward96,contact normal448)<double-0.4000000059604645. Chooses random sound from global681E18,plays positional event at caller position with volume1,shared17F10B0 vector argument,flags0;stores returned voice ID5240 even failure. Does not stop existing playing voice,validate sound or clear physics state. No NULL/class/finite guard or own rate timer.
void __cdecl rf_entity_try_play_vehicle_impact_foley(int a1, float *a2)
{
  int v2; // eax
  float v3; // [esp+10h] [ebp-4h]

  if ( *(float *)(a1 + 2240) * *(float *)(a1 + 2240) * 0.2000000029802322 <= rf_vector_length_squared((float *)(a1 + 324))
    && !rf_gamesound_voice_is_playing(*(_DWORD *)(a1 + 5240)) )
  {
    v3 = rf_vector_dot((float *)(a1 + 96), (float *)(a1 + 448));
    if ( v3 < -0.4000000059604645 )
    {
      v2 = rf_foley_choose_random_sound(unk_681E18);
      *(_DWORD *)(a1 + 5240) = rf_gamesound_play_positional_event(v2, a2, 1.0, (int)&unk_17F10B0, 0);
    }
  }
}

