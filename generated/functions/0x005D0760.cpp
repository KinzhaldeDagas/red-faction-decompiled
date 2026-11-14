// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D0760 rf_audio_streaming_initialize_slots
// UNREALRED VERIFIED [audio-streaming-20261028]: Initializes critical section0x1E014B0, calls timeBeginPeriod(1) without checking result. For16 slots sets timer+16=0,drain counter+20=0,write cursor+12=0,backend buffer+4=-1,source sample+0=-1. Does NOT initialize flags+24 or ring bytes+8; initial BSS state may be relied on. Return loop value16 rather than timer API result. No repeated-initialization guard.
MMRESULT rf_audio_streaming_initialize_slots()
{
  MMRESULT result; // eax
  int i; // [esp+0h] [ebp-4h]

  InitializeCriticalSection(&unk_1E014B0);
  result = timeBeginPeriod(1u);
  for ( i = 0; i < 16; ++i )
  {
    unk_1E01300[7 * i] = 0;
    unk_1E01304[7 * i] = 0;
    unk_1E012FC[7 * i] = 0;
    unk_1E012F4[7 * i] = -1;
    unk_1E012F0[7 * i] = -1;
    result = i + 1;
  }
  return result;
}

