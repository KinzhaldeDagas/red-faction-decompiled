// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593DF0 rf_window_initialize_thread_and_optional_hooks
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tokenizer ownership/quote rules, native hook contracts, observer registration, startup signaling and thread-exit/calling-convention paths): Cdecl application/class name, initial title, install-hooks byte, windowed byte. Stores normalized windowed flag1BC2140; unbounded-copies app name to2090 mutex-name buffer and1BC1F08 class buffer, title to1BC1F88. In nonwindowed mode creates initially-owned named mutex; last-error183 finds existing class/title window, attempts foreground then exit1. Otherwise closes mutex handle immediately, so handle is not retained as lifetime guard. Initializes shared critical section, creates auto-reset nonsignaled event, starts worker594130 with event, waits5000ms and closes event; API failures/wait result ignored. Sets startup flag1BC2138=1 regardless worker success, then detects run-title
// window via593FE0. If hook byte nonzero installs IDs2 and5 with moduleNULL/threadId0; failures unchecked. Returns atexit registration result for5946B0, which only closes/clears stored thread HANDLE, without joining/terminating thread, closing window or uninstalling hooks. No prior-init cleanup or callback-count reset.
int __cdecl rf_window_initialize_thread_and_optional_hooks(CHAR *a1, CHAR *a2, char a3, char a4)
{
  CHAR v5; // [esp+3h] [ebp-39h]
  int *v6; // [esp+8h] [ebp-34h]
  CHAR *v7; // [esp+Ch] [ebp-30h]
  char v8; // [esp+13h] [ebp-29h]
  CHAR *v9; // [esp+18h] [ebp-24h]
  CHAR v11; // [esp+23h] [ebp-19h]
  CHAR *v12; // [esp+28h] [ebp-14h]
  CHAR *v13; // [esp+2Ch] [ebp-10h]
  HWND hWnd; // [esp+30h] [ebp-Ch]
  HANDLE hObject; // [esp+34h] [ebp-8h]
  HANDLE lpParameter; // [esp+38h] [ebp-4h]

  unk_1BC2140 = a4 != 0;
  v13 = a1;
  v12 = unk_1BC2090;
  do
  {
    v11 = *v13;
    *v12++ = *v13++;
  }
  while ( v11 );
  v9 = MEMORY[0x1BC1F88];
  do
  {
    v8 = *a2;
    *v9++ = *a2++;
  }
  while ( v8 );
  v7 = a1;
  v6 = &dword_1BA1F00[32770];
  do
  {
    v5 = *v7;
    *(_BYTE *)v6 = *v7++;
    v6 = (int *)((char *)v6 + 1);
  }
  while ( v5 );
  if ( !unk_1BC2140 )
  {
    hObject = CreateMutexA(nullptr, 1, unk_1BC2090);
    if ( GetLastError() == 183 )
    {
      hWnd = FindWindowA((LPCSTR)&dword_1BA1F00[32770], MEMORY[0x1BC1F88]);
      if ( hWnd )
        SetForegroundWindow(hWnd);
      exit(1);
    }
    CloseHandle(hObject);
  }
  InitializeCriticalSection(&unk_1BC2110);
  lpParameter = CreateEventA(nullptr, 0, 0, nullptr);
  MEMORY[0x1BC2130] = CreateThread(
                        nullptr,
                        0,
                        (LPTHREAD_START_ROUTINE)rf_window_thread_message_pump,
                        lpParameter,
                        0,
                        (LPDWORD)&dword_1BA1F00[32769]);
  WaitForSingleObject(lpParameter, 0x1388u);
  CloseHandle(lpParameter);
  unk_1BC2138 = 1;
  rf_window_detect_run_title_for_executable();
  if ( a3 )
  {
    dword_1BA1F00[0x8000] = (int)SetWindowsHookExA(2, rf_window_keyboard_hook_block_ctrl_alt_escape_tab, nullptr, 0);
    unk_1BC2008 = SetWindowsHookExA(5, rf_window_cbt_hook_block_f040_f050_commands, nullptr, 0);
  }
  return atexit(rf_window_close_stored_thread_handle);
}

