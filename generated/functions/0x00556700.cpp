// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556700 rf_solid_project_selected_uvs_from_transformed_copy
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): ECX solid plus translationXYZ and orientation matrix, RET8. Clones entire solid with welding disabled via51A2B0 (still sorts ORIGINAL vertex array and writes original Vertex28 maps), transforms all clone vertices by vector*matrix+translation and finalizes all clone faces. For corresponding selected textured original faces, chooses dominant normal axis on clone and writes original primary UVs from transformed clone positions, global scale663E60 divided by original bitmap width/height(default16). DominantY:U=(ny>0?-x:x),V=z; dominantX:U=(nx>0?z:-z),V=-y; dominantZ:U=(nz>0?-x:x),V=-y, multiplied by respective scales. Skips original bitmap=-1; secondary UV unchanged. Destroys clone after use; no original geometry transform/room
// update or allocation/finalize check.
void __thiscall rf_solid_project_selected_uvs_from_transformed_copy(void *this, const float *a2, const float *a3)
{
  int first_dword; // eax
  float *v4; // eax
  float *v5; // eax
  int v6; // eax
  double v7; // st7
  double v8; // st7
  double v9; // st7
  int v10; // [esp+4h] [ebp-84h]
  _DWORD *v11; // [esp+8h] [ebp-80h]
  int v12; // [esp+Ch] [ebp-7Ch]
  _DWORD *v13; // [esp+10h] [ebp-78h]
  float copy_result[3]; // [esp+20h] [ebp-68h] BYREF
  float sum_result[3]; // [esp+2Ch] [ebp-5Ch] BYREF
  float v17[3]; // [esp+38h] [ebp-50h] BYREF
  _DWORD *k; // [esp+44h] [ebp-44h]
  int v19; // [esp+48h] [ebp-40h]
  _DWORD *m; // [esp+4Ch] [ebp-3Ch]
  int v21; // [esp+50h] [ebp-38h]
  int v22; // [esp+54h] [ebp-34h] BYREF
  float v23; // [esp+58h] [ebp-30h]
  float *v24; // [esp+5Ch] [ebp-2Ch]
  int v25; // [esp+60h] [ebp-28h] BYREF
  int v26; // [esp+64h] [ebp-24h]
  int v27; // [esp+68h] [ebp-20h] BYREF
  float v28; // [esp+6Ch] [ebp-1Ch]
  int v29; // [esp+70h] [ebp-18h] BYREF
  int v30; // [esp+74h] [ebp-14h] BYREF
  float *destination; // [esp+78h] [ebp-10h]
  int j; // [esp+7Ch] [ebp-Ch]
  void **v33; // [esp+80h] [ebp-8h]
  int i; // [esp+84h] [ebp-4h]

  v33 = rf_solid_clone_with_optional_vertex_welding((char *)this, 0);
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword(v33 + 30);
    if ( i >= first_dword )
      break;
    destination = *(float **)sub_552200(v33 + 30, i);
    v4 = rf_matrix3_rotate_vector(destination, v17, (float *)a3);
    v5 = rf_vector_add(v4, sum_result, a2);
    rf_vector_copy(destination, copy_result, v5);
  }
  for ( j = rf_receiver_get_first_dword(v33 + 28); j; j = rf_solid_face_next_link(j) )
    rf_geomod_face_finalize_geometry(j, nullptr, 0);
  for ( i = 0; ; ++i )
  {
    v6 = rf_receiver_get_first_dword(v33 + 54);
    if ( i >= v6 )
      break;
    v26 = *(_DWORD *)sub_552200((_DWORD *)this + 54, i);
    if ( *(_DWORD *)(v26 + 48) != -1 )
    {
      v24 = *(float **)sub_552200(v33 + 54, i);
      rf_face_projection_axes_select(v24, &v25, &v27, &v22);
      v30 = 16;
      v29 = 16;
      rf_bitmap_get_resolved_dimensions(*(_DWORD *)(v26 + 48), &v30, &v29);
      v28 = flt_663E60 / (double)v30;
      v23 = flt_663E60 / (double)v29;
      if ( v25 == 1 )
      {
        v19 = *(_DWORD *)(v26 + 64);
        for ( k = *((_DWORD **)v24 + 16); k; k = v11 )
        {
          if ( v24[1] <= 0.0 )
            v9 = *(float *)*k * v28;
          else
            v9 = -*(float *)*k * v28;
          *(float *)(v19 + 4) = v9;
          *(float *)(v19 + 8) = *(float *)(*k + 8) * v23;
          if ( *(_DWORD *)(v19 + 20) == *(_DWORD *)(v26 + 64) )
            v10 = 0;
          else
            v10 = *(_DWORD *)(v19 + 20);
          v19 = v10;
          if ( k[5] == *((_DWORD *)v24 + 16) )
            v11 = nullptr;
          else
            v11 = (_DWORD *)k[5];
        }
      }
      else
      {
        v21 = *(_DWORD *)(v26 + 64);
        for ( m = *((_DWORD **)v24 + 16); m; m = v13 )
        {
          if ( v25 )
          {
            if ( v24[2] <= 0.0 )
              v8 = *(float *)*m * v28;
            else
              v8 = -*(float *)*m * v28;
            *(float *)(v21 + 4) = v8;
          }
          else
          {
            if ( *v24 <= 0.0 )
              v7 = -*(float *)(*m + 8) * v28;
            else
              v7 = *(float *)(*m + 8) * v28;
            *(float *)(v21 + 4) = v7;
          }
          *(float *)(v21 + 8) = -*(float *)(*m + 4) * v23;
          if ( *(_DWORD *)(v21 + 20) == *(_DWORD *)(v26 + 64) )
            v12 = 0;
          else
            v12 = *(_DWORD *)(v21 + 20);
          v21 = v12;
          if ( m[5] == *((_DWORD *)v24 + 16) )
            v13 = nullptr;
          else
            v13 = (_DWORD *)m[5];
        }
      }
    }
  }
  if ( v33 )
    rf_solid_destroy((char *)v33, 1);
}

