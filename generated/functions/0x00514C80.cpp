// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00514C80 rf_console_timedemo_command
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, timedemo/framerate state machine,x87FPS extrema,log ABI and recovered console handlers,original ECX/stack flow and PE bytes): Recovered exact code span514C80..514DD8,cdeclnoargs. If levelstatebit0query true,print main-menu-only error andreturn. Else ONLYifglobal argument-remaining1809818 !=0 callconsole parser(typeMask2,required0),IGNORE parserreturn,andinspect globaltextbuffer1809820. Nonempty:unboundedwhole-NULcopytolevelname92DD90,replace last-dot suffix with.rfl into localbuffer,callcommonstart514DE0. Empty:setglobal consoleerror1809814=1. Finally printUsage:timedemo<level_name> ONLYif consoleerrornonzero. Argumentcount0 by itself does NOT seterror here;preexistingerror/parserfailuredoes NOT gate levelstart beforefinalUsagecheck. No loop/multipleargumentconsume,boundscheck orCLIstate663AF0 update. AL/EAXresidue has
// no normalizedsuccessmeaning;char prototype retains inferredlowbyte contract. Command role supportedbyliteraltext/parseruse;no incomingxrefs observed,registration/reachability unproven.
char __cdecl rf_console_timedemo_command()
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
    }
  }
  if ( dword_1809814 )
    return rf_console_output_append_text_lines("Usage: timedemo <level_name>\n", nullptr);
  return result;
}

