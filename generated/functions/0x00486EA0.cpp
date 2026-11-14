// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486EA0 sub_486EA0
// UNREALRED VERIFIED [ai-health-goals-20261028] RFL loader caller0x47D280 loads named waypoint lists: int32 listcount at0x700478; each0x20C-byte record has RF string at+0, pointcount at+8 and pointindices at+0xC. RFL version>=140 reads each pointindex directly. Older versions create0x7C-byte point records, initialize legacy defaults and link successive points. Full point-pool ownership/section identifiers still need tracing.
int __cdecl sub_486EA0(_DWORD *a1)
{
  int result; // eax
  int int32_versioned; // eax
  double float_versioned; // st7
  int v4; // eax
  float *v5; // [esp+8h] [ebp-3Ch]
  char *v6; // [esp+Ch] [ebp-38h]
  int v7; // [esp+14h] [ebp-30h]
  int v8; // [esp+18h] [ebp-2Ch]
  int v9[2]; // [esp+1Ch] [ebp-28h] BYREF
  float *v10; // [esp+24h] [ebp-20h]
  int v11; // [esp+28h] [ebp-1Ch]
  int j; // [esp+2Ch] [ebp-18h]
  int v13; // [esp+30h] [ebp-14h]
  int i; // [esp+34h] [ebp-10h]
  int v15; // [esp+40h] [ebp-4h]

  v13 = 0;
  result = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  dword_700478 = result;
  for ( i = 0; i < dword_700478; ++i )
  {
    v11 = (int)&dword_700480[131 * i];
    rf_binary_stream_read_string_object_versioned(a1, (_DWORD *)v11, 0, nullptr);
    int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    *(_DWORD *)(v11 + 8) = int32_versioned;
    for ( j = 0; j < *(_DWORD *)(v11 + 8); ++j )
    {
      if ( rf_vfile_get_slot_version(a1) >= 140 )
      {
        v4 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
        *(_DWORD *)(v11 + 4 * j + 12) = v4;
      }
      else
      {
        v6 = (char *)operator new(0x7Cu);
        v15 = 0;
        if ( v6 )
          v5 = (float *)rf_dual_array_pose_block_construct_empty(v6);
        else
          v5 = nullptr;
        v15 = -1;
        v10 = v5;
        rf_binary_stream_read_int32_versioned(a1, 0, 0);
        rf_binary_stream_read_vector3_versioned(a1, v10, 0, unk_1C8FBDC);
        if ( rf_vfile_get_slot_version(a1) < 67 )
        {
          rf_string_construct_empty(v9);
          v15 = 1;
          rf_binary_stream_read_string_object_versioned(a1, v9, 0, nullptr);
          v15 = -1;
          rf_string_destroy_buffer(v9);
        }
        rf_binary_stream_read_bool_versioned(a1, 0, 1);
        float_versioned = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
        v10[9] = float_versioned;
        v10[7] = 0.5;
        v10[8] = 2.0;
        *((_DWORD *)v10 + 27) = v13;
        rf_pointer_array_append_dword((_DWORD *)(rf_world_solid + 768), (int)v10);
        *(_DWORD *)(v11 + 4 * j + 12) = v13++;
      }
    }
    if ( rf_vfile_get_slot_version(a1) < 140 && *(int *)(v11 + 8) >= 2 )
    {
      for ( j = 0; j < *(_DWORD *)(v11 + 8) - 1; ++j )
      {
        v8 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 768), *(_DWORD *)(v11 + 4 * j + 12));
        v7 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 768), *(_DWORD *)(v11 + 4 * j + 16));
        rf_pointer_array_append_dword((_DWORD *)(v8 + 40), v7);
        rf_pointer_array_append_dword((_DWORD *)(v7 + 40), v8);
      }
    }
    result = i + 1;
  }
  return result;
}

