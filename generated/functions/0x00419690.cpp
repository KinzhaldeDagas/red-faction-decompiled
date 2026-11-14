// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00419690 rf_glare_definitions_load_effects_table
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Constructs temporary RFString and memory parser, opens effects.tbl; nonzero open status calls fatal error at glare.cpp line408. Finds/consumes #Glares, then consumes/tests #End BEFORE checking signed global count0x680AE0<64; each admitted iteration parses one52-byte definition and increments count afterward. Does not reset count or definition storage before loading, so repeated calls append until the retained count reaches64. Closes parser buffer and destroys parser/string temporaries, with EH cleanup. No recovery after malformed required tokens, bitmap rollback or per-record validation here.
void rf_glare_definitions_load_effects_table()
{
  _DWORD v0[2]; // [esp+4h] [ebp-12Ch] BYREF
  void *self[69]; // [esp+Ch] [ebp-124h] BYREF
  int v2; // [esp+12Ch] [ebp-4h]

  rf_string_construct_empty(v0);
  v2 = 0;
  rf_memory_text_parser_construct_empty(self);
  LOBYTE(v2) = 1;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "effects.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\effects\\glare.cpp",
      408,
      "Unable to open effects.tbl");
  if ( rf_text_parser_find_before_stop_and_consume_required((char **)self, "#Glares", nullptr) )
  {
    while ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#End") && dword_680AE0 < 64 )
    {
      rf_glare_definition_parse_into_current_slot((const char **)self);
      ++dword_680AE0;
    }
  }
  rf_memory_text_parser_close_buffer(self);
  LOBYTE(v2) = 0;
  rf_memory_text_parser_destroy_buffer_adapter(self);
  v2 = -1;
  rf_string_destroy_buffer(v0);
}

