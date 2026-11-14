// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004377A0 rf_entity_speech_voice_is_playing
// UNREALRED VERIFIED [entity-speech-lifecycle-20261027] Entity speech playback query: requires owner+0x1400 != -1 and common gamesound voice_is_playing(handle) nonzero. Does not clear stale/completed handles or mutate speech countdown/timer.
bool __cdecl rf_entity_speech_voice_is_playing(int a1)
{
  return *(_DWORD *)(a1 + 5120) != -1 && rf_gamesound_voice_is_playing(*(_DWORD *)(a1 + 5120)) != 0;
}

