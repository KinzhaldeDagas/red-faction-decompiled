// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D07F0 rf_audio_streaming_shutdown_slots
// UNREALRED VERIFIED [audio-streaming-20261028]: Walks16 slots,stops those whose active mask1set through0x5D0200. Calls timeEndPeriod(1) and DeleteCriticalSection. Does not explicitly drain callbacks or stop timers in slots whose active flagclear but timer nonzero. No initialization/lifetime validation or explicit source/DS resource release.
void rf_audio_streaming_shutdown_slots()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 16; ++i )
  {
    if ( (unk_1E01308[7 * i] & 1) != 0 )
      rf_audio_stream_stop_slot(i);
  }
  timeEndPeriod(1u);
  DeleteCriticalSection(&unk_1E014B0);
}

