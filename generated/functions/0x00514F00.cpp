// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00514F00 rf_console_framerate_test_command
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, timedemo/framerate state machine,x87FPS extrema,log ABI and recovered console handlers,original ECX/stack flow and PE bytes): Recovered exact code span514F00..515069,cdeclnoargs. Same levelstatebit0 main-menu-only rejection andglobal argumentcount/parser(typeMask2,required0) flow as514C80. Nonempty globalargumenttext1809820 unbounded-copiedto92DD90,.rfl suffixreplaced,commonstart514DE0 called;ONLYafterward setstep92DDFC=2 andnavModeBYTE92DE10=1 (commonstatus stays1). Emptyargumentsetsconsoleerror1809814=1;printUsage:frameratetest<level_name> onlyiferrornonzero. Zeroargumentcountdoesnotseterrorbyitself,and parserreturn/error isnot apre-startguard. No CLIstate663AF0 update,initialwaypointteleportorqualification. AL/EAX isnonsemanticresidue,charprototype followsinference. Literalstringsandparserusesupportcommandrole;no
// incomingxrefs observed orregistrationclaim.
char __cdecl rf_console_framerate_test_command()
{
  char result; // al
  char v1; // [esp+3h] [ebp-225h]
  char *v2; // [esp+8h] [ebp-220h]
  char *v3; // [esp+Ch] [ebp-21Ch]
  char *v5; // [esp+1Ch] [ebp-20Ch]
  char v6[516]; // [esp+20h] [ebp-208h] BYREF

  result = rf_level_state_bit0_is_set();
  if ( result )
    return rf_console_output_append_text_lines(
             "ERROR: This command can only be run from main menu, please exit game first",
             nullptr);
  if ( dword_1809818 )
  {
    rf_console_read_argument_validate_type_mask(2, 0);
    v5 = &MEMORY[0x1809820];
    do
      result = *v5;
    while ( *v5++ );
    if ( v5 == (char *)&unk_1809821 )
    {
      dword_1809814 = 1;
    }
    else
    {
      v3 = &MEMORY[0x1809820];
      v2 = unk_92DD90;
      do
      {
        v1 = *v3;
        *v2++ = *v3++;
      }
      while ( v1 );
      rf_path_replace_last_dot_suffix_unbounded(v6, unk_92DD90, ".rfl");
      result = rf_benchmark_start_level_and_reset_stats(v6);
      dword_92DDFC = 2;
      byte_92DE10 = 1;
    }
  }
  if ( dword_1809814 )
    return rf_console_output_append_text_lines("Usage: frameratetest <level_name>\n", nullptr);
  return result;
}

