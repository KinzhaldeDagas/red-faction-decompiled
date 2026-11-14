// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051A2B0 rf_solid_clone_with_optional_vertex_welding
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): Allocates888-byte solid. ALWAYS qsorts ORIGINAL all-vertex array120 in place by X coordinate when nonempty, even when weld byte0. Builds clone vertex map in ORIGINAL Vertex28 scratch DWORDs. With weld enabled, scans earlier sorted vertices within per-axis <=~1e-4 and strict squared distance<9.999999051046871e-9, merging only when51A760 all-incident-flag8 boolean matches; copies prior mapped pointer, otherwise creates clone vertex. No weld creates distinct clone per source vertex. Resizes clone selected-vertex204 and selected-face216 counts to originals; writes mapped pointers at original selection indices (first occurrence lookup), so welded selections can retain duplicate pointers. Copies every original face through
// face-copy helper and fills selected-face correspondences. Clones UV-scroll descriptors from array756 by bit-copy key0, velocity4/8, rebuilds clone face cache; finalizes clone bounds. No allocation/failure rollback; modifies original order and scratch even though returning separate solid.
void **__thiscall rf_solid_clone_with_optional_vertex_welding(char *this, char a2)
{
  void *v2; // eax
  void *v3; // eax
  int v4; // eax
  const float **v5; // eax
  int *v6; // eax
  char v7; // al
  int v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  void *v12; // eax
  int v13; // eax
  size_t first_dword; // [esp-4h] [ebp-94h]
  float *v16; // [esp+Ch] [ebp-84h]
  float v17; // [esp+10h] [ebp-80h]
  float v18; // [esp+14h] [ebp-7Ch]
  float v19; // [esp+18h] [ebp-78h]
  float *v20; // [esp+1Ch] [ebp-74h]
  void *v22; // [esp+24h] [ebp-6Ch]
  void **v23; // [esp+2Ch] [ebp-64h]
  float *v24; // [esp+38h] [ebp-58h]
  int v25; // [esp+3Ch] [ebp-54h]
  int v26; // [esp+40h] [ebp-50h]
  float v27; // [esp+44h] [ebp-4Ch]
  float out_vector[3]; // [esp+48h] [ebp-48h] BYREF
  float v29; // [esp+54h] [ebp-3Ch]
  int j; // [esp+58h] [ebp-38h]
  char have_flag8; // [esp+5Fh] [ebp-31h]
  int index; // [esp+60h] [ebp-30h]
  float rhs[3]; // [esp+64h] [ebp-2Ch] BYREF
  float *v34; // [esp+70h] [ebp-20h]
  _DWORD *k; // [esp+74h] [ebp-1Ch]
  void **v36; // [esp+78h] [ebp-18h]
  int i; // [esp+7Ch] [ebp-14h]
  int v38; // [esp+80h] [ebp-10h]
  int v39; // [esp+8Ch] [ebp-4h]

  v23 = (void **)operator new(0x378u);
  v39 = 0;
  if ( v23 )
    v20 = (float *)rf_solid888_construct(v23);
  else
    v20 = nullptr;
  v39 = -1;
  v36 = (void **)v20;
  if ( rf_receiver_get_first_dword(this + 120) > 0 )
  {
    first_dword = rf_receiver_get_first_dword(this + 120);
    v2 = (void *)sub_552200((_DWORD *)this + 30, 0);
    qsort(v2, first_dword, 4u, (_CoreCrtNonSecureSearchSortCompareFunction)rf_qsort_vertex_pointer_compare_x);
  }
  v38 = 0;
  v3 = (void *)rf_receiver_get_first_dword(this + 204);
  rf_pointer_array_resize_count_unchecked(v36 + 51, v3);
  for ( i = 0; ; ++i )
  {
    v4 = rf_receiver_get_first_dword(this + 120);
    if ( i >= v4 )
      break;
    v34 = *(float **)sub_552200((_DWORD *)this + 30, i);
    rf_vector3_copy_return_destination(rhs, v34);
    if ( a2 )
    {
      v34[7] = 0.0;
      have_flag8 = rf_vertex_all_incident_faces_have_flag8((int)v34);
      for ( j = v38; j < i; ++j )
      {
        v29 = **(float **)sub_552200((_DWORD *)this + 30, j);
        if ( v29 >= rhs[0] - 0.00009999999747378752 )
        {
          if ( v29 > rhs[0] + 0.00009999999747378752 )
            break;
          v5 = (const float **)sub_552200((_DWORD *)this + 30, j);
          rf_vector_subtract(*v5, out_vector, rhs);
          v19 = fabs(out_vector[0]);
          if ( v19 <= 0.00009999999747378752 )
          {
            v18 = fabs(out_vector[1]);
            if ( v18 <= 0.00009999999747378752 )
            {
              v17 = fabs(out_vector[2]);
              if ( v17 <= 0.00009999999747378752 )
              {
                v27 = rf_vector_length_squared(out_vector);
                if ( v27 < 0.000000009999999051046871 )
                {
                  v6 = (int *)sub_552200((_DWORD *)this + 30, j);
                  v7 = rf_vertex_all_incident_faces_have_flag8(*v6);
                  if ( v7 == have_flag8 )
                  {
                    v8 = sub_552200((_DWORD *)this + 30, j);
                    v34[7] = *(float *)(*(_DWORD *)v8 + 28);
                    break;
                  }
                }
              }
            }
          }
        }
        else
        {
          v38 = j;
        }
      }
      if ( !*((_DWORD *)v34 + 7) )
      {
        v9 = rf_solid_vertex_copy_append(v36, rhs);
        *((_DWORD *)v34 + 7) = v9;
      }
    }
    else
    {
      v10 = rf_solid_vertex_copy_append(v36, rhs);
      *((_DWORD *)v34 + 7) = v10;
    }
    index = rf_pointer_array_find_index((_DWORD *)this + 51, (int)v34);
    if ( index > -1 )
    {
      v11 = (float *)sub_552200(v36 + 51, index);
      *v11 = v34[7];
    }
  }
  v12 = (void *)rf_receiver_get_first_dword(this + 216);
  rf_pointer_array_resize_count_unchecked(v36 + 54, v12);
  for ( k = (_DWORD *)rf_receiver_get_first_dword(this + 112); k; k = (_DWORD *)rf_solid_face_next_link((int)k) )
  {
    v26 = rf_geomod_face_copy_to_output(k, v36, (int)this, 0);
    v25 = rf_pointer_array_find_index((_DWORD *)this + 54, (int)k);
    if ( v25 > -1 )
      *(_DWORD *)sub_552200(v36 + 54, v25) = v26;
  }
  for ( i = 0; ; ++i )
  {
    v13 = rf_receiver_get_first_dword(this + 756);
    if ( i >= v13 )
      break;
    v24 = *(float **)sub_552200((_DWORD *)this + 189, i);
    v22 = operator new(0x18u);
    v39 = 1;
    if ( v22 )
      v16 = (float *)rf_uv_scroll_descriptor_construct_invalid(v22);
    else
      v16 = nullptr;
    v39 = -1;
    rf_pointer_array_append_dword(v36 + 189, (int)v16);
    *v16 = *v24;
    rf_uv_scroll_descriptor_set_velocity(v16, v24[1], v24[2]);
    rf_uv_scroll_descriptor_rebuild_face_cache(v16, (int)v36);
  }
  rf_solid_finalize_bounds((float *)v36);
  return v36;
}

