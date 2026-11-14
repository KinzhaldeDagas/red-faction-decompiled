// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AED90 rf_splitscreen_begin_player_respawn_fade
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Cdecl player. Set playerBYTE4592=1, float4596=0.0, then gamesound event58 with(0,0.0,1.0), return sound delegate EAX. No player/runtime/death/duplicate-fade
// guard; leaves second phase BYTE4593 untouched. Does not create new entity or advance elapsed time here. Native fade renderer4AF0E0 owns later spawn threshold.
int __cdecl rf_splitscreen_begin_player_respawn_fade(int a1)
{
  *(_BYTE *)(a1 + 4592) = 1;
  *(float *)(a1 + 4596) = 0.0;
  return rf_gamesound_play_event(58, 0, 0.0, 1.0);
}

