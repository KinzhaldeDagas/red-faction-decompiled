// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052ADC0 rf_geomod_boolean_advance
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): No argsAL continuation flag. If signedstage<0 return0 with no work. Else clock elapsed_scaled(1000), save oldstage then INCREMENT globalstage BEFORE dispatch. Old0 merge with7 storedargs;1 candidates(workspace,mode);2 split(workspace,0,0);3 classify;4 transfer(workspace,outSolid,transferMode,outArea);5 policyRooms(workspace,mode) withTWO stackDWORDs/callerpop8;6 cleanup;7 finish pluslocalcomplete1. Store elapsed millisecond-scale difference inD4B898[oldstage]. Invalid>=8 still increments and writes unchecked timing index,returns1; no stage clamp. Normally0..6 return1; ONLY after stage7, optionaldebugbyte D4B7D5 sums timings into unusedlocal, mark live scratch-owner blocks54ADF0,
// setstage-1 andreturn0. No time-budget/yield check or initializer-success test; one whole stage percall. Split reinsertion behavior belongs nested pair routine; wrapper only supplies literal zero selectors and stage2 ends with corner-limit cleanup of active+backup lists.
char rf_geomod_boolean_advance()
{
  int v1; // [esp+10h] [ebp-1Ch]
  int v2; // [esp+14h] [ebp-18h]
  int i; // [esp+18h] [ebp-14h]
  char v4; // [esp+1Fh] [ebp-Dh]
  int v5; // [esp+20h] [ebp-Ch]
  int v6; // [esp+24h] [ebp-8h]

  if ( rf_geomod_boolean_stage < 0 )
    return 0;
  v4 = 0;
  v5 = rf_performance_clock_elapsed_scaled(1000);
  v6 = rf_geomod_boolean_stage;
  v1 = rf_geomod_boolean_stage++;
  switch ( v1 )
  {
    case 0:
      rf_geomod_boolean_stage_0_merge(
        (_DWORD *)dword_D4B88C,
        (_DWORD *)unk_D4B7C8,
        (float *)unk_D4B7D0,
        unk_D4B7F0,
        unk_D4B8E8,
        unk_D4B7D8,
        unk_D4B7C0);
      break;
    case 1:
      rf_geomod_boolean_stage_1_candidates((_DWORD *)dword_D4B88C, dword_D4B890);
      break;
    case 2:
      rf_geomod_boolean_stage_2_split((_DWORD *)dword_D4B88C, 0, 0);
      break;
    case 3:
      rf_geomod_boolean_stage_3_classify(dword_D4B88C, dword_D4B890);
      break;
    case 4:
      rf_geomod_boolean_stage_4_transfer(dword_D4B88C, unk_D4B894, unk_D4B8E4, unk_D4B8DC);
      break;
    case 5:
      rf_geomod_boolean_stage_5_policy_rooms((float *)dword_D4B88C, dword_D4B890);
      break;
    case 6:
      rf_geomod_boolean_stage_6_cleanup(dword_D4B88C);
      break;
    case 7:
      rf_geomod_boolean_stage_7_finish((char *)dword_D4B88C);
      v4 = 1;
      break;
    default:
      break;
  }
  unk_D4B898[v6] = rf_performance_clock_elapsed_scaled(1000) - v5;
  if ( !v4 )
    return 1;
  if ( unk_D4B7D5 )
  {
    v2 = 0;
    for ( i = 0; i < rf_geomod_boolean_stage; ++i )
      v2 += unk_D4B898[i];
  }
  rf_scratch_arena_mark_live_owner_blocks();
  rf_geomod_boolean_stage = -1;
  return 0;
}

