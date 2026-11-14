// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040FD80 sub_40FD80
// UNREALRED VERIFIED [combat-native-directed-ai-20261111] Target fit visits source nodes then unordered linked corridors with runtime pointer-order comparisons; fallback searches nodes within squared625 and invokes4D0650 filter2.5/mask1.410120 eligibility and40E830/40E950 geometry scratch are native data, not UE nav. Native heap pointer ranks cannot be recovered from RFL order alone; any stable host ordering must be explicit allocator adapter, preserving full corridor/control/math and recording incomplete address-order parity.
char __cdecl sub_40FD80(float *a1, float a2, float a3, char a4, int *a5, int *a6, char a7)
{
  int v8; // eax
  int v9; // [esp+14h] [ebp-44h]
  int v10; // [esp+1Ch] [ebp-3Ch]
  int v11; // [esp+20h] [ebp-38h]
  int v12; // [esp+28h] [ebp-30h] BYREF
  int v13; // [esp+2Ch] [ebp-2Ch]
  int j; // [esp+30h] [ebp-28h]
  int v15; // [esp+34h] [ebp-24h]
  int v16; // [esp+38h] [ebp-20h]
  int v17; // [esp+3Ch] [ebp-1Ch]
  int v18; // [esp+40h] [ebp-18h]
  int v19; // [esp+44h] [ebp-14h]
  int v20; // [esp+48h] [ebp-10h]
  char v21; // [esp+4Fh] [ebp-9h]
  int i; // [esp+50h] [ebp-8h]
  int first_dword; // [esp+54h] [ebp-4h]

  *a5 = 0;
  *a6 = 0;
  first_dword = rf_receiver_get_first_dword((void *)(rf_world_solid + 768));
  *(float *)&v20 = 3.4028235e38;
  for ( i = 0; i < first_dword; ++i )
  {
    v19 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 768), i);
    *(_BYTE *)(v19 + 53) = !rf_path_record_dimensions_and_flag_admit(a2, a3, a4, v19);
  }
  for ( i = 0; i < first_dword; ++i )
  {
    v17 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 768), i);
    if ( *(_BYTE *)(v17 + 53) != 1 )
    {
      v18 = sub_40E830(a1, a2, a3, a4, (float *)v17);
      if ( !v18 )
      {
        *a5 = v17;
        return 1;
      }
      if ( v18 == 1 && *(float *)&v20 > (double)*(float *)(v17 + 56) )
      {
        *a5 = v17;
        v20 = *(int *)(v17 + 56);
      }
    }
  }
  if ( *a5 )
    return 1;
  for ( i = 0; i < first_dword; ++i )
  {
    v16 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 768), i);
    if ( *(_BYTE *)(v16 + 53) != 1 )
    {
      v15 = rf_receiver_get_first_dword((void *)(v16 + 40));
      for ( j = 0; j < v15; ++j )
      {
        v13 = *(_DWORD *)sub_552200((_DWORD *)(v16 + 40), j);
        if ( v16 <= (unsigned int)v13 && *(_BYTE *)(v13 + 53) != 1 )
        {
          v9 = rf_route_edge_classify_point_clearance(a1, a2, (float *)v16, (float *)v13, (float *)&v12);
          if ( !v9 )
          {
            *a5 = v16;
            *a6 = v13;
            return 1;
          }
          if ( v9 == 1 && *(float *)&v20 > (double)*(float *)&v12 )
          {
            v20 = v12;
            *a5 = v16;
            *a6 = v13;
          }
        }
      }
    }
  }
  if ( *a5 && *a6 )
    return 1;
  v21 = 1;
  while ( v21 == 1 )
  {
    *(float *)&v20 = 3.4028235e38;
    v21 = 0;
    v11 = 0;
    for ( i = 0; i < first_dword; ++i )
    {
      v8 = sub_552200((_DWORD *)(rf_world_solid + 768), i);
      v10 = *(_DWORD *)v8;
      if ( *(_BYTE *)(*(_DWORD *)v8 + 53) != 1
        && (a7 || *(float *)(v10 + 56) <= 625.0)
        && *(float *)&v20 > (double)*(float *)(v10 + 56) )
      {
        v20 = *(int *)(v10 + 56);
        v11 = v10;
        v21 = 1;
      }
    }
    if ( v11 )
    {
      if ( !rf_segment_objects_or_world_hit_filtered_by_radius(v11 + 12, (int)a1, 2.5, 1, 0, 0, 0) )
      {
        *a5 = v11;
        return 0;
      }
      *(_BYTE *)(v11 + 53) = 1;
    }
  }
  return 0;
}

