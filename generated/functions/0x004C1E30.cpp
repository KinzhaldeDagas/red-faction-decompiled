// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1E30 rf_explosion_definitions_load_table
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, managed emitter and voice ownership, original table parser, circular graph lifecycle, native unordered time gates and direct particle descriptor consumer): 
// Cdecl no args. Constructs stack owned-memory parser; global definitionCount814348=0 (does not clear definition row storage). Opens explosion.tbl using directory string98967F and
// flags0; NONZERO open return triggers fatal explosion.cpp:331, native retry loop if it returned. Requires #explosion types header. Repeatedly parse_next4C1AA0 until EAX==-1,
// incrementing global count after each success with no capacity check. Explicitly closes owned buffer then parser destruction adapter; exception cleanup also destroys parser. Does
// not reset explosion graph pool, validate optional references/unused stale fields, or create runtime particles. Return EAX parser-destructor artifact, not loaded count or durable
// parser ownership.
void **rf_explosion_definitions_load_table()
{
  void *self[69]; // [esp+4h] [ebp-124h] BYREF
  int v2; // [esp+124h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v2 = 0;
  unk_814348 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "explosion.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\particle\\explosion.cpp",
      331,
      "Unable to open explosion.tbl");
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#explosion types");
  while ( rf_explosion_definition_parse_next((_BYTE **)self) != -1 )
    ++unk_814348;
  rf_memory_text_parser_close_buffer(self);
  v2 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

