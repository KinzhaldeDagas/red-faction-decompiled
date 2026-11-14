// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00537980 rf_solid_build_lightmap_face_clusters
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, lightmap clusters, tile mapping, atlas placement, seam blend snapshots, recovered halfplanes and original PE bytes): Thiscall solid,density float,unusedDWORD,optionalBegin(groupCount),optionalPerGroup(). Resets global1425E8C;sets face DWORD+44=FFFFFFFF INTEGER marker (float-plane pointer causes misleading NaN pseudocode),WORD lightmap index+54=-1. Allocates seed-plane16B,group-countDWORD,owner-keyDWORD arrays sized global15A6B28;no group-capacity/NULL checks. Eligible faces require flags40&2025==0. If grouping flag15A6B37 set,each unassigned eligible face seeds plane/current owner keyFace68. Breadth-first frontier finds candidate faces occurring at least twice among current face vertices incident-face arrays AND same owner key,not unique edge-pair proof. Unassigned candidate joins iff
// dot(candidateNormal,seedNormal)>threshold15A6B2C,abs(Dcandidate-Dseed)<0.001,and groupSize<15A6B40. Already assigned candidate may move to new group if normal dot improves AND plane-offset distance improves,with size cap;this branch uses relative tests,not original fixed thresholds. Counts old/new groups adjusted,seeds unchanged;no dedup/queue cycle validation beyond assigned IDs/comparisons. Grouping disabled assigns one eligible face per group. A later eligibility-only loop has no side effects. Begin callback once with final group count. For every group (including one emptied by reassignment),rescans all faces into pointer list,allocates124-byte registered descriptor536740,configures via536B40 using seed plane/density,sums returned texel areas,calls per-group callback. Updates decal lightmap UVs,then deletes temporary arrays,returns sum. Group face IDs start0 independently of existing
// descriptor list index assigned by constructor;no existing-list clear or index reconciliation here. Third stackDWORD unused,callbacks do not supply status. Mutates source faces/world arrays before completion,no rollback or tile-allocation failure handling.
int __thiscall rf_solid_build_lightmap_face_clusters(
        char *this,
        float a2,
        int a3,
        void (__cdecl *a4)(int),
        void (*a5)(void))
{
  int first_dword; // eax
  int v6; // eax
  int v7; // eax
  int *v9; // [esp+8h] [ebp-C8h]
  float v10; // [esp+Ch] [ebp-C4h]
  float v11; // [esp+10h] [ebp-C0h]
  float v12; // [esp+14h] [ebp-BCh]
  _DWORD *v13; // [esp+18h] [ebp-B8h]
  float *v14; // [esp+1Ch] [ebp-B4h]
  int *v16; // [esp+30h] [ebp-A0h]
  char *v17; // [esp+40h] [ebp-90h]
  int v18; // [esp+48h] [ebp-88h]
  int v19[4]; // [esp+4Ch] [ebp-84h] BYREF
  float v20; // [esp+5Ch] [ebp-74h]
  float v21; // [esp+60h] [ebp-70h]
  float v22; // [esp+64h] [ebp-6Ch]
  float v23; // [esp+68h] [ebp-68h]
  float v24; // [esp+6Ch] [ebp-64h]
  float v25; // [esp+70h] [ebp-60h]
  float *v26; // [esp+74h] [ebp-5Ch]
  int v27; // [esp+78h] [ebp-58h]
  void *v28[3]; // [esp+7Ch] [ebp-54h] BYREF
  int v29; // [esp+88h] [ebp-48h]
  _DWORD *j; // [esp+8Ch] [ebp-44h]
  void *v31[3]; // [esp+90h] [ebp-40h] BYREF
  void *v32[3]; // [esp+9Ch] [ebp-34h] BYREF
  int v33; // [esp+A8h] [ebp-28h]
  float *v34; // [esp+ACh] [ebp-24h]
  _DWORD *v35; // [esp+B0h] [ebp-20h]
  float *v36; // [esp+B4h] [ebp-1Ch]
  float *i; // [esp+B8h] [ebp-18h]
  int v38; // [esp+BCh] [ebp-14h]
  int k; // [esp+C0h] [ebp-10h]
  int v40; // [esp+CCh] [ebp-4h]

  unk_1425E8C = 0;
  v38 = 0;
  for ( i = (float *)rf_receiver_get_first_dword(this + 112); i; i = (float *)rf_solid_face_next_link((int)i) )
    i[11] = NAN;
  for ( i = (float *)rf_receiver_get_first_dword(this + 112); i; i = (float *)rf_solid_face_next_link((int)i) )
    *((_WORD *)i + 27) = -1;
  v33 = 0;
  v18 = unk_15A6B28;
  v17 = (char *)operator new(16 * unk_15A6B28);
  v40 = 0;
  if ( v17 )
  {
    rf_vector_construct_no_unwind(v17, 0x10u, v18, rf_vector_prefix_construct_noop);
    v14 = (float *)v17;
  }
  else
  {
    v14 = nullptr;
  }
  v40 = -1;
  v34 = v14;
  v35 = operator new(4 * unk_15A6B28);
  v36 = (float *)operator new(4 * unk_15A6B28);
  if ( unk_15A6B37 )
  {
    for ( i = (float *)rf_receiver_get_first_dword(this + 112); i; i = (float *)rf_solid_face_next_link((int)i) )
    {
      if ( *((__int16 *)i + 27) == -1 && rf_flags_test_2025_clear((_DWORD *)i + 10) )
      {
        rf_dword_array_construct_capacity(v32, 0);
        v40 = 1;
        *((_WORD *)i + 27) = v33;
        rf_pointer_array_append_dword(v32, (int)i);
        rf_plane_copy(&v34[4 * v33], i);
        v35[v33] = 1;
        v36[v33] = i[17];
        while ( rf_receiver_get_first_dword(v32) > 0 )
        {
          v29 = *(_DWORD *)sub_552200(v32, 0);
          rf_pointer_array_erase_index_unchecked(v32, 0);
          rf_dword_array_construct_capacity(v28, 0);
          LOBYTE(v40) = 2;
          rf_dword_array_construct_capacity(v31, 0);
          LOBYTE(v40) = 3;
          for ( j = *(_DWORD **)(v29 + 64); j; j = v13 )
          {
            for ( k = 0; ; ++k )
            {
              first_dword = rf_receiver_get_first_dword((void *)(*j + 32));
              if ( k >= first_dword )
                break;
              v27 = *(_DWORD *)sub_552200((_DWORD *)(*j + 32), k);
              if ( *(_DWORD *)(v27 + 68) == LODWORD(v36[v33]) )
              {
                if ( rf_pointer_array_count_matches(v28, v27) )
                {
                  if ( !rf_pointer_array_count_matches(v31, v27) )
                    rf_pointer_array_append_dword(v31, v27);
                }
                else
                {
                  rf_pointer_array_append_dword(v28, v27);
                }
              }
            }
            if ( j[5] == *(_DWORD *)(v29 + 64) )
              v13 = nullptr;
            else
              v13 = (_DWORD *)j[5];
          }
          for ( k = 0; ; ++k )
          {
            v6 = rf_receiver_get_first_dword(v31);
            if ( k >= v6 )
              break;
            v26 = *(float **)sub_552200(v31, k);
            if ( rf_flags_test_2025_clear((_DWORD *)v26 + 10) )
            {
              if ( *((__int16 *)v26 + 27) == -1 )
              {
                v24 = rf_plane_normal_alignment_negative_dot(v26, &v34[4 * v33]);
                v12 = fabs(v26[3] - v34[4 * v33 + 3]);
                v25 = v12;
                if ( v24 < -unk_15A6B2C && v25 < 0.001 && v35[v33] < unk_15A6B40 )
                {
                  *((_WORD *)v26 + 27) = v33;
                  rf_pointer_array_append_dword(v32, (int)v26);
                  ++v35[*((__int16 *)v26 + 27)];
                }
              }
              else if ( *((__int16 *)v26 + 27) != v33 )
              {
                v20 = rf_plane_normal_alignment_negative_dot(v26, &v34[4 * v33]);
                v11 = fabs(v26[3] - v34[4 * v33 + 3]);
                v23 = v11;
                v21 = rf_plane_normal_alignment_negative_dot(v26, &v34[4 * *((__int16 *)v26 + 27)]);
                v10 = fabs(v26[3] - v34[4 * *((__int16 *)v26 + 27) + 3]);
                v22 = v10;
                if ( v20 < (double)v21 && v22 > (double)v23 && v35[v33] < unk_15A6B40 )
                {
                  --v35[*((__int16 *)v26 + 27)];
                  *((_WORD *)v26 + 27) = v33;
                  rf_pointer_array_append_dword(v32, (int)v26);
                  ++v35[*((__int16 *)v26 + 27)];
                }
              }
            }
          }
          LOBYTE(v40) = 2;
          rf_pointer_array_destroy_backing_storage(v31);
          LOBYTE(v40) = 1;
          rf_pointer_array_destroy_backing_storage(v28);
        }
        ++v33;
        v40 = -1;
        rf_pointer_array_destroy_backing_storage(v32);
      }
    }
  }
  else
  {
    for ( i = (float *)rf_receiver_get_first_dword(this + 112); i; i = (float *)rf_solid_face_next_link((int)i) )
    {
      if ( rf_flags_test_2025_clear((_DWORD *)i + 10) )
      {
        *((_WORD *)i + 27) = v33;
        rf_plane_copy(&v34[4 * v33], i);
        v35[v33++] = 1;
      }
    }
  }
  for ( i = (float *)rf_receiver_get_first_dword(this + 112); i; i = (float *)rf_solid_face_next_link((int)i) )
    rf_flags_test_2025_clear((_DWORD *)i + 10);
  if ( a4 )
    a4(v33);
  for ( k = 0; k < v33; ++k )
  {
    rf_dword_array_construct_capacity(v19, 0);
    v40 = 4;
    for ( i = (float *)rf_receiver_get_first_dword(this + 112); i; i = (float *)rf_solid_face_next_link((int)i) )
    {
      if ( *((__int16 *)i + 27) == k )
        rf_pointer_array_append_dword(v19, (int)i);
    }
    v16 = (int *)operator new(0x7Cu);
    LOBYTE(v40) = 5;
    if ( v16 )
      v9 = rf_lightmap_descriptor124_construct_register(v16, (int)this);
    else
      v9 = nullptr;
    LOBYTE(v40) = 4;
    v19[3] = (int)v9;
    v7 = rf_lightmap_descriptor_configure_faces((int)v9, (int)this, v19, &v34[4 * k], a2);
    v38 += v7;
    if ( a5 )
      a5();
    v40 = -1;
    rf_pointer_array_destroy_backing_storage((void **)v19);
  }
  rf_world_decal_update_lightmap_uvs();
  operator delete(v34);
  operator delete(v35);
  operator delete(v36);
  return v38;
}

