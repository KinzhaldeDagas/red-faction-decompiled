// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005157C0 rf_timedemo_command_line_state_step
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, timedemo/framerate state machine,x87FPS extrema,log ABI and recovered console handlers,original ECX/stack flow and PE bytes): CdecloptionalnameCString,caller pops4;branches on signedglobal663AF0 equality1/2/3. State1:NULL/emptyname printsUsage:timedemo<name> then exit(0);nonemptysetbenchmarkstatus92DE1C=2,copyWHOLEname includingNUL unboundedto92DD90,setstate2. DoesNOTstartlevelin samecall. State2:replace last-dot suffix with.rfl into localbuffer via57C380(parentdirectory dots also qualify),callcommonstart514DE0;thenstatus=1,navModeBYTE=0,state=3 (commonstep remains1). State3:exit(1),includingNULLinputcallfrom results. Otherstate:no benchmarkwork. NonterminalEAX varies:state1 one-past-copied-NUL pointer,state2 delegatedstart residue,otherstatesunspecified;not normalizedsuccess. No argumentname use/check outside
// state1,buffer bounds,extensionvalidation orloopingthroughstatesin onecall.
char *__cdecl rf_timedemo_command_line_state_step(const char *a1)
{
  char *result; // eax
  char v2; // [esp+3h] [ebp-225h]
  char *v3; // [esp+8h] [ebp-220h]
  const char *v4; // [esp+Ch] [ebp-21Ch]
  char Source[516]; // [esp+20h] [ebp-208h] BYREF

  switch ( dword_663AF0 )
  {
    case 1:
      if ( !a1 || !strlen(a1) )
      {
        printf("Usage: timedemo <name>\n");
        exit(0);
      }
      unk_92DE1C = 2;
      v4 = a1;
      v3 = unk_92DD90;
      do
      {
        v2 = *v4;
        *v3 = *v4++;
        result = ++v3;
      }
      while ( v2 );
      dword_663AF0 = 2;
      break;
    case 2:
      rf_path_replace_last_dot_suffix_unbounded(Source, unk_92DD90, ".rfl");
      result = (char *)rf_benchmark_start_level_and_reset_stats(Source);
      unk_92DE1C = 1;
      byte_92DE10 = 0;
      dword_663AF0 = 3;
      break;
    case 3:
      exit(1);
  }
  return result;
}

