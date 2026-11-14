// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F33E0 rf_savegame_parse_ponr_table
// UNREALRED VERIFIED [save-validation-20261028]: Parses ponr.tbl: #Red Faction PONR, repeated $Level:, $Levels to save:, and +Save: entries, ending #End. Stores records at 0x890508 with stride164: name[32], count at+32, saved names at+36 stride32; record count at0x890500. Missing table enters fatal-error path. This body does not cap record count or per-record level count; returns1 after parsing.
char rf_savegame_parse_ponr_table()
{
  char *Destination; // [esp+8h] [ebp-130h]
  int i; // [esp+Ch] [ebp-12Ch]
  int v3; // [esp+10h] [ebp-128h]
  void *self[69]; // [esp+14h] [ebp-124h] BYREF
  int v5; // [esp+134h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v5 = 0;
  v3 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "ponr.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\save_restore\\save_restore.cpp",
      486,
      "Unable to open ponr.tbl");
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#Red Faction PONR");
  while ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#End") )
  {
    Destination = (char *)&unk_890508 + 164 * v3++;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Level:");
    rf_text_parser_read_delimited_cstring((int)self, Destination, 32, 34, 34);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Levels to save:");
    *((_DWORD *)Destination + 8) = rf_text_parser_read_signed_decimal_or_hex_integer(self);
    for ( i = 0; i < *((_DWORD *)Destination + 8); ++i )
    {
      rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "+Save:");
      rf_text_parser_read_delimited_cstring((int)self, &Destination[32 * i + 36], 32, 34, 34);
    }
  }
  unk_890500 = v3;
  v5 = -1;
  rf_memory_text_parser_destroy_buffer_adapter(self);
  return 1;
}

