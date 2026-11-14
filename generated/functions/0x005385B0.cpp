// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005385B0 rf_lightmap_blend_matching_record_seams
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Cdecl28-byte record array,count;NO real incoming x87 parameter. Old inferred double@st0 came from wrongly VOID fast-distance helper5598F0. For each record and its source face,collects corner pointers into fixed32-entry stack array,no vertex-count guard. Candidate descriptor must have SAME roomIndex104 and DIFFERENT descriptor index0. Skips IDs already in current record processed-neighbor array+16. Compares candidate face vertices to current face vertices using FAST approximate distance5598F0,stored float before strict<0.001000000047497451 threshold. First two positional matches supply seam endpoints;does not require distinct matched vertices,adjacent edges,equal normals or matching material.
// Calls5389B0 with endpoint pointers and ignored other-face-corner argument,then appends descriptor IDs symmetrically to processed arrays. Multiple candidate faces may be processed before outer membership check reruns,so ordering matters. Modifies atlas RAM via seam blender;no GPU upload/dirty flags here. No geometry/array/degenerate seam validation.
void __cdecl rf_lightmap_blend_matching_record_seams(int a1, int a2)
{
  int first_dword; // eax
  int v3; // [esp+0h] [ebp-D4h]
  int v4; // [esp+4h] [ebp-D0h]
  float v5; // [esp+8h] [ebp-CCh]
  int kk; // [esp+Ch] [ebp-C8h]
  int v7; // [esp+10h] [ebp-C4h]
  int v8; // [esp+18h] [ebp-BCh]
  int jj; // [esp+1Ch] [ebp-B8h]
  float **v10; // [esp+20h] [ebp-B4h]
  float **v11; // [esp+24h] [ebp-B0h]
  int ii; // [esp+28h] [ebp-ACh]
  int n; // [esp+2Ch] [ebp-A8h]
  char v14; // [esp+33h] [ebp-A1h]
  int v15; // [esp+34h] [ebp-A0h]
  int m; // [esp+38h] [ebp-9Ch]
  int v17; // [esp+3Ch] [ebp-98h]
  int v18; // [esp+40h] [ebp-94h]
  _DWORD v19[32]; // [esp+44h] [ebp-90h]
  int k; // [esp+C4h] [ebp-10h]
  int j; // [esp+C8h] [ebp-Ch]
  int **v22; // [esp+CCh] [ebp-8h]
  int i; // [esp+D0h] [ebp-4h]

  for ( i = 0; i < a2; ++i )
  {
    v22 = (int **)(a1 + 28 * i);
    for ( j = 0; ; ++j )
    {
      first_dword = rf_receiver_get_first_dword(v22 + 1);
      if ( j >= first_dword )
        break;
      v18 = 0;
      v17 = *(_DWORD *)sub_552200(v22 + 1, j);
      for ( k = *(_DWORD *)(v17 + 64); k; k = v4 )
      {
        v19[v18++] = k;
        if ( *(_DWORD *)(k + 20) == *(_DWORD *)(v17 + 64) )
          v4 = 0;
        else
          v4 = *(_DWORD *)(k + 20);
      }
      for ( m = 0; m < a2; ++m )
      {
        v15 = a1 + 28 * m;
        if ( *(_DWORD *)(*(_DWORD *)v15 + 104) == (*v22)[26] && **(_DWORD **)v15 != **v22 )
        {
          v14 = 0;
          for ( n = 0; n < rf_receiver_get_first_dword(v22 + 4); ++n )
          {
            if ( *(_DWORD *)sub_552200(v22 + 4, n) == **(_DWORD **)v15 )
            {
              v14 = 1;
              break;
            }
          }
          if ( !v14 )
          {
            for ( ii = 0; ii < rf_receiver_get_first_dword((void *)(v15 + 4)); ++ii )
            {
              v7 = *(_DWORD *)sub_552200((_DWORD *)(v15 + 4), ii);
              v11 = nullptr;
              v10 = nullptr;
              v8 = 0;
              for ( jj = *(_DWORD *)(v7 + 64); jj; jj = v3 )
              {
                for ( kk = 0; kk < v18; ++kk )
                {
                  v5 = rf_vector_fast_distance((const float *)*(_DWORD *)jj, (const float *)*(_DWORD *)v19[kk]);
                  if ( v5 < 0.001000000047497451 )
                  {
                    if ( v11 )
                    {
                      v10 = (float **)v19[kk];
                      break;
                    }
                    v11 = (float **)v19[kk];
                    v8 = jj;
                  }
                }
                if ( v10 )
                  break;
                if ( *(_DWORD *)(jj + 20) == *(_DWORD *)(v7 + 64) )
                  v3 = 0;
                else
                  v3 = *(_DWORD *)(jj + 20);
              }
              if ( v11 && v10 )
              {
                rf_lightmap_blend_tile_seam_along_segment(v22, (_DWORD **)v15, v11, v8, v10);
                rf_pointer_array_append_dword(v22 + 4, **(_DWORD **)v15);
                rf_pointer_array_append_dword((_DWORD *)(v15 + 16), **v22);
              }
            }
          }
        }
      }
    }
  }
}

