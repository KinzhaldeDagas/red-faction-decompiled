// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00507B00 rf_ammo_load_table_append_records
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Constructs owned memory parser, opens literal ammo.tbl with numeric context9999999 (98967F) and final0. Any nonzero open result enters fatal-error path (ammo.cpp line110, Unable to open ammo.tbl). Requires CURRENT case-insensitive #Ammo prefix, repeats507BF0(parser pointer) until CURRENT #End prefix, increments global911480 AFTER each row. No own count reset, row limit, name deduplication/filtering or EOF/trailing-section validation. Closes parser and destroys buffer normally; SEH also destroys parser. Return EAX is cleanup residue, not parse count/success.
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: Ordered raw byte registry: require CURRENT#Ammo; until CURRENT#End parse507BF0 then increment count. No EOF, row sorting, deduplication, empty-name/icon filtering or bitmap-load-success gate. Same native cursor/comment/prefix rules as weapons.tbl. Physical capacity is independently32*20 via62F4D0, not checked by this loader. Host greater-than32 must remain explicit unsafe unsupported domain, not native checked rejection.
void **rf_ammo_load_table_append_records()
{
  void *self[69]; // [esp+4h] [ebp-124h] BYREF
  int v2; // [esp+124h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v2 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "ammo.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\weapon\\ammo.cpp",
      110,
      "Unable to open ammo.tbl");
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#Ammo");
  while ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#End") )
  {
    rf_ammo_parse_record(self);
    ++unk_911480;
  }
  rf_memory_text_parser_close_buffer(self);
  v2 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

