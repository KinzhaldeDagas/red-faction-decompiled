// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057A4C0 rf_text_parser_read_parenthesized_integer_list_with_name_callback
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric grammar and rounding, structured-value layouts, ignored list limits, callback/flag behavior and formatter cleanup): ECX parser, DWORD output array, unused capacity-like argument, cdecl callback(slotAddress,index,quotedName). Requires (, processes until )/EOF: unquoted item uses signed decimal/hex reader579890 and writes slot; quoted item uses256-capacity delimited reader (maximum255 bytes) and callback, with no automatic integer assignment. Tests only LOW BYTE of callback return. Null callback or zero low byte restores item bookmark and fatals; callback side effects are not rolled back. Increments index after each accepted item, skips trivia, requires/consumes ), returns count. Third argument unused, no capacity check; no comma syntax. Empty list valid. Quoted callback name buffer is transient stack storage.
int __thiscall rf_text_parser_read_parenthesized_integer_list_with_name_callback(
        void *self,
        int *out_values,
        int unused_limit,
        int (__cdecl *name_callback)(int *slot, int index, char *name))
{
  int signed_decimal_or_hex_integer; // eax
  char v7[260]; // [esp+4h] [ebp-118h] BYREF
  _DWORD v8[2]; // [esp+10Ch] [ebp-10h] BYREF
  char v9; // [esp+117h] [ebp-5h]
  int v10; // [esp+118h] [ebp-4h]

  rf_text_parser_skip_trivia_and_cr_lines(self);
  if ( **((_BYTE **)self + 1) != 40 )
    rf_text_parser_fatal_expected_with_context((char **)self, "an integer list");
  ++*((_DWORD *)self + 1);
  rf_text_parser_skip_trivia_and_cr_lines(self);
  v10 = 0;
  while ( **((_BYTE **)self + 1) && **((_BYTE **)self + 1) != 41 )
  {
    if ( **((_BYTE **)self + 1) == 34 )
    {
      rf_text_parser_save_cursor_bookmark(self, v8);
      rf_text_parser_read_delimited_cstring((int)self, v7, 256, 34, 34);
      v9 = 0;
      if ( name_callback )
        v9 = name_callback(&out_values[v10], v10, v7);
      if ( !v9 )
      {
        rf_text_parser_restore_cursor_bookmark(self, v8);
        rf_text_parser_fatal_expected_with_context((char **)self, "an integer list element");
      }
    }
    else
    {
      signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer((char **)self);
      out_values[v10] = signed_decimal_or_hex_integer;
    }
    ++v10;
    rf_text_parser_skip_trivia_and_cr_lines(self);
  }
  if ( **((_BYTE **)self + 1) != 41 )
    rf_text_parser_fatal_expected_with_context((char **)self, "an integer list terminator");
  ++*((_DWORD *)self + 1);
  return v10;
}

