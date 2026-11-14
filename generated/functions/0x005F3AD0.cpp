// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F3AD0 rf_ui_inputbox_accept_character
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): BYTE input. If reject-string1144 nonempty and contains byte,returns0. Else if allow-string888 nonempty and does NOT contain byte,returns0. Else if callback1456 nonNULL calls cdecl callback(textBuffer632,unsignedBYTE character),returns its raw AL;otherwise1. No insertion,length,width check;reject list takes precedence;no normalization of callback result.
char __thiscall rf_ui_inputbox_accept_character(int this, char a2)
{
  if ( this + 1144 + strlen((const char *)(this + 1144)) + 1 != this + 1145
    && rf_cstring_find_first_character((char *)(this + 1144), a2) )
  {
    return 0;
  }
  if ( this + 888 + strlen((const char *)(this + 888)) + 1 != this + 889
    && !rf_cstring_find_first_character((char *)(this + 888), a2) )
  {
    return 0;
  }
  if ( *(_DWORD *)(this + 1456) )
    return (*(char (__cdecl **)(int, _DWORD))(this + 1456))(this + 632, (unsigned __int8)a2);
  return 1;
}

