// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EFAF0 rf_localization_load_strings_table
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, thermal renderer x87 branches, native stack aliases, localization pool writes and skin-profile selection): No arguments. Constructs memory text parser and opens strings.tbl with context98967F,flags0; nonzero open result enters repeated fatal-error call at localize.cpp line377 with Unable to open strings.tbl. Requires #Strings then parses multilingual entries until case-insensitive #End prefix is consumed. Sets loaded byte88E3E8=1, closes parser buffer and destroys parser; destructor also on SEH unwind. Does not reset loaded flag first, shared pool cursor, fallback count or indexed table. Incidental EAX is destroy-adapter result, not a load-status contract.
void **rf_localization_load_strings_table()
{
  void *self[69]; // [esp+4h] [ebp-124h] BYREF
  int v2; // [esp+124h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v2 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "strings.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\rf\\localize.cpp",
      377,
      "Unable to open strings.tbl");
  rf_text_parser_find_before_stop_and_consume_required((char **)self, "#Strings", nullptr);
  while ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#End") )
    rf_localization_parse_multilingual_string_entry(self);
  unk_88E3E8 = 1;
  rf_memory_text_parser_close_buffer(self);
  v2 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

