// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005705C0 rf_console_execute_script_file
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): cdecl one source filename pointer,NOT incoming EBX/ESI parameters. Constructs local file-reader object,copies at most1023 bytes to1024B filename buffer WITHOUT forcing finalNUL,finds FIRST dot anywhere in resulting path and truncates there,then appends .txt with unchecked strcpy. No dot-aware directory handling or room reserved for extension;long input can scan/write beyond buffer. Opens via578EA0 and prints executing message on success;reads256B line buffers through579580,trim space/tab/LF in place,skips empty lines,executes each via56D740. Stops at first nonzero command result,prints1-based physical line number and line;blank lines still increment counter. Closes/destroys reader on
// normal/command-error exits;open failure destroys without execute message. Shared console lexer/context is overwritten by nested calls and not restored. Returns incidental destructor pointer value,not reliable script success code.
void **__cdecl rf_console_execute_script_file(const char *source)
{
  char *v3; // [esp+1Ch] [ebp-62Ch]
  char *first_character; // [esp+20h] [ebp-628h]
  char command_line; // [esp+24h] [ebp-624h] BYREF
  _BYTE v6[3]; // [esp+25h] [ebp-623h] BYREF
  char v7; // [esp+123h] [ebp-525h] BYREF
  char Destination[1024]; // [esp+124h] [ebp-524h] BYREF
  void *self[68]; // [esp+524h] [ebp-124h] BYREF
  int v10; // [esp+638h] [ebp-10h]
  int v11; // [esp+644h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v11 = 0;
  strncpy(Destination, source, 0x3FFu);
  first_character = rf_cstring_find_first_character(Destination, 46);
  if ( first_character )
    *first_character = 0;
  v3 = &v7;
  while ( *++v3 )
    ;
  strcpy(v3, ".txt");
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, Destination, byte_98967F, 0) )
  {
    v11 = -1;
    return rf_memory_text_parser_destroy_buffer_adapter(self);
  }
  else
  {
    sprintf(&unk_18CD828, "Executing script file '%s'...\n", Destination);
    rf_console_output_append_text_lines(&unk_18CD828, nullptr);
    v10 = 1;
    while ( rf_text_parser_skip_trivia_then_read_cstring_line(self, &command_line, 256) )
    {
      rf_cstring_trim_space_tab_lf_copy(&command_line, &command_line);
      if ( &v6[strlen(&command_line)] != v6 && rf_console_execute_command_line(&command_line) )
      {
        sprintf(&unk_18CD828, "Error processing script line %d: '%s'\n", v10, &command_line);
        rf_console_output_append_text_lines(&unk_18CD828, nullptr);
        rf_memory_text_parser_close_buffer(self);
        v11 = -1;
        return rf_memory_text_parser_destroy_buffer_adapter(self);
      }
      ++v10;
    }
    rf_memory_text_parser_close_buffer(self);
    v11 = -1;
    return rf_memory_text_parser_destroy_buffer_adapter(self);
  }
}

