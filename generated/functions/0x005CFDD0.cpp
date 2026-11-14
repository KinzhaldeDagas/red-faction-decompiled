// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CFDD0 rf_audio_stream_start_periodic_timer
// UNREALRED VERIFIED [audio-streaming-20261028]: Arguments delay milliseconds,user slot. Calls timeSetEvent(delay,delay,callback0x5CFDF0,user,flags1), returns timer ID or failure0. Delay used for BOTH interval and resolution; no retries or validation. Stream creation supplies250ms.
MMRESULT __cdecl rf_audio_stream_start_periodic_timer(UINT uDelay, DWORD_PTR dwUser)
{
  return timeSetEvent(uDelay, uDelay, rf_audio_stream_timer_callback, dwUser, 1u);
}

