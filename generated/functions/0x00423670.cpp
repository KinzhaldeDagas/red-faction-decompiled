// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00423670 rf_entity_load_entity_tbl_definitions
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): No args; constructs local memory-text parser with SEH cleanup.578EA0(ECX local parser,path entity.tbl,ADDRESS98967F context,raw0) must return
// EAX0; ANY nonzero enters fatal diagnostic loop entity.cpp line2496 Unable to open entity.tbl. Require case-insensitive prefix #Entity Classes via5797A0, ignoring bool return
// because delegate enforces fatal grammar. Repeatedly423760(&parser); ONLY EAX EXACT-1 ends loop, every other result increments shared DWORD681E14 with32-bit arithmetic. Does NOT
// reset count, enforce75-record limit, require a nonnegative parse index or free previous definitions in this wrapper. After terminal-1 call43C4F0, whose signed definition/record
// loops copy each existing class+3308 forty-byte record FLOAT+8 to active FLOAT+4. Explicitly close parser buffer579190, mark cleanup state-1, then destructor578830 closes again;
// close clears buffer, so normal second close seesNULL. Native SEH tail622AE5 destroys parser backing on unwind after construction; it does not roll back partial global
// definitions/count. No caller-visible validated success/count returned: final register bits derive from local parser destructor and security epilogue, with decompiler inferring
// pointer to expired local parser. Open/read/parser helpers retain their native ownership/read-status behavior; EAX0 from open does not establish complete file read.
void **rf_entity_load_entity_tbl_definitions()
{
  void *self[69]; // [esp+4h] [ebp-124h] BYREF
  int v2; // [esp+124h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v2 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "entity.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\entity\\entity.cpp",
      2496,
      "Unable to open entity.tbl");
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#Entity Classes");
  while ( rf_entity_info_parse_definition((int)self) != -1 )
    ++unk_681E14;
  sub_43C4F0();
  rf_memory_text_parser_close_buffer(self);
  v2 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

