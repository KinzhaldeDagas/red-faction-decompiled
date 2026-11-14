// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005946B0 rf_window_close_stored_thread_handle
// UNREALRED VERIFIED [system-progress-20261028]: If HANDLE global0x1BC2130 nonnull,CloseHandle then clears it regardless API result. Does not terminate,wait for,or join thread,close HWND or post a message.
void __cdecl rf_window_close_stored_thread_handle()
{
  if ( MEMORY[0x1BC2130] )
  {
    CloseHandle(MEMORY[0x1BC2130]);
    MEMORY[0x1BC2130] = nullptr;
  }
}

