// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578DE0 rf_text_parser_read_xstr_id_and_delimited_text
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus(destination,capacity,openingDelimiter,closingDelimiter),RET16. Requires case-insensitive literal XSTR(,parses integer579890,requires comma,reads literal text through57A050 using caller delimiter BYTES (not boolean flags),then requires right parenthesis. Returns parsed integer ID;does not translate/localize text or validate identifier. Trivia allowed before each component;XSTR and opening parenthesis must match one contiguous prefix. Integer hex-EOF and delimiter parser behavior inherited.
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: XSTR grammar when invoked: CURRENT contiguous CI XSTR( prefix, signedinteger, required comma, delimitedCString caller capacity256, required closing ). Weapon DisplayName uses this reader; plainquoted alternative is not native.
int __thiscall rf_text_parser_read_xstr_id_and_delimited_text(
        _DWORD *this,
        char *Destination,
        int a3,
        char a4,
        char a5)
{
  int signed_decimal_or_hex_integer; // [esp+4h] [ebp-4h]

  rf_text_parser_require_case_insensitive_prefix_or_fatal(this, "XSTR(");
  signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(this);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(this, ",");
  rf_text_parser_read_delimited_cstring((int)this, Destination, a3, a4, a5);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(this, ")");
  return signed_decimal_or_hex_integer;
}

