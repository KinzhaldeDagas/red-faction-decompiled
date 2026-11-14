// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593BA0 rf_window_keyboard_hook_block_ctrl_alt_escape_tab
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tokenizer ownership/quote rules, native hook contracts, observer registration, startup signaling and thread-exit/calling-convention paths): STDCALL keyboard hook(code,wParam,lParam), RET12. Only code0 applies filters: Escape27 plus GetAsyncKeyState(Control17) bit15 set returns1; Tab9 or Escape27 plus lParam bit29(0x20000000) returns1. No key-up/down bit31 filter or window-active check here. All other cases forward CallNextHookEx with stored hook handle1BC1F00 and unchanged arguments. Does not install/uninstall hook, call input callbacks or change key states.
LRESULT __stdcall rf_window_keyboard_hook_block_ctrl_alt_escape_tab(int code, WPARAM wParam, LPARAM lParam)
{
  if ( code )
    return CallNextHookEx((HHOOK)dword_1BA1F00[0x8000], code, wParam, lParam);
  if ( wParam == 27 && GetAsyncKeyState(17) >> 15 )
    return 1;
  if ( wParam == 9 && (lParam & 0x20000000) != 0 )
    return 1;
  if ( wParam == 27 && (lParam & 0x20000000) != 0 )
    return 1;
  else
    return CallNextHookEx((HHOOK)dword_1BA1F00[0x8000], code, wParam, lParam);
}

