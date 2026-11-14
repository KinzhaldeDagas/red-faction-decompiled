// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A3DD0 rf_model_render_select_lod_and_skin
// UNREALRED VERIFIED [character-pipeline-20261029]: cdecl LOD table,world position,orientation,optional character instance,render context. Requires enable BYTE0x664818 and nonnull table. If context flags0x80 clear and no precomputed RGB+28,sets context RGB bytes+40..42=global ambient coefficients*255. Context flags mask9 force LOD=count-1. Otherwise default0;when special mode0x1C99894 clear and count>1,starts at min(global0x1C99890,count-1),computes scaled Euclidean LOD distance0x581710,multiplies2.5 only for multiplayer plus character instance,scans thresholds at table+16+4*i from last toward minimum and selects first threshold<=metric. Builds3 lights0x5A1070. Flags9 without flag2 call packed helper unknown_libname_29(0),store context+12. Destructively replaces context RGB-table+28 with selected LOD pointer; texture override+16 remaps selected mesh BYTE indices+24 into local7-DWORD array
// then leaves context+16 pointing at stack array (not restored). No remap count<=7 guard. Character path updates skin transforms; nonzero LOD with byte0x663F05 alternates using character BYTE+4812,other cases always rebuild. Dispatches character morph renderer0x5A2570 when instance supplied,else0x5A1470. No positive LOD-count,upper-array,global-minimum or context-pointer validation; selected mesh pointer comes from table+4+4*LOD.
void __cdecl rf_model_render_select_lod_and_skin(int *a1, float *position, float *a3, int a4, int a5)
{
  int v5; // [esp+0h] [ebp-5Ch]
  int v6; // [esp+28h] [ebp-34h] BYREF
  int j; // [esp+2Ch] [ebp-30h]
  int i; // [esp+30h] [ebp-2Ch]
  float v9; // [esp+34h] [ebp-28h]
  int v10; // [esp+38h] [ebp-24h]
  int v11; // [esp+3Ch] [ebp-20h]
  _DWORD v12[7]; // [esp+40h] [ebp-1Ch] BYREF

  if ( byte_664818 && a1 )
  {
    if ( (*(_DWORD *)a5 & 0x80) == 0 && !*(_DWORD *)(a5 + 28) )
    {
      *(_BYTE *)(a5 + 40) = (int)(flt_663B1C * 255.0);
      *(_BYTE *)(a5 + 41) = (int)(flt_663B20 * 255.0);
      *(_BYTE *)(a5 + 42) = (int)(flt_663B24 * 255.0);
    }
    v11 = 0;
    if ( (*(_DWORD *)a5 & 9) != 0 )
    {
      v11 = *a1 - 1;
    }
    else if ( !unk_1C99894 && *a1 > 1 )
    {
      if ( dword_1C99890 >= *a1 - 1 )
        v5 = *a1 - 1;
      else
        v5 = dword_1C99890;
      v10 = v5;
      v11 = v5;
      v9 = rf_renderer_lod_distance_scaled(position);
      if ( rf_multiplayer_runtime_mode && a4 )
        v9 = v9 * 2.5;
      for ( i = *a1 - 1; i >= v10; --i )
      {
        if ( *(float *)&a1[i + 4] <= (double)v9 )
        {
          v11 = i;
          break;
        }
      }
    }
    rf_render_prepare_three_light_records(a5, position, a3);
    if ( (*(_DWORD *)a5 & 9) != 0 && (*(_DWORD *)a5 & 2) == 0 )
    {
      rf_packed_dword_construct_return_self_5719E0(&v6, 0);
      *(_DWORD *)(a5 + 12) = v6;
    }
    if ( *(_DWORD *)(a5 + 28) )
      *(_DWORD *)(a5 + 28) = *(_DWORD *)(*(_DWORD *)(a5 + 28) + 4 * v11);
    if ( *(_DWORD *)(a5 + 16) )
    {
      for ( j = 0; j < *(_DWORD *)(a1[v11 + 1] + 60); ++j )
        v12[j] = *(_DWORD *)(*(_DWORD *)(a5 + 16) + 4 * *(unsigned __int8 *)(a1[v11 + 1] + j + 24));
      *(_DWORD *)(a5 + 16) = v12;
    }
    if ( a4 )
    {
      if ( v11 && byte_663F05 )
      {
        if ( *(_BYTE *)(a4 + 4812) )
        {
          *(_BYTE *)(a4 + 4812) = 0;
        }
        else
        {
          *(_BYTE *)(a4 + 4812) = 1;
          rf_character_build_skin_transforms(a4, 0, *(_DWORD *)(a4 + 7504) + 6592, 0, 0, 0, 1);
        }
      }
      else
      {
        rf_character_build_skin_transforms(a4, 0, *(_DWORD *)(a4 + 7504) + 6592, 0, 0, 0, 1);
        *(_BYTE *)(a4 + 4812) = 1;
      }
    }
    if ( a4 )
      rf_character_render_skinned_lod_batches((int)a1, a1[v11 + 1], position, a3, a4, v11, a5);
    else
      rf_model_render_unskinned_lod_batches((int)a1, a1[v11 + 1], position, a3, v11, a5);
  }
}

