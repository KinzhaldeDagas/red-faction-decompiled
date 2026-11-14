// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578E70 rf_text_parser_restore_cursor_bookmark
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus8B bookmark input,RET4. Restores line264 from bookmark0,cursor4 from bookmark4,and returns receiver. No buffer/file association,range/liveness or line-number validation;other parser fields unchanged.
_DWORD *__thiscall rf_text_parser_restore_cursor_bookmark(_DWORD *this, _DWORD *a2)
{
  *(this + 66) = *a2;
  *(this + 1) = a2[1];
  return this;
}

