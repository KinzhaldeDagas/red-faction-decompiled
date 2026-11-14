// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057A720 rf_text_parser_read_parenthesized_named_flag_mask
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric grammar and rounding, structured-value layouts, ignored list limits, callback/flag behavior and formatter cleanup): ECX parser, table of name pointers and signed count. Requires (, reads quoted names (maximum255 bytes), scans table with case-insensitive strcmp and ORs1<<matchedIndex into32-bit mask. Stops scan on NULL entry or index>=count, but errors ONLY for index>=count: early NULL silently ignores unmatched input names. Raw SHL edx,cl masks index modulo32, so matches32+ alias earlier bits. Duplicate inputs are idempotent and duplicate table names use first match. Missing name at count restores item bookmark then fatals; missing closing ) fatals. Full trivia between entries; no commas. Returns mask in EAX; no explicit32-name limit.
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: Flag reader requires parenthesized quoted names with trivia separators (no commas), CString256 capacity (max255byte payload), exact wholeCI lookup then OR bit. Duplicates idempotent, unknown flag fatal. Weapon-specific tables663A40[23],663A9C[11] dense and all pointers/rawstrings verified from original executable.
int __thiscall rf_text_parser_read_parenthesized_named_flag_mask(char **this, int a2, int a3)
{
  char String1[260]; // [esp+4h] [ebp-118h] BYREF
  _DWORD v6[2]; // [esp+10Ch] [ebp-10h] BYREF
  int i; // [esp+114h] [ebp-8h]
  int v8; // [esp+118h] [ebp-4h]

  v8 = 0;
  rf_text_parser_skip_trivia_and_cr_lines(this);
  if ( **(this + 1) != 40 )
    rf_text_parser_fatal_expected_with_context(this, "a flags list");
  ++*(this + 1);
  rf_text_parser_skip_trivia_and_cr_lines(this);
  while ( **(this + 1) && **(this + 1) != 41 )
  {
    rf_text_parser_save_cursor_bookmark(this, v6);
    rf_text_parser_read_delimited_cstring((int)this, String1, 256, 34, 34);
    for ( i = 0; i < a3 && *(_DWORD *)(a2 + 4 * i); ++i )
    {
      if ( !_stricmp(String1, *(const char **)(a2 + 4 * i)) )
      {
        v8 |= 1 << i;
        break;
      }
    }
    if ( i >= a3 )
    {
      rf_text_parser_restore_cursor_bookmark(this, v6);
      rf_text_parser_fatal_expected_with_context(this, "a valid flag name");
    }
    rf_text_parser_skip_trivia_and_cr_lines(this);
  }
  if ( **(this + 1) != 41 )
    rf_text_parser_fatal_expected_with_context(this, "a flags list terminator");
  ++*(this + 1);
  return v8;
}

