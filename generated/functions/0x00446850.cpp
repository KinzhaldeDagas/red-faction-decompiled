// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446850 rf_gamesound_load_table
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Constructs a local memory-text parser and opens sounds.tbl with namespace/string98967F and flag0. Any nonzero
// full-EAX open result destroys the parser and returns without parsing. On success requires case-insensitive '#Sounds Start', then repeatedly tries to consume '#Sounds End' BEFORE
// checking signed ordinal<2048. A nonzero end-prefix AL or ordinal>=2048 stops; the capacity exit does not require an end marker. Each accepted iteration calls446960(parser,ordinal),
// ignores its ordinary return, and increments ordinal from0; the delegate registers a row and fatally rejects a registered ID unequal to that ordinal. Normal completion explicitly
// closes then destroys the parser; open failure destroys it, which also closes. No rollback of already registered rows. Return bits are the parser-destroy adapter's pointer to this
// now-dead stack object, not an owned parser or success code. The second chunk implements state0 parser destruction on C++ unwind and the cookie/frame handler; no heap parser
// receiver is allocated.
void **rf_gamesound_load_table()
{
  int v1; // [esp+4h] [ebp-128h]
  void *self[69]; // [esp+8h] [ebp-124h] BYREF
  int v3; // [esp+128h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v3 = 0;
  v1 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "sounds.tbl", byte_98967F, 0) )
  {
    v3 = -1;
    return rf_memory_text_parser_destroy_buffer_adapter(self);
  }
  else
  {
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#Sounds Start");
    while ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#Sounds End") && v1 < 2048 )
      rf_gamesound_parse_table_entry(self, v1++);
    rf_memory_text_parser_close_buffer(self);
    v3 = -1;
    return rf_memory_text_parser_destroy_buffer_adapter(self);
  }
}

