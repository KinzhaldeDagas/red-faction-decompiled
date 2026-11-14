// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00404740 rf_ai_scan_and_commit_weighted_target
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI weighted-target/mode11/15/16/speech/stimulus chains, original dispatch/float constants and native field
// lifetime and native signed/x87/stack/callback ABI): One required AI block. Deadline+732 elapsed any-nonzero ->save old target+704, obtain maximum attack range4098B0 roundedfloat32,
// maximum(range,100.0f) roundedfloat32 (unordered selects100), call402160(owner,threshold,extra difficulty+2), clean12; extra third slot unused by callee. Rearm+732 from unchecked
// difficulty-indexed661274 BEFORE testing result-1. Candidate found: mode2 OR(mode4 and owner DWORD+504==0) permits speech prelude. If target changed, AI DWORD+1228!=-1, class(+660)
// DWORD+360>=0: choose-random-Foley(class value) RETURN IS STORED BUT UNUSED; replace-speech(owner,ORIGINAL class value,0), propagate40A810(candidate handle,owner
// common+60,10.0f,LOWBYTE0,extra0), and arm block+1188 with LOW32 trunc(float32(duration(original class value))*1000+DOUBLE0.5)+250. This branch suppresses404900 fallback regardless
// of delegate outcomes. Otherwise404900(block,new candidate). Finally40BA80(block,candidate) then40B2D0(block), no acceptance-result gate; these last operations run for found
// candidates outside modes2/4 too. No own dead/silent/inactive/authority gate. EAX/AL is incidental helper result.
// UNREALRED VERIFIED [original-target-scan-cadence-20261112]: AI2DC cadence table661274 PE DWORDs are600,450,300,200 for raw active6612A4 indices0..3. Native index is unchecked, not clamped.402160 result precedes the rearm and the rearm precedes testing native result-1. Native scan calls may push difficulty+2 but402160 does not consume that third slot. Speech, target40BA80 and reaction40B2D0 are ordered calls, not a successful-targetsetter conditional reaction.
char __cdecl rf_ai_scan_and_commit_weighted_target(int *a1)
{
  char result; // al
  float v2; // [esp+4h] [ebp-24h]
  float duration; // [esp+Ch] [ebp-1Ch]
  int v4; // [esp+14h] [ebp-14h]
  char v5; // [esp+1Bh] [ebp-Dh]
  int v6; // [esp+1Ch] [ebp-Ch]
  float v7; // [esp+20h] [ebp-8h]
  int v8; // [esp+24h] [ebp-4h]

  result = rf_replicator_has_elapsed(a1 + 183);
  if ( result )
  {
    v6 = a1[176];
    v2 = rf_ai_resolve_maximum_attack_range(a1);
    v7 = rf_float_maximum_two_values(v2, 100.0);
    v8 = rf_ai_choose_weighted_target_handle((const float *)*a1, v7);
    result = rf_replicator_arm_milliseconds(a1 + 183, dword_661274[dword_6612A4]);
    if ( v8 != -1 )
    {
      if ( a1[160] == 2 || a1[160] == 4 && !*(_DWORD *)(*a1 + 504) )
      {
        v5 = 1;
        if ( v6 != v8 && a1[307] != -1 )
        {
          v4 = *(_DWORD *)(*(_DWORD *)(*a1 + 660) + 360);
          if ( v4 >= 0 )
          {
            rf_foley_choose_random_sound(v4);
            rf_entity_replace_speech_voice(*a1, v4, 0);
            rf_ai_propagate_stimulus_to_nearby_entities(v8, *a1 + 60, 10.0, 0);
            duration = rf_sound_query_duration(v4);
            rf_replicator_arm_milliseconds(a1 + 297, (int)(duration * 1000.0 + 0.5) + 250);
            v5 = 0;
          }
        }
        if ( v5 )
          rf_ai_play_target_acquisition_speech(a1, v8);
      }
      sub_40BA80(a1, v8);
      return sub_40B2D0(a1);
    }
  }
  return result;
}

