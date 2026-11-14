// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052BEE0 rf_geomod_split_candidate_pair
// UNREALRED VERIFIED [finite-pair-20261028] Initial finite extrema overlap uses epsilon then sorted middle endpoints supply common length. Actual division requires common scalar length >=double(float(0.0001)) RF units (0.009999999747378752 cm host). A point touch, sub-epsilon interval or near disjoint gap only marks touch state; endpoint containment / expanded AABB contact alone does not justify dividing. One operand may have a coplanar edge with adjacent endpoint pointers and need no division while the other spans it.
void __cdecl rf_geomod_split_candidate_pair(int *a1, float *a2, float *a3, char a4, int a5)
{
  float *v5; // eax
  float *v6; // eax
  int v7; // [esp+0h] [ebp-37Ch]
  float v8[3]; // [esp+4h] [ebp-378h] BYREF
  float out_vector[3]; // [esp+10h] [ebp-36Ch] BYREF
  float v10; // [esp+1Ch] [ebp-360h]
  float v11; // [esp+20h] [ebp-35Ch]
  int v12; // [esp+24h] [ebp-358h]
  int v13; // [esp+28h] [ebp-354h]
  int kk; // [esp+2Ch] [ebp-350h]
  _DWORD *v15; // [esp+30h] [ebp-34Ch]
  int jj; // [esp+34h] [ebp-348h]
  int *v17; // [esp+38h] [ebp-344h]
  int v18; // [esp+3Ch] [ebp-340h]
  int v19; // [esp+40h] [ebp-33Ch]
  int v20[2]; // [esp+44h] [ebp-338h] BYREF
  int v21; // [esp+4Ch] [ebp-330h] BYREF
  int v23; // [esp+54h] [ebp-328h] BYREF
  int v24; // [esp+58h] [ebp-324h]
  int v25[2]; // [esp+5Ch] [ebp-320h] BYREF
  int v26; // [esp+64h] [ebp-318h] BYREF
  int v28; // [esp+6Ch] [ebp-310h] BYREF
  int n; // [esp+70h] [ebp-30Ch]
  int v30; // [esp+74h] [ebp-308h]
  float *v31; // [esp+78h] [ebp-304h]
  int m; // [esp+7Ch] [ebp-300h]
  int v33; // [esp+80h] [ebp-2FCh]
  int v34; // [esp+84h] [ebp-2F8h]
  int v35; // [esp+88h] [ebp-2F4h]
  int v36; // [esp+8Ch] [ebp-2F0h]
  int v37; // [esp+90h] [ebp-2ECh]
  _DWORD v38[129]; // [esp+94h] [ebp-2E8h] BYREF
  int k; // [esp+298h] [ebp-E4h]
  int *v40; // [esp+29Ch] [ebp-E0h]
  int j; // [esp+2A0h] [ebp-DCh]
  int *v42; // [esp+2A4h] [ebp-D8h]
  int *v43; // [esp+2A8h] [ebp-D4h]
  int *v44; // [esp+2ACh] [ebp-D0h]
  int *v45; // [esp+2B0h] [ebp-CCh]
  int i; // [esp+2B4h] [ebp-C8h]
  int v47; // [esp+2B8h] [ebp-C4h] BYREF
  int v48; // [esp+2BCh] [ebp-C0h]
  int v49; // [esp+2C0h] [ebp-BCh] BYREF
  bool v50; // [esp+2C7h] [ebp-B5h]
  int *v51; // [esp+2C8h] [ebp-B4h]
  _OWORD v52[4]; // [esp+2CCh] [ebp-B0h] BYREF
  float rhs[3]; // [esp+30Ch] [ebp-70h] BYREF
  float v54[3]; // [esp+318h] [ebp-64h] BYREF
  int v55; // [esp+324h] [ebp-58h] BYREF
  int *v56; // [esp+328h] [ebp-54h]
  unsigned int v57; // [esp+32Ch] [ebp-50h]
  float v58[4]; // [esp+330h] [ebp-4Ch] BYREF
  unsigned int v59; // [esp+340h] [ebp-3Ch]
  float v60[4]; // [esp+344h] [ebp-38h] BYREF
  char v61; // [esp+357h] [ebp-25h]
  _DWORD v62[4]; // [esp+358h] [ebp-24h]
  int v63; // [esp+368h] [ebp-14h] BYREF
  float v64; // [esp+36Ch] [ebp-10h]
  int ii; // [esp+370h] [ebp-Ch]
  int v66; // [esp+374h] [ebp-8h] BYREF

  rf_force_sample44_construct_vectors_noop((char *)rhs);
  if ( sub_56BA70(a2, a3, rhs) )
  {
    v55 = 0;
    v59 = sub_5339B0(a2, &v63, &v49, (int)a3, (int)rhs, &v55, 128, (int)rf_geomod_intersection_record_workspace);
    if ( v59 > 1 )
    {
      v57 = sub_5339B0(a3, &v47, &v66, (int)a2, (int)rhs, &v55, 128, (int)rf_geomod_intersection_record_workspace);
      if ( v57 > 1 )
      {
        v50 = 1;
        v61 = 1;
        if ( a4 )
        {
          v50 = rf_geomod_face_operand_get((_DWORD *)a2 + 10) != a5;
          if ( rf_geomod_face_operand_get((_DWORD *)a3 + 10) == a5 )
            v61 = 0;
        }
        rf_vector_prefix_construct_noop(v58);
        rf_vector_prefix_construct_noop(v60);
        rf_plane_copy(v58, a2);
        rf_plane_copy(v60, a3);
        if ( unk_D4B93C[6 * v49] > unk_D4B93C[6 * v47] - 0.00009999999747378752
          && unk_D4B93C[6 * v63] < unk_D4B93C[6 * v66] + 0.00009999999747378752 )
        {
          v56 = nullptr;
          v51 = nullptr;
          v64 = 0.0;
          v42 = &rf_geomod_intersection_record_workspace[6 * v63];
          v43 = &rf_geomod_intersection_record_workspace[6 * v49];
          v44 = &rf_geomod_intersection_record_workspace[6 * v47];
          v45 = &rf_geomod_intersection_record_workspace[6 * v66];
          for ( i = 0; i < 3; ++i )
          {
            for ( j = i; j < 4; ++j )
            {
              if ( *((float *)(&v42)[j] + 5) < (double)*((float *)(&v42)[i] + 5) )
              {
                v40 = (&v42)[i];
                (&v42)[i] = (&v42)[j];
                (&v42)[j] = v40;
              }
            }
          }
          v56 = v43;
          v51 = v44;
          v64 = *((float *)v44 + 5) - *((float *)v43 + 5);
          rf_vector_construct_no_unwind((char *)v52, 0x10u, 4, rf_vector_prefix_construct_noop);
          v48 = 0;
          if ( v64 >= 0.00009999999747378752 )
          {
            for ( k = 0; k < v55; ++k )
              v38[k] = &rf_geomod_intersection_record_workspace[6 * k];
            for ( k = 0; k < v55; ++k )
            {
              if ( *(_DWORD *)(v38[k] + 4) )
              {
                v31 = rf_solid_vertex_copy_append(a1, (float *)(v38[k] + 8));
                if ( a4 )
                  rf_geomod_split_vertex_propagate_to_adjacent_faces(
                    (int)a1,
                    *(_DWORD *)v38[k],
                    *(_DWORD *)(v38[k] + 4),
                    (int)v31,
                    a5);
                else
                  rf_geomod_split_vertex_propagate_to_incident_faces(*(float **)v38[k], *(float **)(v38[k] + 4), v31);
                *(_DWORD *)v38[k] = v31;
                *(_DWORD *)(v38[k] + 4) = 0;
              }
            }
            for ( k = 0; k < v55 - 1; ++k )
            {
              for ( m = k; m < v55; ++m )
              {
                if ( *(float *)(v38[m] + 20) < (double)*(float *)(v38[k] + 20) )
                {
                  v30 = v38[k];
                  v38[k] = v38[m];
                  v38[m] = v30;
                }
              }
            }
            for ( k = 0; k < v55 - 1; ++k )
            {
              for ( m = k + 1; m < v55; ++m )
              {
                if ( *(_DWORD *)v38[k] == *(_DWORD *)v38[m] )
                {
                  for ( n = m; n < v55 - 1; ++n )
                    v38[n] = v38[n + 1];
                  --v55;
                }
              }
            }
            v35 = rf_geomod_intersection_record_index_find(
                    rf_geomod_intersection_record_workspace[6 * v63],
                    v55,
                    (int)v38);
            v33 = rf_geomod_intersection_record_index_find(
                    rf_geomod_intersection_record_workspace[6 * v49],
                    v55,
                    (int)v38);
            v36 = rf_geomod_intersection_record_index_find(
                    rf_geomod_intersection_record_workspace[6 * v47],
                    v55,
                    (int)v38);
            v34 = rf_geomod_intersection_record_index_find(
                    rf_geomod_intersection_record_workspace[6 * v66],
                    v55,
                    (int)v38);
            v37 = 0;
            if ( v59 == 3 && v50 )
            {
              if ( rf_geomod_face_split_between_intersection_vertices((int)a2, (int)a1, v35, v33, (int)v38, &v26, &v28) )
              {
                v24 = 0;
                if ( v26 )
                {
                  v62[v48] = v26;
                  rf_plane_copy((float *)&v52[v48++], v60);
                  v25[v24++] = v26;
                }
                if ( v28 )
                {
                  v62[v48] = v28;
                  rf_plane_copy((float *)&v52[v48++], v60);
                  v25[v24++] = v28;
                }
                ++v37;
                rf_geomod_candidate_pairs_refresh_after_face_split((int)a2, (int)v25, v24);
                rf_solid_face_remove_destroy(a1, a2, 0);
                ++rf_geomod_boolean_split_face_count;
              }
              else
              {
                v62[v48] = a2;
                rf_plane_copy((float *)&v52[v48++], v60);
              }
            }
            else
            {
              v62[v48] = a2;
              rf_plane_copy((float *)&v52[v48++], v60);
            }
            if ( v57 == 3 && v61 )
            {
              if ( rf_geomod_face_split_between_intersection_vertices((int)a3, (int)a1, v36, v34, (int)v38, &v21, &v23) )
              {
                v19 = 0;
                if ( v21 )
                {
                  v62[v48] = v21;
                  rf_plane_copy((float *)&v52[v48++], v58);
                  v20[v19++] = v21;
                }
                if ( v23 )
                {
                  v62[v48] = v23;
                  rf_plane_copy((float *)&v52[v48++], v58);
                  v20[v19++] = v23;
                }
                ++v37;
                rf_geomod_candidate_pairs_refresh_after_face_split((int)a3, (int)v20, v19);
                rf_solid_face_remove_destroy(a1, a3, 0);
                ++rf_geomod_boolean_split_face_count;
              }
              else
              {
                v62[v48] = a3;
                rf_plane_copy((float *)&v52[v48++], v58);
              }
            }
            else
            {
              v62[v48] = a3;
              rf_plane_copy((float *)&v52[v48++], v58);
            }
            for ( ii = 0; ii < v48; ++ii )
            {
              v18 = v62[ii];
              rf_geomod_face_set_boolean_scratch_bit27((unsigned int *)(v18 + 40), 1);
              rf_geomod_face_boolean_class_set((int *)(v18 + 40), 0);
            }
            if ( !a4 )
            {
              for ( ii = 0; ii < v55; ++ii )
              {
                v17 = &rf_geomod_intersection_record_workspace[6 * ii];
                if ( *((float *)v56 + 5) <= (double)*((float *)v17 + 5)
                  && *((float *)v51 + 5) >= (double)*((float *)v17 + 5) )
                {
                  for ( jj = 0; jj < v48; ++jj )
                  {
                    v15 = (_DWORD *)v62[jj];
                    if ( !rf_geomod_face_contains_shared_vertex(v15, *v17) )
                    {
                      for ( kk = v15[16]; kk; kk = v7 )
                      {
                        v13 = rf_geomod_point_classify_against_face_plane(*(const float **)kk, &v52[jj]);
                        v12 = rf_geomod_point_classify_against_face_plane(**(const float ***)(kk + 20), &v52[jj]);
                        if ( v13 == 2 && v12 == 2 )
                        {
                          v5 = rf_vector_subtract(*(const float **)kk, out_vector, rhs);
                          v10 = rf_vector_dot(v5, v54);
                          v6 = rf_vector_subtract(**(const float ***)(kk + 20), v8, rhs);
                          v11 = rf_vector_dot(v6, v54);
                          if ( v10 <= (double)*((float *)v17 + 5) && v11 >= (double)*((float *)v17 + 5) )
                          {
                            rf_geomod_face_edge_split_insert_vertex(
                              v15,
                              *(float **)kk,
                              **(float ***)(kk + 20),
                              (float *)*v17);
                            break;
                          }
                        }
                        if ( *(_DWORD *)(kk + 20) == v15[16] )
                          v7 = 0;
                        else
                          v7 = *(_DWORD *)(kk + 20);
                      }
                    }
                  }
                }
              }
            }
          }
          else
          {
            rf_geomod_face_set_boolean_scratch_bit27((unsigned int *)a2 + 10, 1);
            rf_geomod_face_set_boolean_scratch_bit27((unsigned int *)a3 + 10, 1);
          }
        }
      }
    }
  }
}

