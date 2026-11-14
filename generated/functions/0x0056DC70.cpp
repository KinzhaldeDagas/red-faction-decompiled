// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056DC70 rf_console_print_registered_help_list
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args. Prints header then loops global registry count180A480. Prints name - help only when helpPointer nonNULL and strlen(help)>0;commands without descriptions omitted. Registry entries themselves assumed nonNULL. Uses shared scratch18CD828 with unbounded sprintf and output56DD50. EAX incidental (loop count when nonempty),not a number of printed commands.
int rf_console_print_registered_help_list()
{
  int result; // eax
  int i; // [esp+14h] [ebp-4h]

  result = rf_console_output_append_text_lines(unk_88E280, nullptr);
  for ( i = 0; i < dword_180A480; ++i )
  {
    if ( *(_DWORD *)(dword_180A408[i] + 4) )
    {
      if ( strlen(*(const char **)(dword_180A408[i] + 4)) )
      {
        sprintf(&unk_18CD828, " %s - %s\n", *(const char **)dword_180A408[i], *(const char **)(dword_180A408[i] + 4));
        rf_console_output_append_text_lines(&unk_18CD828, nullptr);
      }
    }
    result = i + 1;
  }
  return result;
}

