// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004857A0 rf_level_text_parse_entry
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, geometry-operation phases, terrain/debris ownership, saved replay, native x87 gates and localized level-text lifecycle): 
// Cdecl parser pointer. Reads signed decimal/hex index; native signed0<=index<64 required, otherwise fatal level_text.cpp:159 with repeated fatal-call loop if it returns. Constructs
// temporary RFString for quoted sound filename. Length>4 ->sound_resource_load(filename,distance7.0,volume binary320.8999999761581421,scale1), stores returned handle
// at0x6FF890+12*index even if failed; length<=4 ->-1. Does not release previous sound on duplicate index.
// If case-insensitive 'En:' token present, samples language ONCE, reads quoted English into slot RFString for language0 or discards into local C buffer with max1024; then requires
// 'Gr:' and stores only language1, then requires 'Fr:' and stores only language2. All three strings are consumed in that fixed order. Other language values discard all three and
// leave existing slot text unchanged; no fallback to English. If En: absent, reads one quoted RFString directly into slot independent of language. Sound filename is shared across
// languages. Temporary filename destroyed on exit/unwind; duplicate entries overwrite selected text/handle without resetting other slots.
void __cdecl rf_level_text_parse_entry(const char **parser)
{
  const char *v1; // eax
  int v2; // eax
  char Destination[1028]; // [esp+10h] [ebp-424h] BYREF
  int language; // [esp+418h] [ebp-1Ch]
  const char *destination[2]; // [esp+41Ch] [ebp-18h] BYREF
  unsigned int signed_decimal_or_hex_integer; // [esp+424h] [ebp-10h]
  int v7; // [esp+430h] [ebp-4h]

  signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
  if ( signed_decimal_or_hex_integer >= 0x40 )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\level\\level_text.cpp",
      159,
      "Invalid index in level text tbl");
  rf_string_construct_empty(destination);
  v7 = 0;
  rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
  if ( (int)rf_string_length_from_cstr(destination) <= 4 )
  {
    unk_6FF890[3 * signed_decimal_or_hex_integer] = -1;
  }
  else
  {
    v1 = rf_string_object_c_str_or_empty(destination);
    v2 = rf_sound_resource_load(v1, 7.0, 0.89999998, 1.0);
    unk_6FF890[3 * signed_decimal_or_hex_integer] = v2;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "En:") )
  {
    language = rf_localization_get_language();
    if ( language )
      rf_text_parser_read_delimited_cstring((int)parser, Destination, 1024, 34, 34);
    else
      rf_text_parser_read_delimited_rfstring(parser, &byte_6FF888[12 * signed_decimal_or_hex_integer], 34, 34);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "Gr:");
    if ( language == 1 )
      rf_text_parser_read_delimited_rfstring(parser, &byte_6FF888[12 * signed_decimal_or_hex_integer], 34, 34);
    else
      rf_text_parser_read_delimited_cstring((int)parser, Destination, 1024, 34, 34);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "Fr:");
    if ( language == 2 )
      rf_text_parser_read_delimited_rfstring(parser, &byte_6FF888[12 * signed_decimal_or_hex_integer], 34, 34);
    else
      rf_text_parser_read_delimited_cstring((int)parser, Destination, 1024, 34, 34);
  }
  else
  {
    rf_text_parser_read_delimited_rfstring(parser, &byte_6FF888[12 * signed_decimal_or_hex_integer], 34, 34);
  }
  v7 = -1;
  rf_string_destroy_buffer(destination);
}

