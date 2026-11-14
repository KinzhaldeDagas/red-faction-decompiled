// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00515930 rf_framerate_test_command_line_state_step
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, timedemo/framerate state machine,x87FPS extrema,log ABI and recovered console handlers,original ECX/stack flow and PE bytes): CdecloptionalnameCString,caller pops4,state663AF0 equality1/2/3. State1:NULL/emptyname prints the SAME timedemo Usage string (notframeratetest) then exit(0);nonemptysetstatus92DE1C=3,unboundedwhole-name/NULcopyto92DD90,setstate2,returnwithoutloading. State2:replace last-dot suffix with.rfl through57C380,callcommonstart514DE0;THEN setstep92DDFC=2,navModeBYTE92DE10=1,status92DE1C=1,state663AF0=3. State3 exit(1),no argumentneeded. Otherstatesno benchmarkwork. No initialteleport/waypointfilter,framecountvalidation,bufferlimit orstable successreturn;state1EAX isonepastcopiedNUL,state2delegatedstartresidue. Nativeframerate variantsets2-degree increments (180 expected samples/batch),not a timebudget.
char *__cdecl rf_framerate_test_command_line_state_step(const char *a1)
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
      unk_92DE1C = 3;
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
      dword_92DDFC = 2;
      byte_92DE10 = 1;
      unk_92DE1C = 1;
      dword_663AF0 = 3;
      break;
    case 3:
      exit(1);
  }
  return result;
}

