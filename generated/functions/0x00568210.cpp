// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568210 rf_gamesound_release_voice_slot
// UNREALRED VERIFIED [sound-spatialization]: Clears one 44-byte gamesound voice slot while preserving its generation counter for stale-handle rejection.
int __cdecl rf_gamesound_release_voice_slot(int a1)
{
  *(_DWORD *)a1 = -1;
  *(_DWORD *)(a1 + 4) = -1;
  *(_DWORD *)(a1 + 8) = 0;
  *(float *)(a1 + 16) = 0.0;
  *(float *)(a1 + 36) = 0.0;
  *(float *)(a1 + 20) = 0.0;
  return a1;
}

