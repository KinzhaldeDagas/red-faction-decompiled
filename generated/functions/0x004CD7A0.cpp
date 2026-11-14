// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CD7A0 rf_particle_emitter_definitions_load_table
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Cdecl stack-owned memory parser loads plural "emitters.tbl" with directory argument 0x98967F and flags0. Nonzero open result invokes fatal error particle_emitter.cpp:449; native
// code retries the fatal call indefinitely if it returns. Requires case-insensitive "#particle emitter types", then reads entries until case-insensitive "#end".
// For each row, allocates 132 bytes and invokes no-op definition constructor only if allocation is nonnull. Stores resulting pointer (including NULL) into 0x867800[count 0x867904]
// BEFORE requiring "$name:" and reading double-quoted RFString at 0x867A60+8*count; calls definition parser even on the NULL allocation path, then increments count. No reset of count
// here, no per-row capacity guard, no duplicate-name check, no all-row rollback. After end, zeros only pointer slots count..63; leaves unused name slots unchanged. Startup resets
// count before calling this loader. Normal parser destruction releases owned buffer; unwind also deletes the current raw allocation if construction throws. Return is destructor
// register artifact.
void **rf_particle_emitter_definitions_load_table()
{
  void *v1; // [esp+4h] [ebp-134h]
  void *v2; // [esp+8h] [ebp-130h]
  int i; // [esp+10h] [ebp-128h]
  void *self[69]; // [esp+14h] [ebp-124h] BYREF
  int v5; // [esp+134h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v5 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "emitters.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\particle\\particle_emitter.cpp",
      449,
      "Unable to open emitters.tbl");
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#particle emitter types");
  while ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#end") )
  {
    v2 = operator new(0x84u);
    LOBYTE(v5) = 1;
    if ( v2 )
      v1 = rf_particle_emitter_definition_construct_noop(v2);
    else
      v1 = nullptr;
    LOBYTE(v5) = 0;
    dword_867800[unk_867904] = (int)v1;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$name:");
    rf_text_parser_read_delimited_rfstring(self, (void *)(8 * unk_867904 + 8813152), 34, 34);
    rf_particle_emitter_definition_parse((int)self, dword_867800[unk_867904]);
    ++unk_867904;
  }
  for ( i = unk_867904; i < 64; ++i )
    dword_867800[i] = 0;
  v5 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

