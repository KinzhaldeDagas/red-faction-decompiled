// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EF870 rf_localization_parse_multilingual_string_entry
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, thermal renderer x87 branches, native stack aliases, localization pool writes and skin-profile selection): Cdecl parser pointer. Requires # prefix, reads signed decimal/hex ID, then requires En:, Gr:, Fr: in that order and reads each double-quoted string into same1024-byte stack buffer. Language global88E3DC exactly0/1/2 selects English/German/French for escaped-pool storage with that ID; other values still parse all three and store none. Always consumes all three entries, even after selected storage returnsNULL; no own ID-range/duplicate checks. EAX is last parse/storage result, not aggregate success.
_BYTE *__cdecl rf_localization_parse_multilingual_string_entry(_DWORD *parser)
{
  _BYTE *result; // eax
  char Destination[1024]; // [esp+0h] [ebp-408h] BYREF
  int signed_decimal_or_hex_integer; // [esp+404h] [ebp-4h]

  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "#");
  signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "En:");
  rf_text_parser_read_delimited_cstring((int)parser, Destination, 1024, 34, 34);
  if ( !unk_88E3DC )
    rf_localization_store_escaped_string(Destination, signed_decimal_or_hex_integer);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "Gr:");
  rf_text_parser_read_delimited_cstring((int)parser, Destination, 1024, 34, 34);
  if ( unk_88E3DC == 1 )
    rf_localization_store_escaped_string(Destination, signed_decimal_or_hex_integer);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "Fr:");
  result = (_BYTE *)rf_text_parser_read_delimited_cstring((int)parser, Destination, 1024, 34, 34);
  if ( unk_88E3DC == 2 )
    return rf_localization_store_escaped_string(Destination, signed_decimal_or_hex_integer);
  return result;
}

