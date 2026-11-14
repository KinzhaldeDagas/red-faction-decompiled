// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CFE40 rf_audio_stream_kill_slot_timer
// UNREALRED VERIFIED [audio-streaming-20261028]: Argument pointer to28-byte stream record, NOT slot index. If timerDWORD+16 nonzero, calls timeKillEvent and clears it regardless result. Returns record pointer. Does not clear active flags, stop sound buffer or acquire critical section.
int __cdecl rf_audio_stream_kill_slot_timer(int a1)
{
  int result; // eax

  result = a1;
  if ( *(_DWORD *)(a1 + 16) )
  {
    timeKillEvent(*(_DWORD *)(a1 + 16));
    *(_DWORD *)(a1 + 16) = 0;
    return a1;
  }
  return result;
}

