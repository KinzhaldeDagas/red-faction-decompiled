// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057A8C0 rf_text_parser_read_quoted_enum_index
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): ECX parser, name-pointer table, signed entry count (RET8). Skips full trivia, saves cursor/line bookmark, reads one quoted string with capacity256 (maximum255 body bytes), scans names with case-insensitive strcmp and returns first matching index. Reaching count OR encountering a NULL name restores bookmark and fatals expected a valid type string. Unlike named-flag reader57A720, early NULL does not silently accept unknown names. No output mask, comma or parentheses syntax; no table/buffer ownership checks.
int __thiscall rf_text_parser_read_quoted_enum_index(void *self, const char *const *names, int name_count)
{
  char String1[256]; // [esp+4h] [ebp-110h] BYREF
  _DWORD v6[2]; // [esp+108h] [ebp-Ch] BYREF
  int i; // [esp+110h] [ebp-4h]

  rf_text_parser_skip_trivia_and_cr_lines(self);
  rf_text_parser_save_cursor_bookmark(self, v6);
  rf_text_parser_read_delimited_cstring((int)self, String1, 256, 34, 34);
  for ( i = 0; ; ++i )
  {
    if ( i >= name_count || !names[i] )
    {
      rf_text_parser_restore_cursor_bookmark(self, v6);
      rf_text_parser_fatal_expected_with_context((char **)self, "a valid type string");
    }
    if ( !_stricmp(String1, names[i]) )
      break;
  }
  return i;
}

