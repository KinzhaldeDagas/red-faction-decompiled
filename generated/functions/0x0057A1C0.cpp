// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057A1C0 rf_text_parser_read_multiline_rfstring_until_substring
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric grammar and rounding, structured-value layouts, ignored list limits, callback/flag behavior and formatter cleanup): ECX parser, RFString output and raw case-sensitive terminator substring. Skips leading trivia; saves 8-byte bookmark containing line and source cursor. Decompiler Source local is bookmark second DWORD, not uninitialized data. Searches raw substring578BF0 with null stop; missing terminator restores bookmark then constructs diagnostic via unbounded sprintf into256 bytes and fatals. Trims trailing space or bytes9..13 from span, WITHOUT lower-bound check: starts at match-1 even for empty span, can read before span and decrement length below zero. Assigns bounded source span then advances cursor by terminator strlen, returning updated cursor. Search counts crossed CR; consumed terminator bytes are not
// separately counted here. No quote/comment filtering within raw search.
char *__thiscall rf_text_parser_read_multiline_rfstring_until_substring(char **this, int a2, char *SubStr)
{
  char *result; // eax
  int v5; // [esp+14h] [ebp-114h] BYREF
  char *Source; // [esp+18h] [ebp-110h]
  int v7; // [esp+1Ch] [ebp-10Ch]
  char Buffer[256]; // [esp+20h] [ebp-108h] BYREF
  char *v9; // [esp+124h] [ebp-4h]

  rf_text_parser_skip_trivia_and_cr_lines(this);
  rf_text_parser_save_cursor_bookmark(this, &v5);
  if ( !rf_text_parser_find_substring_before_optional_stop(this, SubStr, nullptr) )
  {
    rf_text_parser_restore_cursor_bookmark(this, &v5);
    sprintf(Buffer, "multiline terminator \"%s\"", SubStr);
    rf_text_parser_fatal_expected_with_context(this, Buffer);
  }
  v7 = *(this + 1) - Source;
  v9 = *(this + 1) - 1;
  while ( *v9 == 32 || *v9 >= 9 && *v9 <= 13 )
  {
    --v9;
    --v7;
  }
  rf_string_assign_cstr_bounded(a2, Source, v7);
  result = &(*(this + 1))[strlen(SubStr)];
  *(this + 1) = result;
  return result;
}

