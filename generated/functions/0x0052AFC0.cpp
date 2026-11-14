// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052AFC0 rf_geomod_boolean_stage_0_merge
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl destinationSolid,cutterSolid,optionalTranslation,optionalMatrix,scale,optionalDeformVector1,optionalDeformVector2, void. NULL operands or identical pointers skip ALL work. Clear solidDWORD880 forboth,globalD4B7E8=0. Spatialenabled: existing destinationroot0 copies rootbounds0/12 into opposing-bounds globalsD4C53C/D4B91C and setsD4B8FC=1; missingroot allocate andsetflag0. Spatialdisabled: finalize destinationbounds72/84,copy to thoseglobals,setflag1. Reset pair count/head/tail sentinel WITHOUT freeing old nodes. Walk destinationfaces112 clearbit27,operandbit23=0,class0; if room68 exists mirror roomBYTE0 into metadata bit8 (roomless retainsbit8). Walk cutterfaces
// clearbit27,setoperand1,class0; store original facecountsD4B8F4/F8. For each cuttervertex120: matrix-transform ifprovided elsecopy; scale ONLY ORDERED scale>PEdouble0.00009999999747378752 (zero/negative/NaN skip); add translation ifprovided. Optional deformation enabled only vector1 nonNULL and not exactzero; normalization returns raw lengths with helperfallback. Denominator=GLOBAL cutterD4B7C8.radius96 * GLOBAL scaleD4B8E8, not simply formalarguments. Vector2 considered only when firstenabled. After translation, normalized point-translation direction is computed ONCE; for each normalized deform normal whose ordered dot>0, project CURRENT point onto plane throughtranslation, replace with projection+normal*(distanceToPlane/denominator*originalVectorLength). Second test reuses original radial direction even after first deformation; no divide-zero/finite guard. Build cutter
// transformedboundsD4C530/D4B910 from firstpoint theninclude; append NEWvertex to destination, store mappingpointer at originalcuttervertex28. Empty cuttervertexcount leaves prior globalbounds then expands them +/-F32epsilon. Allocate temporary cutterrootD4B90C ifspatialenabled elseNULL. Copy each cutterface into destination with flag1 using mappings; nonNULLcopy spatial-list append/rootowner72 assigned. Finalize/buildtemporaryroot whenenabled. Does not move/destroy source cutterfaces/vertices, finalize destinationbounds at end or roll back failures.
void __cdecl rf_geomod_boolean_stage_0_merge(
        void **a1,
        void **a2,
        float *plane_point,
        float *a4,
        float a5,
        float *source,
        float *a7)
{
  int first_dword; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float v14; // [esp+Ch] [ebp-14Ch]
  float v15; // [esp+10h] [ebp-148h]
  float v16[3]; // [esp+14h] [ebp-144h] BYREF
  float v17[3]; // [esp+20h] [ebp-138h] BYREF
  float v18[3]; // [esp+2Ch] [ebp-12Ch] BYREF
  float v19[3]; // [esp+38h] [ebp-120h] BYREF
  int v20[3]; // [esp+44h] [ebp-114h] BYREF
  float v21[3]; // [esp+50h] [ebp-108h] BYREF
  float sum_result[3]; // [esp+5Ch] [ebp-FCh] BYREF
  int v23[3]; // [esp+68h] [ebp-F0h] BYREF
  float v24[3]; // [esp+74h] [ebp-E4h] BYREF
  float v25[3]; // [esp+80h] [ebp-D8h] BYREF
  float v26[3]; // [esp+8Ch] [ebp-CCh] BYREF
  float v27[3]; // [esp+98h] [ebp-C0h] BYREF
  float v28[3]; // [esp+A4h] [ebp-B4h] BYREF
  float v29[3]; // [esp+B0h] [ebp-A8h] BYREF
  float v30[3]; // [esp+BCh] [ebp-9Ch] BYREF
  float v31[3]; // [esp+C8h] [ebp-90h] BYREF
  float copy_result[3]; // [esp+D4h] [ebp-84h] BYREF
  int v33; // [esp+E0h] [ebp-78h]
  float lhs[3]; // [esp+E4h] [ebp-74h] BYREF
  float v35; // [esp+F0h] [ebp-68h]
  float output[3]; // [esp+F4h] [ebp-64h] BYREF
  float v37; // [esp+100h] [ebp-58h]
  float out_vector[3]; // [esp+104h] [ebp-54h] BYREF
  float point[3]; // [esp+110h] [ebp-48h] BYREF
  float *v40; // [esp+11Ch] [ebp-3Ch]
  float v41; // [esp+120h] [ebp-38h]
  _DWORD *i; // [esp+124h] [ebp-34h]
  int v43; // [esp+128h] [ebp-30h]
  char v44; // [esp+12Fh] [ebp-29h]
  float normal[3]; // [esp+130h] [ebp-28h] BYREF
  float destination[3]; // [esp+13Ch] [ebp-1Ch] BYREF
  int v47; // [esp+148h] [ebp-10h]
  int j; // [esp+14Ch] [ebp-Ch]
  float v49; // [esp+150h] [ebp-8h]
  float length; // [esp+154h] [ebp-4h]

  if ( a1 && a2 && a1 != a2 )
  {
    a1[220] = nullptr;
    a2[220] = nullptr;
    unk_D4B7E8 = 0;
    if ( rf_geomod_spatial_classifier_enabled )
    {
      if ( *a1 )
      {
        rf_vector_copy(&flt_D4C53C, copy_result, (const float *)*a1);
        rf_vector_copy(&flt_D4B91C, v31, (const float *)*a1 + 3);
        unk_D4B8FC = 1;
      }
      else
      {
        *a1 = rf_geomod_spatial_node_allocate();
        unk_D4B8FC = 0;
      }
    }
    else
    {
      rf_solid_finalize_bounds((float *)a1);
      rf_vector_copy(&flt_D4C53C, v30, (const float *)a1 + 18);
      rf_vector_copy(&flt_D4B91C, v29, (const float *)a1 + 21);
      unk_D4B8FC = 1;
    }
    rf_geomod_candidate_pair_count = 0;
    rf_geomod_candidate_pair_list_tail = &rf_geomod_candidate_pair_list_sentinel;
    rf_geomod_candidate_pair_list_head = (int)&rf_geomod_candidate_pair_list_sentinel;
    v47 = 0;
    v43 = 0;
    for ( i = (_DWORD *)rf_receiver_get_first_dword(a1 + 28); i; i = (_DWORD *)rf_solid_face_next_link((int)i) )
    {
      rf_geomod_face_set_boolean_scratch_bit27(i + 10, 0);
      rf_geomod_face_set_operand_exact_one(i + 10, 0);
      rf_geomod_face_boolean_class_set(i + 10, 0);
      if ( i[17] )
      {
        if ( unknown_libname_11((void *)i[17]) )
        {
          if ( !rf_face_metadata_has_flag8(i + 10) )
            i[10] |= 8u;
        }
        else if ( rf_face_metadata_has_flag8(i + 10) )
        {
          i[10] &= ~8u;
        }
      }
      ++v47;
    }
    for ( i = (_DWORD *)rf_receiver_get_first_dword(a2 + 28); i; i = (_DWORD *)rf_solid_face_next_link((int)i) )
    {
      rf_geomod_face_set_boolean_scratch_bit27(i + 10, 0);
      rf_geomod_face_set_operand_exact_one(i + 10, 1);
      rf_geomod_face_boolean_class_set(i + 10, 0);
      ++v43;
    }
    unk_D4B8F4 = v47;
    unk_D4B8F8 = v43;
    v44 = 0;
    v41 = 0.0;
    rf_vector3_set_components_return_destination(normal, 0.0, 0.0, 0.0);
    rf_vector3_set_components_return_destination(destination, 0.0, 0.0, 0.0);
    length = 0.0;
    v49 = 0.0;
    if ( source )
    {
      if ( !rf_vector3_is_exact_zero(source) )
      {
        v44 = 1;
        v41 = *(float *)(unk_D4B7C8 + 96) * unk_D4B8E8;
        rf_vector_copy(normal, v28, source);
        length = rf_vector_normalize_get_length(normal);
        if ( a7 )
        {
          if ( !rf_vector3_is_exact_zero(a7) )
          {
            rf_vector_copy(destination, v27, a7);
            v49 = rf_vector_normalize_get_length(destination);
          }
        }
      }
    }
    for ( j = 0; ; ++j )
    {
      first_dword = rf_receiver_get_first_dword(a2 + 30);
      if ( j >= first_dword )
        break;
      v40 = *(float **)sub_552200(a2 + 30, j);
      rf_vector3_default_construct_noop(point);
      if ( a4 )
      {
        v8 = rf_matrix3_rotate_vector(v40, v26, a4);
        rf_vector_copy(point, v25, v8);
      }
      else
      {
        rf_vector_copy(point, v24, v40);
      }
      if ( a5 > 0.00009999999747378752 )
        rf_vector3_scale_in_place_return_self(point, a5);
      if ( plane_point )
      {
        rf_vector_accumulate(point, plane_point);
        if ( v44 == 1 )
        {
          rf_vector_subtract(point, out_vector, plane_point);
          rf_vector_normalize(out_vector);
          if ( rf_vector_dot(out_vector, normal) > 0.0 )
          {
            rf_vector3_default_construct_noop(output);
            rf_point_project_to_plane(output, point, normal, plane_point);
            v37 = rf_vector_distance(output, point);
            v15 = v37 / v41 * length;
            v9 = rf_vector_scale((float *)v23, v15, normal);
            v10 = rf_vector_add(output, sum_result, v9);
            rf_vector_copy(point, v21, v10);
          }
          if ( rf_vector_dot(out_vector, destination) > 0.0 )
          {
            rf_vector3_default_construct_noop(lhs);
            rf_point_project_to_plane(lhs, point, destination, plane_point);
            v35 = rf_vector_distance(lhs, point);
            v14 = v35 / v41 * v49;
            v11 = rf_vector_scale((float *)v20, v14, destination);
            v12 = rf_vector_add(lhs, v19, v11);
            rf_vector_copy(point, v18, v12);
          }
        }
      }
      if ( j )
      {
        rf_aabb_include_point_min_else_max(&flt_D4C530, &flt_D4B910, point);
      }
      else
      {
        rf_vector_copy(&flt_D4C530, v17, point);
        rf_vector_copy(&flt_D4B910, v16, point);
      }
      v13 = rf_solid_vertex_copy_append(a1, point);
      *((_DWORD *)v40 + 7) = v13;
    }
    rf_vector3_subtract_scalar_in_place(&flt_D4C530, 0.000099999997);
    rf_vector3_add_scalar_in_place(&flt_D4B910, 0.000099999997);
    if ( rf_geomod_spatial_classifier_enabled )
      dword_D4B90C = (char *)rf_geomod_spatial_node_allocate();
    else
      dword_D4B90C = nullptr;
    for ( i = (_DWORD *)rf_receiver_get_first_dword(a2 + 28); i; i = (_DWORD *)rf_solid_face_next_link((int)i) )
    {
      v33 = rf_geomod_face_copy_to_output(i, a1, (int)a2, 1u);
      if ( v33 && rf_geomod_spatial_classifier_enabled )
      {
        rf_geomod_spatial_node_face_list_append((int *)dword_D4B90C + 6, v33);
        *(_DWORD *)(v33 + 72) = dword_D4B90C;
      }
    }
    if ( rf_geomod_spatial_classifier_enabled )
    {
      rf_geomod_spatial_node_finalize_bounds((float *)dword_D4B90C);
      rf_geomod_spatial_tree_build_recursive(dword_D4B90C, 0);
    }
  }
}

