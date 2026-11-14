// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044CBF0 rf_hud_personas_load_table
// UNREALRED VERIFIED [persona-lifecycle-20260923]: HUD initializer loads hud_personas.tbl, parsing #Personas, $Name:, optional $Display Name:, $Image: and #End. Records have stride 0x128: name string +0, image string +8, display-name string +0x10, bitmap handle +0x18. Initializes ten name/image slots and bitmap handles (-1). Literal loader edge: increments count before comparing >=10, then breaks before parsing that slot; do not describe this as ten successfully parsed records. Registers string-clearing routine through atexit.
void **rf_hud_personas_load_table()
{
  int i; // [esp+4h] [ebp-12Ch]
  char *destination; // [esp+8h] [ebp-128h]
  void *self[69]; // [esp+Ch] [ebp-124h] BYREF
  int v4; // [esp+12Ch] [ebp-4h]

  atexit(rf_hud_personas_clear_strings);
  for ( i = 0; i < 10; ++i )
  {
    rf_string_assign_from_cstr(&rf_hud_persona_records[296 * i], (char *)&byte_63448F);
    rf_string_assign_from_cstr((_DWORD *)&unk_6EF1A8 + 74 * i, (char *)&byte_634490);
    unk_6EF1B8[74 * i] = -1;
  }
  rf_memory_text_parser_construct_empty(self);
  v4 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "hud_personas.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\hud\\hud_personas.cpp",
      328,
      "Unable to open hud_personas.tbl");
  rf_hud_persona_count = 0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#Personas");
  while ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#End") )
  {
    destination = &rf_hud_persona_records[296 * rf_hud_persona_count++];
    if ( rf_hud_persona_count >= 10 )
      break;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Name:");
    rf_text_parser_read_delimited_rfstring(self, destination, 34, 34);
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "$Display Name:") )
      rf_text_parser_read_delimited_rfstring(self, destination + 16, 34, 34);
    else
      rf_string_assign_from_cstr((_DWORD *)destination + 4, (char *)byte_634491);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Image:");
    rf_text_parser_read_delimited_rfstring(self, destination + 8, 34, 34);
  }
  rf_memory_text_parser_close_buffer(self);
  v4 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

