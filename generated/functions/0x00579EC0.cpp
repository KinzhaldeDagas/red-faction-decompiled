// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00579EC0 rf_text_parser_read_braced_rgba_bytes
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric grammar and rounding, structured-value layouts, ignored list limits, callback/flag behavior and formatter cleanup): ECX parser and four-byte color destination. Requires { signedInteger , signedInteger , signedInteger, optionally comma plus fourth signedInteger, then }. RGB values and optional alpha truncate to low8 bits without clamping; omitted alpha is0. Calls color4 setter BEFORE validating closing brace, so malformed terminator can leave color changed. Consumes } and returns updated cursor in EAX, not receiver or boolean. Full trivia and inherited signed decimal/hex semantics apply.
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: RGBA reader requires { int , int , int then optional , int then }; RGB commas mandatory. Values narrow low8bits, omittedalpha0. No clamp. Native writes before final closing validation; host cache must not publish partial fields on failure.
int __thiscall rf_text_parser_read_braced_rgba_bytes(int this, _BYTE *a2)
{
  int result; // eax
  char signed_decimal_or_hex_integer; // [esp+4h] [ebp-10h]
  char v5; // [esp+8h] [ebp-Ch]
  char v6; // [esp+Ch] [ebp-8h]
  char v7; // [esp+10h] [ebp-4h]

  v7 = 0;
  rf_text_parser_skip_trivia_and_cr_lines((_DWORD *)this);
  if ( **(_BYTE **)(this + 4) != 123 )
    rf_text_parser_fatal_expected_with_context((char **)this, "a color");
  ++*(_DWORD *)(this + 4);
  signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer((char **)this);
  rf_text_parser_require_case_insensitive_prefix_or_fatal((void *)this, ",");
  v5 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)this);
  rf_text_parser_require_case_insensitive_prefix_or_fatal((void *)this, ",");
  v6 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)this);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)this, ",") )
    v7 = rf_text_parser_read_signed_decimal_or_hex_integer((char **)this);
  rf_color4_set_bytes_return_destination(a2, signed_decimal_or_hex_integer, v5, v6, v7);
  rf_text_parser_skip_trivia_and_cr_lines((_DWORD *)this);
  if ( **(_BYTE **)(this + 4) != 125 )
    rf_text_parser_fatal_expected_with_context((char **)this, "a color terminator");
  result = *(_DWORD *)(this + 4) + 1;
  *(_DWORD *)(this + 4) = result;
  return result;
}

