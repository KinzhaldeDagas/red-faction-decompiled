// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056D740 rf_console_execute_command_line
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): cdecl one const-char* stack argument; EBX/EDI/ESI are NOT parameters. Requires nonNULL strlen1..254,else-1. Copies to260B stack buffer,clears trace180A488,sets global lexer pointers and context-save buffer180A3C0 via60B154(buffer,0). Nonlocal parser error returns-1. Reads first token with mask-1. Compares debug keyword but discards comparison result: no debug-prefix enable here. Prefix ? selects mode1;help/man select mode2;prefix followed by end token lists documented commands and returns0. Requires token string bit2,then first case-insensitive registry name match;unknown/invalid prints diagnostic and returns-1. Callback mode
// tuples(execute1809818,help1809814,flag1809AB8):normal(1,0,1),?(0,0,1),help/man(0,1,0). Calls record+8 with NO args. Normal mode reads one more token;non-end tail prints unused-tail warning but still returns0. Help/query skip tail check. Global lexer/context/mode state is not saved/restored;lexer pointers refer to local buffer after return,so not reentrant or persistent input storage.
int __cdecl rf_console_execute_command_line(const char *command_line)
{
  char v2; // [esp+Bh] [ebp-13Dh]
  _BYTE *v3; // [esp+10h] [ebp-138h]
  const char *v4; // [esp+14h] [ebp-134h]
  int v5; // [esp+38h] [ebp-110h]
  int i; // [esp+3Ch] [ebp-10Ch]
  _BYTE v7[260]; // [esp+40h] [ebp-108h] BYREF

  if ( !strlen(command_line) || strlen(command_line) >= 0xFF )
    return -1;
  v4 = command_line;
  v3 = v7;
  do
  {
    v2 = *v4;
    *v3++ = *v4++;
  }
  while ( v2 );
  unk_180A488 = 0;
  unk_1809810 = v7;
  rf_console_lexer_set_input_and_prime(v7);
  if ( _setjmp3(Buf, 0) )
    return -1;
  v5 = 0;
  rf_console_read_argument_validate_type_mask(-1, 0);
  _stricmp(&MEMORY[0x1809820], "debug");
  if ( !_stricmp(&MEMORY[0x1809820], "?")
    && (v5 = 1, rf_console_read_argument_validate_type_mask(-1, 0), (dword_1809308 & 1) != 0)
    || (!_stricmp(&MEMORY[0x1809820], "help") || !_stricmp(&MEMORY[0x1809820], off_640A3C))
    && (v5 = 2, rf_console_read_argument_validate_type_mask(-1, 0), (dword_1809308 & 1) != 0) )
  {
    rf_console_print_registered_help_list();
    return 0;
  }
  else if ( (dword_1809308 & 2) != 0 )
  {
    if ( unk_180A488 )
    {
      sprintf(&unk_18CD828, "Searching for command '%s'\n", &MEMORY[0x1809820]);
      rf_console_output_append_text_lines(&unk_18CD828, nullptr);
    }
    for ( i = 0; ; ++i )
    {
      if ( i >= dword_180A480 )
      {
        sprintf(&unk_18CD828, unk_88E288, &MEMORY[0x1809820]);
        rf_console_output_append_text_lines(&unk_18CD828, nullptr);
        return -1;
      }
      if ( !_stricmp(&MEMORY[0x1809820], *(const char **)dword_180A408[i]) )
        break;
    }
    if ( v5 )
    {
      if ( v5 == 1 )
      {
        if ( unk_180A488 )
        {
          sprintf(&unk_18CD828, "Checking status for '%s'\n", &MEMORY[0x1809820]);
          rf_console_output_append_text_lines(&unk_18CD828, nullptr);
        }
        dword_1809818 = 0;
        dword_1809814 = 0;
        unk_1809AB8 = 1;
      }
      else
      {
        if ( unk_180A488 )
        {
          sprintf(&unk_18CD828, "Doing help for '%s'\n", &MEMORY[0x1809820]);
          rf_console_output_append_text_lines(&unk_18CD828, nullptr);
        }
        dword_1809818 = 0;
        dword_1809814 = 1;
        unk_1809AB8 = 0;
      }
    }
    else
    {
      if ( unk_180A488 )
      {
        sprintf(&unk_18CD828, "Calling function '%s'\n", &MEMORY[0x1809820]);
        rf_console_output_append_text_lines(&unk_18CD828, nullptr);
      }
      dword_1809818 = 1;
      dword_1809814 = 0;
      unk_1809AB8 = 1;
    }
    (*(void (**)(void))(dword_180A408[i] + 8))();
    if ( !v5 )
    {
      rf_console_read_argument_validate_type_mask(-1, 0);
      if ( (dword_1809308 & 1) == 0 )
      {
        sprintf(&unk_18CD828, "Ignoring the unused command line tail '%s %s'\n", unk_1809310, (const char *)unk_1809810);
        rf_console_output_append_text_lines(&unk_18CD828, nullptr);
      }
    }
    return 0;
  }
  else
  {
    sprintf(&unk_18CD828, unk_88E284, &MEMORY[0x1809820]);
    rf_console_output_append_text_lines(&unk_18CD828, nullptr);
    return -1;
  }
}

