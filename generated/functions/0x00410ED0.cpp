// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00410ED0 rf_ai_goto_install_destination
// UNREALRED VERIFIED [ai-goto-completion-20261028] Both successful and failed Goto route-admission branches write current numeric mode2 and secondary1 via writers; neither writes saved mode AI+0x284 or saved secondary AI+0x2B8. Destination at entity+0x6EC survives embedded-route reset. At native mode2 route arrival0x409950, restore uses those independently retained saved fields.
// UNREALRED VERIFIED [original-goto-prior-mode-20261112]: Initial434150/40E030 executes under the PRIOR numeric mode, before this caller writes requested2. Thus only actual prior2/16 gets40E030 endpoint-distance bypass; requested Goto2 alone is not a bypass. Successful434150 writes secondary1 for prior3/10, otherwise temporary mode4; outer success then flags/destination/mode2/secondary1. Outer failure armsAI2301000, resets same embedded route, then mode2/secondary1 without success-only flag writes.
int __cdecl rf_ai_goto_install_destination(int a1, float *source, char a3, char a4, char a5)
{
  unsigned int v5; // ecx
  unsigned int v6; // edx
  unsigned int v7; // eax
  float v9[3]; // [esp+4h] [ebp-1Ch] BYREF
  float copy_result[3]; // [esp+10h] [ebp-10h] BYREF
  int v11; // [esp+1Ch] [ebp-4h]

  v11 = rf_entity_resolve_handle(a1);
  rf_ai_cancel_tracked_body_action((int *)(v11 + 672));
  rf_ai_clear_scripted_animation_context((int *)(v11 + 672));
  rf_vector_copy((float *)(v11 + 1772), copy_result, source);
  if ( rf_ai_scripted_route_admit(*(_DWORD *)(v11 + 44), (int)source) )
  {
    rf_replicator_arm_milliseconds((int *)(v11 + 1232), 1000);
    rf_ai_route_reset(v11 + 1416);
    rf_ai_numeric_mode_write((_DWORD *)(v11 + 672), 2, -1, -1);
    rf_ai_secondary_state_write(v11 + 672, 1);
    return -1;
  }
  else
  {
    if ( a3 == 1 )
      v5 = *(_DWORD *)(v11 + 2000) | 8;
    else
      v5 = *(_DWORD *)(v11 + 2000) & 0xFFFFFFF7;
    *(_DWORD *)(v11 + 2000) = v5;
    if ( a4 == 1 )
      v6 = *(_DWORD *)(v11 + 2000) | 0x10000000;
    else
      v6 = *(_DWORD *)(v11 + 2000) & 0xEFFFFFFF;
    *(_DWORD *)(v11 + 2000) = v6;
    if ( a5 == 1 )
      v7 = *(_DWORD *)(v11 + 2000) | 0x40000000;
    else
      v7 = *(_DWORD *)(v11 + 2000) & 0xBFFFFFFF;
    *(_DWORD *)(v11 + 2000) = v7;
    rf_vector_copy((float *)(v11 + 1772), v9, source);
    rf_ai_numeric_mode_write((_DWORD *)(v11 + 672), 2, -1, -1);
    rf_ai_secondary_state_write(v11 + 672, 1);
    return 0;
  }
}

