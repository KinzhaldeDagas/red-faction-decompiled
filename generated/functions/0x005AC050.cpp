// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AC050 rf_ui_parse_hotkey_name
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Object ECX saved but unused; one stack argument is parser object and callee pops4. Repeated optional prefix matches Ctrl,Shift,Alt with required plus,then reads CR-delimited line into256-byte local and trims space/tab/LF into256-byte local with maximum255. Case-insensitive linear lookup in256-pointer key-name table0x664360; unmatched name yields index256 without error. Ctrl ORs0x4000. BUG: Alt branch0x5AC0FD sets SAME local as Shift,so either ORs0x1000; separate Alt local stays0 and0x2000 never set. Prefix matcher has no token-boundary check; line-read failure ignored and may leave local text uninitialized. Returns index OR modifier bits.
int __stdcall rf_ui_parse_hotkey_name(const char **parser)
{
  int i; // [esp+4h] [ebp-214h]
  char Destination[262]; // [esp+8h] [ebp-210h] BYREF
  char v4; // [esp+10Eh] [ebp-10Ah]
  char v5; // [esp+10Fh] [ebp-109h]
  char String1[256]; // [esp+110h] [ebp-108h] BYREF
  char v7; // [esp+217h] [ebp-1h]

  v4 = 0;
  v7 = 0;
  v5 = 0;
  while ( 1 )
  {
    while ( 1 )
    {
      while ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "Ctrl") )
      {
        v4 = 1;
        rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+");
      }
      if ( !rf_text_parser_try_consume_case_insensitive_prefix(parser, "Shift") )
        break;
      v7 = 1;
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+");
    }
    if ( !rf_text_parser_try_consume_case_insensitive_prefix(parser, (char *)off_643118) )
      break;
    v7 = 1;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+");
  }
  rf_text_parser_skip_trivia_and_cr_lines(parser);
  rf_text_parser_read_cr_line_cstring_if_fits((int)parser, Destination, 256);
  rf_cstring_trim_space_tab_lf_copy(String1, Destination);
  for ( i = 0; i < 256 && _stricmp(String1, (&off_664360)[i]); ++i )
    ;
  if ( v4 )
    i |= 0x4000u;
  if ( v7 )
    i |= 0x1000u;
  if ( v5 )
    return i | 0x2000;
  return i;
}

