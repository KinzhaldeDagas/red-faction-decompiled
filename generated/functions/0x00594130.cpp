// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00594130 rf_window_thread_message_pump
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tokenizer ownership/quote rules, native hook contracts, observer registration, startup signaling and thread-exit/calling-convention paths): Worker takes startup-event stack argument. Raw epilogue5941D3 is plain C3 RET, not RET4: corrected false auto-stdcall signature to cdecl despite being passed to CreateThread. Calls5941E0 window registration/create; false result returns0 WITHOUT signaling event. Otherwise SetEvent, loops until WaitMessage returns EXACT EAX1, enters shared critical section and drains PeekMessageA(NULL,0,0,PM_REMOVE). Queued message2 causes immediate Leave/DeleteCriticalSection and return0 BEFORE Translate/Dispatch. All other messages, including0x12 WM_QUIT, translated/dispatched while lock held; no quit-global213C read and no WM_QUIT-specific termination. Empty queue releases lock and returns to
// WaitMessage. No DestroyWindow, hook uninstall, handle close or ready/error publication here. Window-create helper can itself return1 after failed CreateWindowEx, so signaling is not proof of valid HWND.
unsigned int __cdecl rf_window_thread_message_pump(void *startup_event)
{
  struct tagMSG Msg; // [esp+4h] [ebp-1Ch] BYREF

  if ( !rf_window_register_class_and_create() )
    return 0;
  SetEvent(startup_event);
LABEL_4:
  while ( !WaitMessage() )
    ;
  EnterCriticalSection(&unk_1BC2110);
  while ( 1 )
  {
    if ( !PeekMessageA(&Msg, nullptr, 0, 0, 1u) )
    {
      LeaveCriticalSection(&unk_1BC2110);
      goto LABEL_4;
    }
    if ( Msg.message == 2 )
      break;
    TranslateMessage(&Msg);
    DispatchMessageA(&Msg);
  }
  LeaveCriticalSection(&unk_1BC2110);
  DeleteCriticalSection(&unk_1BC2110);
  return 0;
}

