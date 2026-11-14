// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593D80 rf_window_copy_title_and_set_window_text
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tokenizer ownership/quote rules, native hook contracts, observer registration, startup signaling and thread-exit/calling-convention paths): Cdecl input title cstring. Unbounded-copies including NUL into fixed global title buffer at IMMEDIATE address1BC1F88, then calls SetWindowTextA on main HWND1BC212C using that buffer, returns BOOL32 API result. Raw MOV immediate593D8C and PUSH immediate593DC1 prove address; pseudocode MEMORY notation is not a loaded title-buffer pointer. No input/length/HWND check, allocation, class-name update or lock acquisition.
int __cdecl rf_window_copy_title_and_set_window_text(const char *title)
{
  char v1; // dl
  CHAR *v3; // [esp+8h] [ebp-8h]

  v3 = MEMORY[0x1BC1F88];
  do
  {
    v1 = *title;
    *v3++ = *title++;
  }
  while ( v1 );
  return SetWindowTextA(hWnd, MEMORY[0x1BC1F88]);
}

