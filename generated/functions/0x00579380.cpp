// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00579380 rf_text_parser_read_cr_line_into_rfstring
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus RFString output,RET4. At EOF assigns empty C string6410DD and returns0. Otherwise scans to CR orNUL (LF is ordinary content),assigns exact span through RFString bounded assign,moves cursor past span. If atCR,consumes it,increments line264,then consumes one optionalLF. Returns1 for any non-EOF line including empty CR line. No comment/trivia skip,capacity parameter,stored-size guard or LF-only line splitting.
char __thiscall rf_text_parser_read_cr_line_into_rfstring(int this, _DWORD *a2)
{
  int i; // [esp+4h] [ebp-4h]

  if ( **(_BYTE **)(this + 4) )
  {
    for ( i = 0; *(_BYTE *)(*(_DWORD *)(this + 4) + i) && *(_BYTE *)(*(_DWORD *)(this + 4) + i) != 13; ++i )
      ;
    rf_string_assign_cstr_bounded((int)a2, *(char **)(this + 4), i);
    *(_DWORD *)(this + 4) += i;
    if ( **(_BYTE **)(this + 4) == 13 )
    {
      ++*(_DWORD *)(this + 264);
      if ( *(_BYTE *)++*(_DWORD *)(this + 4) == 10 )
        ++*(_DWORD *)(this + 4);
    }
    return 1;
  }
  else
  {
    rf_string_assign_from_cstr(a2, (char *)&byte_6410DD);
    return 0;
  }
}

