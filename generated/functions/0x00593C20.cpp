// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593C20 rf_window_cbt_hook_block_f040_f050_commands
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tokenizer ownership/quote rules, native hook contracts, observer registration, startup signaling and thread-exit/calling-convention paths): STDCALL hook callback(code,wParam,lParam), RET12. Returns1 exactly when code==8 and wParam equals0xF040 or0xF050; comparison does not mask command low bits. All other cases forward CallNextHookEx using handle1BC2008. No window/state filtering or direct message dispatch here.
LRESULT __stdcall rf_window_cbt_hook_block_f040_f050_commands(int code, WPARAM wParam, LPARAM lParam)
{
  if ( code == 8 && (wParam == 61504 || wParam == 61520) )
    return 1;
  else
    return CallNextHookEx(unk_1BC2008, code, wParam, lParam);
}

