// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004897F0 rf_mover_stop_loop_voice
// UNREALRED VERIFIED [mission-mover-runtime-20261013] Stops and clears only the retained sound-slot1 voice at mover+0x320; unlike0x488BE0 it does not start sound slot2.
int __cdecl rf_mover_stop_loop_voice(int a1)
{
  int result; // eax

  result = a1;
  if ( *(_DWORD *)(a1 + 800) != -1 )
  {
    rf_gamesound_stop_voice_handle(*(_DWORD *)(a1 + 800));
    *(_DWORD *)(a1 + 800) = -1;
    return a1;
  }
  return result;
}

