// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00485650 rf_level_text_load_for_level
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, geometry-operation phases, terrain/debris ownership, saved replay, native x87 gates and localized level-text lifecycle): 
// Cdecl source level pathname, returns AL0/1. Copies path without last extension into local512-byte buffer, scans terminator, appends literal '_text.tbl' includingNUL using native
// DWORD/DWORD/WORD copies. No local buffer-capacity check or directory/path canonicalization here. Constructs memory parser and opens derived path with directory0x98967F,flags0.
// Nonzero open result destroys parser and returns0 WITHOUT clearing existing slots/handles. Success clears slots via4855D0, then reads records until parser cursor atNUL; after each
// entry skips trivia/CR lines. No section header/end marker or row-count requirement. Destroys parser and returns1 on normal end, no sound unloading or all-row transaction rollback.
// Failure to find optional file is nonfatal in this wrapper.
char __cdecl rf_level_text_load_for_level(char *Str)
{
  char *v3; // [esp+Ch] [ebp-32Ch]
  char v4; // [esp+13h] [ebp-325h] BYREF
  char path[512]; // [esp+14h] [ebp-324h] BYREF
  void *self[69]; // [esp+214h] [ebp-124h] BYREF
  int v7; // [esp+334h] [ebp-4h]

  rf_path_copy_without_last_extension(path, Str);
  v3 = &v4;
  while ( *++v3 )
    ;
  strcpy(v3, "_text.tbl");
  rf_memory_text_parser_construct_empty(self);
  v7 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, path, byte_98967F, 0) )
  {
    v4 = 0;
    v7 = -1;
    rf_memory_text_parser_destroy_buffer_adapter(self);
    return v4;
  }
  else
  {
    rf_level_text_clear_slots();
    while ( !rf_text_parser_is_cursor_at_nul((char **)self) )
    {
      rf_level_text_parse_entry((const char **)self);
      rf_text_parser_skip_trivia_and_cr_lines(self);
    }
    v7 = -1;
    rf_memory_text_parser_destroy_buffer_adapter(self);
    return 1;
  }
}

