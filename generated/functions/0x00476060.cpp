// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00476060 rf_cutscene_start_segment
// UNREALRED VERIFIED [cutscene-ui-20261028]: Uses active record0x6FB24C plus index*32: camera ID at+8 -> camera index+2060 via0x475E30; sums duration fields and arms timer+2064 with trunc(sum/1.017579913139343*1000+0.5). Stores caller record+8+32*i as current-segment pointer+2076; optional RF string at segment+24 resolves100-byte named record through0x476270 and stores+2080, optionally arms timer+2068 from segment+4 with same conversion. Clears float+2132 and byte+2136. Copies selected camera position+4 and orientation+16 into active record+2084/+2096. Resolves linked object ID from active record+28+32*i through0x4BC680, dispatches common type5 trigger,6 event,8 mover. No null-active, index-range, or failed camera-index guard in this body. Caller record and active global are both used; no equality check.
char __cdecl rf_cutscene_start_segment(int a1, int a2)
{
  char *v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v7; // [esp+0h] [ebp-24h]
  float copy_result[3]; // [esp+4h] [ebp-20h] BYREF
  int v9; // [esp+10h] [ebp-14h]
  float v10; // [esp+14h] [ebp-10h]
  int v11; // [esp+18h] [ebp-Ch]
  int v12; // [esp+1Ch] [ebp-8h]
  int v13; // [esp+20h] [ebp-4h]

  v9 = *(_DWORD *)(dword_6FB24C + 32 * a2 + 8);
  *(_DWORD *)(dword_6FB24C + 2060) = rf_cutscene_camera_find_index_by_id(v9);
  v10 = rf_cutscene_segment_sum_duration(dword_6FB24C, a2);
  rf_replicator_arm_milliseconds((int *)(dword_6FB24C + 2064), (int)(v10 / 1.017579913139343 * 1000.0 + 0.5));
  v12 = a1 + 32 * a2 + 8;
  *(_DWORD *)(dword_6FB24C + 2076) = v12;
  if ( (int)rf_string_length_from_cstr((const char **)(v12 + 24)) <= 0 )
  {
    *(_DWORD *)(dword_6FB24C + 2080) = 0;
  }
  else
  {
    v2 = (char *)rf_string_object_c_str_or_empty((const void *)(v12 + 24));
    *(_DWORD *)(dword_6FB24C + 2080) = rf_cutscene_named_segment_record_find(v2);
    if ( *(_DWORD *)(dword_6FB24C + 2080) )
      rf_replicator_arm_milliseconds(
        (int *)(dword_6FB24C + 2068),
        (int)(*(float *)(v12 + 4) / 1.017579913139343 * 1000.0 + 0.5));
  }
  *(float *)(dword_6FB24C + 2132) = 0.0;
  *(_BYTE *)(dword_6FB24C + 2136) = 0;
  v3 = sub_552200(unk_6FB258, *(_DWORD *)(dword_6FB24C + 2060));
  rf_vector_copy((float *)(dword_6FB24C + 2084), copy_result, (const float *)(*(_DWORD *)v3 + 4));
  v4 = sub_552200(unk_6FB258, *(_DWORD *)(dword_6FB24C + 2060));
  rf_matrix3_copy((float *)(dword_6FB24C + 2096), (const float *)(*(_DWORD *)v4 + 16));
  v13 = *(_DWORD *)(dword_6FB24C + 32 * a2 + 28);
  v5 = rf_object_find_by_saved_identifier(v13);
  v11 = v5;
  if ( v5 )
  {
    LOBYTE(v5) = v11;
    v7 = *(_DWORD *)(v11 + 36);
    switch ( v7 )
    {
      case 5:
        LOBYTE(v5) = rf_trigger_commit_activation(v11, -1, 0, 0);
        break;
      case 6:
        LOBYTE(v5) = (unsigned __int8)rf_mission_event_activate_by_uid(*(_DWORD *)(v11 + 44), -1, -1);
        break;
      case 8:
        LOBYTE(v5) = rf_mover_activate_forward(*(_DWORD *)(v11 + 44), -1, -1);
        break;
    }
  }
  return v5;
}

