// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005642A0 rf_model_handle_render_indexed_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,index,position,orientation,renderOptions80). Copies options locally. Tag1 optionally swaps handle material80 with FIRST mesh material pointer136,collects private200byte material record field16 into stack scratch, draws all144byte mesh records for index-1 or indexed mesh, then swaps back. Optional per-mesh override stream is traversed by DWORD-sized byte offsets from options28. Tag2 optionally installs private materials across148byte LOD containers,forces local LOD mode0 if global17F1118==1, selects564AB0 and renders selected container with character instance. Restore is INSIDE selected-container nonnull branch, so failed LOD selection leaves installed materials. Custom-material LOD
// loop writes count to EBP-8+4*i and old pointer to EBP-68h+4*i; i1 overwrites local distance(EBP-4) and SAVED HANDLE(EBP-64h),i2 count hits saved EBP. No scratch bounds checks. Tag3 swaps scene definition140 material pointer if byte84; whole render updates point pool records, draws meshes in flags3000clear,then2000,then1000 passes (both flags can draw twice). Literal sub.vfx bypasses ordering. Then draws flattened effect subobjects; indexed render draws only requested flat object. Normal scene end restores material pointer; no exception-safe restore or common success return.
int *__cdecl rf_model_handle_render_indexed_dispatch(int *a1, int a2, int a3, float *a4, int a5)
{
  int *result; // eax
  int v6; // [esp+Ch] [ebp-1B8h]
  int v7; // [esp+10h] [ebp-1B4h]
  int i1; // [esp+14h] [ebp-1B0h]
  int v9; // [esp+18h] [ebp-1ACh]
  int ii; // [esp+1Ch] [ebp-1A8h]
  int jj; // [esp+1Ch] [ebp-1A8h]
  int kk; // [esp+1Ch] [ebp-1A8h]
  int mm; // [esp+1Ch] [ebp-1A8h]
  int nn; // [esp+1Ch] [ebp-1A8h]
  int v15; // [esp+20h] [ebp-1A4h]
  char *String1; // [esp+24h] [ebp-1A0h]
  int v17; // [esp+28h] [ebp-19Ch]
  int v18; // [esp+2Ch] [ebp-198h]
  int k; // [esp+30h] [ebp-194h]
  int v20; // [esp+34h] [ebp-190h]
  int v21; // [esp+38h] [ebp-18Ch]
  int mesh_count; // [esp+3Ch] [ebp-188h]
  int i; // [esp+40h] [ebp-184h]
  int v24; // [esp+44h] [ebp-180h]
  int v25; // [esp+48h] [ebp-17Ch]
  int n; // [esp+4Ch] [ebp-178h]
  int m; // [esp+50h] [ebp-174h]
  int v28; // [esp+54h] [ebp-170h]
  _DWORD *v29; // [esp+58h] [ebp-16Ch]
  _DWORD *v30; // [esp+58h] [ebp-16Ch]
  _DWORD v31[65]; // [esp+5Ch] [ebp-168h] BYREF
  int *v32; // [esp+160h] [ebp-64h]
  int v33; // [esp+164h] [ebp-60h] BYREF
  int v34; // [esp+168h] [ebp-5Ch]
  _DWORD *v35; // [esp+174h] [ebp-50h]
  _DWORD *v36; // [esp+180h] [ebp-44h]
  int *v37; // [esp+1B4h] [ebp-10h]
  int j; // [esp+1B8h] [ebp-Ch]
  int v39; // [esp+1BCh] [ebp-8h] BYREF
  float v40; // [esp+1C0h] [ebp-4h]

  v32 = a1;
  rf_model_render_options_copy_construct((float *)&v33, (float *)a5);
  v40 = 0.0;
  result = (int *)*a1;
  v6 = *a1;
  if ( *a1 == 1 )
  {
    if ( *((_BYTE *)v32 + 84) )
    {
      v24 = v32[20];
      v32[20] = *(_DWORD *)(*(_DWORD *)(v32[1] + 76) + 136);
      *(_DWORD *)(*(_DWORD *)(v32[1] + 76) + 136) = v24;
      v35 = v31;
      for ( i = 0; i < *(_DWORD *)(*(_DWORD *)(v32[1] + 76) + 132); ++i )
        v31[i] = *(_DWORD *)(v24 + 200 * i + 16);
    }
    v29 = *(_DWORD **)(a5 + 28);
    if ( a2 == -1 )
    {
      mesh_count = rf_v3c_asset_get_mesh_count((_DWORD *)v32[1]);
      for ( j = 0; j < mesh_count; ++j )
      {
        v21 = *(_DWORD *)(v32[1] + 76) + 144 * j;
        if ( v21 )
        {
          if ( v29 )
          {
            v36 = v29 + 1;
            v29 = (_DWORD *)((char *)v29 + *v29);
          }
          if ( *((_BYTE *)v32 + 84) )
            v35 = v31;
          rf_model_mesh_render_with_lod_translation(v32[1], v21, a3, a4, &v33);
        }
      }
    }
    else
    {
      v20 = *(_DWORD *)(v32[1] + 76) + 144 * a2;
      if ( *(_DWORD *)(a5 + 28) )
      {
        v30 = *(_DWORD **)(a5 + 28);
        for ( k = 0; k < a2; ++k )
          v30 = (_DWORD *)((char *)v30 + *v30);
        v36 = v30 + 1;
      }
      rf_model_mesh_render_with_lod_translation(v32[1], v20, a3, a4, &v33);
    }
    result = v32;
    if ( *((_BYTE *)v32 + 84) )
    {
      v18 = v32[20];
      v32[20] = *(_DWORD *)(*(_DWORD *)(v32[1] + 76) + 136);
      result = (int *)v18;
      *(_DWORD *)(*(_DWORD *)(v32[1] + 76) + 136) = v18;
    }
  }
  else if ( v6 == 2 )
  {
    if ( *((_BYTE *)v32 + 84) )
    {
      v35 = v31;
      v28 = 0;
      for ( m = 0; m < *(_DWORD *)(v32[2] + 6588); ++m )
      {
        rf_model_container_get_reference_mesh_materials((_DWORD *)(v32[2] + 148 * m + 6592), &v39 + m, &v31[m + 64]);
        rf_model_container_set_reference_mesh_materials((_DWORD *)(v32[2] + 148 * m + 6592), v32[20] + 200 * v28);
        for ( n = 0; n < *(&v39 + m); ++n )
          v31[n + v28] = *(_DWORD *)(v32[20] + 200 * (n + v28) + 16);
        v28 += *(&v39 + m);
      }
    }
    if ( unk_17F1118 == 1 )
      v34 = 0;
    result = (int *)rf_character_select_lod_container(v32[2], v34, v40);
    v37 = result;
    if ( result )
    {
      rf_model_instance_render_with_lod_translation((int)v37, v32[1], a3, a4, &v33);
      result = (int *)*((unsigned __int8 *)v32 + 84);
      if ( *((_BYTE *)v32 + 84) )
      {
        v25 = 0;
        for ( j = 0; ; ++j )
        {
          result = (int *)v32[2];
          if ( j >= result[1647] )
            break;
          rf_model_container_set_reference_mesh_materials((_DWORD *)(v32[2] + 148 * j + 6592), v31[j + 64]);
          v25 += *(&v39 + j);
        }
      }
    }
  }
  else if ( v6 == 3 )
  {
    if ( *((_BYTE *)v32 + 84) )
    {
      v15 = v32[20];
      v32[20] = *(_DWORD *)(v32[2] + 140);
      *(_DWORD *)(v32[2] + 140) = v15;
    }
    String1 = (char *)v32[2];
    v17 = v32[1];
    if ( a2 == -1 )
    {
      for ( ii = 0; ii < *((_DWORD *)String1 + 21); ++ii )
        rf_scene_point_track_update_pool_record(*(_DWORD *)(v17 + 24) + 60 * ii, v17, *(float *)(v17 + 16), a3, a4);
      if ( !_stricmp(String1, "sub.vfx") )
      {
        for ( jj = 0; jj < *((_DWORD *)String1 + 19); ++jj )
          rf_scene_instance_draw_flat_object(v17, jj, a3, (int)a4);
      }
      else
      {
        for ( kk = 0; kk < *((_DWORD *)String1 + 19); ++kk )
        {
          if ( (*(_DWORD *)(*((_DWORD *)String1 + 18) + 292 * kk + 276) & 0x3000) == 0 )
            rf_scene_instance_draw_flat_object(v17, kk, a3, (int)a4);
        }
        for ( mm = 0; mm < *((_DWORD *)String1 + 19); ++mm )
        {
          if ( (*(_DWORD *)(*((_DWORD *)String1 + 18) + 292 * mm + 276) & 0x2000) != 0 )
            rf_scene_instance_draw_flat_object(v17, mm, a3, (int)a4);
        }
        for ( jj = 0; jj < *((_DWORD *)String1 + 19); ++jj )
        {
          if ( (*(_DWORD *)(*((_DWORD *)String1 + 18) + 292 * jj + 276) & 0x1000) != 0 )
            rf_scene_instance_draw_flat_object(v17, jj, a3, (int)a4);
        }
      }
      v9 = jj;
      for ( nn = 0; nn < *((_DWORD *)String1 + 23); ++nn )
      {
        for ( i1 = 0; i1 < *(_DWORD *)(*((_DWORD *)String1 + 22) + 220 * nn + 152); ++i1 )
          rf_scene_instance_draw_flat_object(v17, v9++, a3, (int)a4);
      }
    }
    else
    {
      rf_scene_instance_draw_flat_object(v17, a2, a3, (int)a4);
    }
    result = v32;
    if ( *((_BYTE *)v32 + 84) )
    {
      v7 = v32[20];
      v32[20] = *(_DWORD *)(v32[2] + 140);
      result = (int *)v32[2];
      result[35] = v7;
    }
  }
  return result;
}

