// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C5850 rf_glass_smash_sound_play
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original fragment spawn and bounded pool, eight-vertex twelve-triangle layout, fourteen-ray scoring, full room-pointer ABI and native glass branching): 
// Cdecl impactPosition. Samples one event from global Smash Foley set, plays positional(event,position,volume1,listener17F10B0,flags0); playback return ignored. Queries duration for
// selected EVENT, not returned voice; F32duration then duration*DOUBLE500, __ftol2_sse truncates towardzero, arms shared deadline822764 and returns arm result. No event<0 check,
// voice tracking, duration validity/positivity clamp or existing deadline extension policy; each call overwrites/rearms even if playback failed. This is half-duration seconds
// converted to milliseconds, no shard allocation here.
int __cdecl rf_glass_smash_sound_play(float *a1)
{
  float duration; // [esp+Ch] [ebp-8h]
  int v3; // [esp+10h] [ebp-4h]

  v3 = rf_foley_choose_random_sound(rf_glass_smash_foley_id);
  rf_gamesound_play_positional_event(v3, a1, 1.0, (int)flt_17F10B0, 0);
  duration = rf_sound_query_duration(v3);
  return rf_replicator_arm_milliseconds(&unk_822764, (int)(duration * 500.0));
}

