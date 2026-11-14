// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00570540 rf_console_script_command_callback
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args. If execute1809818 nonzero,reads required string token(mask2,preserveCase0);empty token string sets help flag,otherwise executes5705C0 filename. If help1809814 nonzero prints literal Usage: script <scriptfilename>. Uses global parser/context and returns incidental helper/pointer bits. No filename-capacity/recursion guard;query-only mode does no execution/help unless flags changed externally.
void **__cdecl rf_console_script_command_callback()
{
  void **result; // eax
  char *v1; // [esp+Ch] [ebp-4h]

  if ( dword_1809818 )
  {
    rf_console_read_argument_validate_type_mask(2, 0);
    v1 = &MEMORY[0x1809820] + strlen(&MEMORY[0x1809820]) + 1;
    result = (void **)(v1 - byte_1809821);
    if ( v1 == byte_1809821 )
      dword_1809814 = 1;
    else
      result = rf_console_execute_script_file(&MEMORY[0x1809820]);
  }
  if ( dword_1809814 )
    return (void **)rf_console_output_append_text_lines("Usage: script <scriptfilename>\n", nullptr);
  return result;
}

