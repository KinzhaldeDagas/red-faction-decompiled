// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00413CF0 rf_clutter_registry_load_table
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): Noargs. Constructs local memory-text parser,opens clutter.tbl with parser flag byte98967F and mode0;NONZERO open result triggers fatal Unable to open clutter.tbl (native source clutter.cpp line953). Requires #Clutter prefix;repeatedly parses nextclass413DD0 and increments globalcount666B60 after every return!=integer-1. Parser returns0 forsuccess/-1 forend. Does not reset count itself,cap450,clear existing slots or roll back partially parsed records. Closes buffer and destroys parser on normal completion;exit/fatal/SEH follow delegate behavior.
void **rf_clutter_registry_load_table()
{
  void *self[69]; // [esp+4h] [ebp-124h] BYREF
  int v2; // [esp+124h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v2 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "clutter.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\clutter\\clutter.cpp",
      953,
      "Unable to open clutter.tbl");
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#Clutter");
  while ( rf_clutter_class_parse_next_into_registry((int)self) != -1 )
    ++unk_666B60;
  rf_memory_text_parser_close_buffer(self);
  v2 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

