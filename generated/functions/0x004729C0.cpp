// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004729C0 rf_item_definitions_load_table
// UNREALRED VERIFIED [event-item-dispatch-20261028]: Opens items.tbl or invokes fatal error item.cpp line563, expects #Items, repeatedly calls rf_item_definition_parse and increments count0x6F9124 until #End. Selects single-player counts through0x474670 then closes/destroys parser. This wrapper has no explicit96-entry cap; parsing function indexes current count.
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Raw items.tbl grammar is ordered #Items, repeated472AC0 then count++, until #End; then474670 copies SP counts to active. No EOF requirement, deduplication, empty-name filter, or native checked96cap. Physical96 is proven independently62EED0 and472880. Unsafe97th record write is an explicit unsupported host storage domain, not fabricated native validation.
void **rf_item_definitions_load_table()
{
  void *self[69]; // [esp+4h] [ebp-124h] BYREF
  int v2; // [esp+124h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v2 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "items.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\item\\item.cpp",
      563,
      "Unable to open items.tbl");
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#Items");
  while ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#End") )
  {
    rf_item_definition_parse((int)self);
    ++unk_6F9124;
  }
  rf_item_definitions_select_singleplayer_counts();
  rf_memory_text_parser_close_buffer(self);
  v2 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

