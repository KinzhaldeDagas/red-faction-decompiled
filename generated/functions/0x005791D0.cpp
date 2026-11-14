// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005791D0 rf_memory_text_parser_reset_cursor_if_loaded
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): ECX receiver. If buffer DWORD0 nonNULL,sets DWORD264=1 and cursor DWORD4=buffer;otherwise leaves all fields untouched. Always returns receiver. Does not reload file,clear filename/update size268,allocate or free. Field264 is the CR-based line number:579200 prints it as line #%d;5789E0 and line readers increment it on CR,not LF.
_DWORD *__thiscall rf_memory_text_parser_reset_cursor_if_loaded(_DWORD *this)
{
  _DWORD *result; // eax

  result = this;
  if ( *this )
  {
    *(this + 66) = 1;
    *(this + 1) = *this;
    return this;
  }
  return result;
}

