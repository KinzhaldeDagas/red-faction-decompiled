// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00506A10 rf_vclip_load_table_records
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VClip initialization/preloads,byte occupancy and physical array sizes,trigger suppression/member cleanup and constructor ABI,original ECX/stack flow and PE bytes): Constructs owned memory parser, opens exact vclip.tbl with numeric context9999999 (98967F) and final0. Any nonzero open result enters repeated fatal path (vclip.cpp line557, Unable to open vclip.tbl). Requires CURRENT case-insensitive #Vclips prefix; until CURRENT #End, passes parser pointer to506AF0 (callee increments definition count before required row tokens). No own count reset/increment, capacity guard, name deduplication or EOF/trailing-section validation. Closes parser then destroys owned buffer; SEH destroys parser too. EAX is cleanup residue, not a reliable parser object/count/success result.
void **rf_vclip_load_table_records()
{
  void *self[69]; // [esp+4h] [ebp-124h] BYREF
  int v2; // [esp+124h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v2 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "vclip.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\vclip\\vclip.cpp",
      557,
      "Unable to open vclip.tbl");
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#Vclips");
  while ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#End") )
    sub_506AF0((_BYTE **)self);
  rf_memory_text_parser_close_buffer(self);
  v2 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

