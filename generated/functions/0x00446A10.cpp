// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446A10 rf_foley_load_table_append_sets
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Constructs a local memory-text parser, opens foley.tbl with string98967F and flag0, and on any nonzero full-EAX
// failure repeatedly calls fatal5708E0(gamesound.cpp,425,'Unable to open foley.tbl') if that nonreturning delegate were to return. Success requires '#Entity Sounds', then repeatedly
// calls446AF0(parser). Exactly EAX==-1 ends the loop; every other return increments the LIVE DWORD6EDC30 with wrapping32-bit arithmetic, without resetting that global or imposing a
// capacity limit here. Thus parsing appends at the existing count; the helper owns per-row parsing/allocation/registration. Normal end closes then destroys the parser; C++ unwind
// destroys it through the second chunk. No release/rollback of prior rows and no requirement for a section-end marker in this caller. Final ordinary EAX is the destroy adapter's
// pointer to a dead local parser, not a reliable status or an owned result.
void **rf_foley_load_table_append_sets()
{
  void *self[69]; // [esp+4h] [ebp-124h] BYREF
  int v2; // [esp+124h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v2 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "foley.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\gamewide\\gamesound.cpp",
      425,
      "Unable to open foley.tbl");
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#Entity Sounds");
  while ( rf_foley_parse_sound_set((int)self) != -1 )
    ++unk_6EDC30;
  rf_memory_text_parser_close_buffer(self);
  v2 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

