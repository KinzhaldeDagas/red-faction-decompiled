// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00531500 rf_geomod_coplanar_fragment_classify_from_adjacency
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Thiscall face,UNUSED worldDWORD RET4 ALbool. Return0 if globalspatial classifier enabled or face metadata bit0x08000000 clear. For each original oriented corner edge A->B, nested scans of A.incidence32 then B.incidence32 find pointer-identical opposite-operand terrain-eligible faces; does NOT require edge adjacency on neighbor. Count MATCH ENTRIES, not unique face pointers: first setsneighbor1, secondneighbor2, thirdreturns0 immediately. An edge with fewer than2 moves to next edge; first EXACT2 edge stops search. Compute current face corner mean. If centroid is epsilon-coplanar(class2) with first neighbor and projected containment true, set class4 when dot(normals)<0 OR
// unorderedNaN, else class3 (raw TEST AH,1 treats unordered as negative),return1. Else test second neighbor identically. If neither contains and BOTH side classifiers1, setclass1; if BOTH3 setclass2;otherwise return0 with class unchanged. No raycast/flood fill, distance weighting, full-face polygon overlap or manifold guarantee; duplicates may select same face twice.
char __thiscall rf_geomod_coplanar_fragment_classify_from_adjacency(_DWORD *this, int a2)
{
  BOOL v3; // esi
  BOOL v4; // esi
  int *v5; // [esp+4h] [ebp-44h]
  __int16 *v7; // [esp+Ch] [ebp-3Ch]
  __int16 *v8; // [esp+10h] [ebp-38h]
  int k; // [esp+14h] [ebp-34h]
  char v10; // [esp+1Bh] [ebp-2Dh]
  int j; // [esp+1Ch] [ebp-2Ch]
  int *i; // [esp+20h] [ebp-28h]
  int v13; // [esp+24h] [ebp-24h]
  int v14; // [esp+28h] [ebp-20h]
  int v15; // [esp+2Ch] [ebp-1Ch]
  int v16; // [esp+30h] [ebp-18h]
  __int16 *v17; // [esp+34h] [ebp-14h]
  __int16 *v18; // [esp+38h] [ebp-10h]
  float v19[3]; // [esp+3Ch] [ebp-Ch] BYREF

  if ( rf_geomod_spatial_classifier_enabled )
    return 0;
  if ( !rf_geomod_face_flag_08000000_is_set(this + 10) )
    return 0;
  for ( i = (int *)*(this + 16); ; i = v5 )
  {
    if ( !i )
      return 0;
    v16 = *i;
    v15 = *(_DWORD *)i[5];
    v17 = nullptr;
    v18 = nullptr;
    v10 = 0;
    for ( j = 0; j < rf_receiver_get_first_dword((void *)(v16 + 32)); ++j )
    {
      v8 = *(__int16 **)sub_552200((_DWORD *)(v16 + 32), j);
      v3 = rf_geomod_face_operand_get((_DWORD *)v8 + 10);
      if ( v3 != rf_geomod_face_operand_get(this + 10) && rf_geomod_terrain_component_face_eligible(v8 + 20) )
      {
        for ( k = 0; k < rf_receiver_get_first_dword((void *)(v15 + 32)); ++k )
        {
          v7 = *(__int16 **)sub_552200((_DWORD *)(v15 + 32), k);
          v4 = rf_geomod_face_operand_get((_DWORD *)v7 + 10);
          if ( v4 != rf_geomod_face_operand_get(this + 10)
            && rf_geomod_terrain_component_face_eligible(v7 + 20)
            && v8 == v7 )
          {
            if ( v10 )
              return 0;
            if ( v17 )
            {
              if ( !v18 )
              {
                v18 = v8;
                v10 = 1;
              }
            }
            else
            {
              v17 = v8;
            }
          }
        }
      }
    }
    if ( v10 )
      break;
    if ( i[5] == *(this + 16) )
      v5 = nullptr;
    else
      v5 = (int *)i[5];
  }
  rf_vector3_default_construct_noop(v19);
  rf_geomod_face_centroid(this, v19);
  v13 = rf_geomod_point_classify_against_face_plane(v19, v17);
  if ( v13 == 2 && rf_geomod_face_contains_projected_point(v17, (int)v19) )
  {
    if ( rf_vector_dot((float *)this, (float *)v17) < 0.0 )
      rf_geomod_face_boolean_class_set(this + 10, 4);
    else
      rf_geomod_face_boolean_class_set(this + 10, 3);
    return 1;
  }
  else
  {
    v14 = rf_geomod_point_classify_against_face_plane(v19, v18);
    if ( v14 == 2 && rf_geomod_face_contains_projected_point(v18, (int)v19) )
    {
      if ( rf_vector_dot((float *)this, (float *)v18) < 0.0 )
        rf_geomod_face_boolean_class_set(this + 10, 4);
      else
        rf_geomod_face_boolean_class_set(this + 10, 3);
      return 1;
    }
    else if ( v13 == 1 && v14 == 1 )
    {
      rf_geomod_face_boolean_class_set(this + 10, 1);
      return 1;
    }
    else if ( v13 == 3 && v14 == 3 )
    {
      rf_geomod_face_boolean_class_set(this + 10, 2);
      return 1;
    }
    else
    {
      return 0;
    }
  }
}

