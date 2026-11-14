// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057A330 rf_text_parser_read_multiline_rfstring_flatten_cr_lf
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric grammar and rounding, structured-value layouts, ignored list limits, callback/flag behavior and formatter cleanup): Calls57A1C0 multiline reader, inheriting terminator search, trimming and error behavior. Compacts returned RFString in place: each CR becomes one space, each LF is removed, all other bytes retained; CRLF therefore becomes one space. Writes NUL at compacted length, returns pointer to that NUL, not receiver or string object. Does not reallocate or adjust stored buffer capacity.
char *__thiscall rf_text_parser_read_multiline_rfstring_flatten_cr_lf(
        void *self,
        void *out_string,
        const char *terminator)
{
  char *result; // eax
  int v4; // [esp+Ch] [ebp-10h]
  char v5; // [esp+13h] [ebp-9h]
  signed int v6; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  rf_text_parser_read_multiline_rfstring_until_substring((char **)self, (int)out_string, (char *)terminator);
  v6 = rf_string_length_from_cstr((const char **)out_string);
  v4 = 0;
  for ( i = 0; i < v6; ++i )
  {
    v5 = *rf_string_byte_pointer_or_zero_sentinel((int *)out_string, i);
    if ( v5 == 13 )
    {
      *rf_string_byte_pointer_or_zero_sentinel((int *)out_string, v4++) = 32;
    }
    else if ( v5 != 10 )
    {
      *rf_string_byte_pointer_or_zero_sentinel((int *)out_string, v4++) = v5;
    }
  }
  result = rf_string_byte_pointer_or_zero_sentinel((int *)out_string, v4);
  *result = 0;
  return result;
}

