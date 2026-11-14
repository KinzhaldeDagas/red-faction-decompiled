// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CFDF0 rf_audio_stream_timer_callback
// UNREALRED VERIFIED [audio-streaming-20261028]: Five WinMM callback arguments; uses only dwUser as stream slot index. Enters global critical section0x1E014B0, calls0x5D0540(slot), leaves critical section. Does not check slot range, timer ID or subsystem lifetime; synchronization is callback-side, not automatically present in public slot helpers.
void __stdcall rf_audio_stream_timer_callback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
  EnterCriticalSection(&unk_1E014B0);
  rf_audio_stream_service_slot(dwUser);
  LeaveCriticalSection(&unk_1E014B0);
}

