// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578E40 rf_text_parser_save_cursor_bookmark
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus8B bookmark output,RET4. Stores DWORD line264 at bookmark0 and cursor pointer4 at bookmark4,returns bookmark pointer. Does not save buffer pointer,filename,size or ownership and does not move cursor. No output bounds/alias check.
_DWORD *__thiscall rf_text_parser_save_cursor_bookmark(_DWORD *this, _DWORD *a2)
{
  *a2 = *(this + 66);
  a2[1] = *(this + 1);
  return a2;
}

