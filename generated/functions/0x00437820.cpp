// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437820 rf_entity_stop_speech_voice
// UNREALRED VERIFIED [entity-speech-lifecycle-20261027] Entity speech stop: if owner+0x1400 != -1, call common stop_voice_handle then write -1. Does not reset owner+0x1408 duration, +0x140C action deadline, persona presentation or ordinary message state.
int __cdecl rf_entity_stop_speech_voice(int a1)
{
  int result; // eax

  result = a1;
  if ( *(_DWORD *)(a1 + 5120) != -1 )
  {
    rf_gamesound_stop_voice_handle(*(_DWORD *)(a1 + 5120));
    *(_DWORD *)(a1 + 5120) = -1;
    return a1;
  }
  return result;
}

