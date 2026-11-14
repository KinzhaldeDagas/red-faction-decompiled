// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041B2A0 rf_glare_line_of_sight_with_caches
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, glare visibility/reflection and cached-query initialization, native flags/x87 gates and static ownership): Cdecl(glare,viewPoint), returns AL1 for clear,0 for blocked; mutates mixed DWORD cache fields. Old fresh pseudocode inferred a const-float receiver despite raw native writes; saved second-argument int is corrected to view-point pointer while retaining the two-DWORD cdecl ABI. First resolves cached model UID+656 (unless -1); a still-occluding model returns0, otherwise clears UID to -1. Next tests cached MOVING-SOLID POINTER+660 directly, requiring common flags0x10 and segment/AABB overlap, inverse-transforming both endpoints into mover frame and sweeping solid+660. IMPORTANT: this cached-mover sweep precedes initialization of query pose+4/+16,radius+76 and flags+80; constructor only zeroed face hint+0, so cached
// branch passes unwritten stack fields to0x52F8D0, which reads flags/pose/radius. Positive hit count returns0 and retains cache; otherwise pointer+660=0. Only afterward initializes identity query pose, zero translation/radius, flags5 plus0x80 when global BYTE680AE5 nonzero. Uses viewPoint->glarePos displacement and seeds query face hint from nonzero cached face+664. World-solid hit stores result face+36 to glare+664 and returns0; miss DOES NOT clear that cache. Then scans moving-solid list0x704BCC/sentinel704940 in link+652 order, filters mask0x10/AABB, inverse-transforms endpoints and reuses query including flags/radius/face hint; first positive hit stores mover pointer+660, returns0. If global local entity681E38 exists, scans entity list68211C/sentinel681E90 in source order, requiring same room DWORD0 and excluding attached-use-vehicle candidates plus local entity resolved vehicle owner.
// First model occluder caches candidate UID+44 at+656 and returns0. Finally tests resolved glare owner+48 through model predicate, caching UID if blocked, else returns1. No closest-hit selection, raw cached-pointer lifetime validation, null view/glare guard, face-hint reset between solid queries or rollback; world core also mutates global collision scratch/cache serial.
char __cdecl rf_glare_line_of_sight_with_caches(_DWORD *glare, float *view_point)
{
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  int v10; // eax
  _DWORD *v11; // eax
  float v12[3]; // [esp+0h] [ebp-228h] BYREF
  float v13[3]; // [esp+Ch] [ebp-21Ch] BYREF
  float v14[3]; // [esp+18h] [ebp-210h] BYREF
  float v15[3]; // [esp+24h] [ebp-204h] BYREF
  float v16[3]; // [esp+30h] [ebp-1F8h] BYREF
  float v17[3]; // [esp+3Ch] [ebp-1ECh] BYREF
  float v18[3]; // [esp+48h] [ebp-1E0h] BYREF
  float v19[3]; // [esp+54h] [ebp-1D4h] BYREF
  float v20[3]; // [esp+60h] [ebp-1C8h] BYREF
  float v21[3]; // [esp+6Ch] [ebp-1BCh] BYREF
  float v22[3]; // [esp+78h] [ebp-1B0h] BYREF
  float v23[3]; // [esp+84h] [ebp-1A4h] BYREF
  float v24[3]; // [esp+90h] [ebp-198h] BYREF
  float v25[3]; // [esp+9Ch] [ebp-18Ch] BYREF
  float v26[3]; // [esp+A8h] [ebp-180h] BYREF
  float copy_result[3]; // [esp+B4h] [ebp-174h] BYREF
  float out_vector[3]; // [esp+C0h] [ebp-168h] BYREF
  int first_dword; // [esp+CCh] [ebp-15Ch]
  _DWORD *j; // [esp+D0h] [ebp-158h]
  _DWORD *v31; // [esp+D4h] [ebp-154h]
  float destination[3]; // [esp+D8h] [ebp-150h] BYREF
  _DWORD v33[10]; // [esp+E4h] [ebp-144h] BYREF
  float rhs[3]; // [esp+10Ch] [ebp-11Ch] BYREF
  int v35; // [esp+118h] [ebp-110h] BYREF
  float v36[3]; // [esp+11Ch] [ebp-10Ch] BYREF
  float v37[9]; // [esp+128h] [ebp-100h] BYREF
  float v38[3]; // [esp+14Ch] [ebp-DCh] BYREF
  float v39[4]; // [esp+158h] [ebp-D0h] BYREF
  int v40; // [esp+168h] [ebp-C0h]
  _BYTE v41[32]; // [esp+188h] [ebp-A0h] BYREF
  char v42[108]; // [esp+1A8h] [ebp-80h] BYREF
  float v43[3]; // [esp+214h] [ebp-14h] BYREF
  int i; // [esp+220h] [ebp-8h]
  _DWORD *v45; // [esp+224h] [ebp-4h]

  rf_solid_collision_query_construct_clear_face_hint((char *)&v35);
  rf_solid_collision_result_construct_noop((int)v33);
  rf_model_collision_query_construct_noop(v42);
  rf_model_collision_result_construct_noop((int)v41);
  rf_vector3_default_construct_noop(v43);
  if ( glare[164] != -1 )
  {
    v31 = (_DWORD *)rf_object_resolve_handle(glare[164]);
    if ( v31 && rf_glare_model_occludes_segment(v31, (int)glare, (int)view_point) )
      return 0;
    glare[164] = -1;
  }
  rf_vector3_default_construct_noop(rhs);
  rf_vector3_default_construct_noop(destination);
  if ( glare[165] )
  {
    i = glare[165];
    if ( (*(_DWORD *)(i + 124) & 0x10) != 0
      && rf_segment_intersects_aabb((float *)(i + 400), (float *)(i + 412), (float *)glare + 15, view_point, v43) )
    {
      v3 = rf_vector_subtract(view_point, out_vector, (const float *)(i + 60));
      rf_vector_copy(rhs, copy_result, v3);
      rf_matrix3_inverse_rotate_vector(rhs, (float *)(i + 72));
      v4 = rf_vector_subtract((const float *)glare + 15, v26, (const float *)(i + 60));
      rf_vector_copy(destination, v25, v4);
      rf_matrix3_inverse_rotate_vector(destination, (float *)(i + 72));
      rf_vector_copy(v38, v24, rhs);
      v5 = rf_vector_subtract(destination, v23, rhs);
      rf_vector_copy(v39, v22, v5);
      rf_world_collision_sweep(*(char **)(i + 660), (int)&v35, (int)v33, 1);
      if ( v33[0] > 0 )
        return 0;
    }
    glare[165] = 0;
  }
  rf_identity_orientation_matrix(v37);
  rf_vector3_zero_return_destination(v36);
  v39[3] = 0.0;
  v40 = 5;
  if ( unk_680AE5 )
    v40 |= 0x80u;
  rf_vector_copy(v38, v21, view_point);
  v6 = rf_vector_subtract((const float *)glare + 15, v20, view_point);
  rf_vector_copy(v39, v19, v6);
  if ( glare[166] )
    v35 = glare[166];
  rf_world_collision_sweep((char *)rf_world_solid, (int)&v35, (int)v33, 1);
  if ( v33[0] <= 0 )
  {
    for ( i = unk_704BCC; (_UNKNOWN *)i != &unk_704940; i = *(_DWORD *)(i + 652) )
    {
      if ( (*(_DWORD *)(i + 124) & 0x10) != 0
        && rf_segment_intersects_aabb((float *)(i + 400), (float *)(i + 412), (float *)glare + 15, view_point, v43) )
      {
        v7 = rf_vector_subtract(view_point, v18, (const float *)(i + 60));
        rf_vector_copy(rhs, v17, v7);
        rf_matrix3_inverse_rotate_vector(rhs, (float *)(i + 72));
        v8 = rf_vector_subtract((const float *)glare + 15, v16, (const float *)(i + 60));
        rf_vector_copy(destination, v15, v8);
        rf_matrix3_inverse_rotate_vector(destination, (float *)(i + 72));
        rf_vector_copy(v38, v14, rhs);
        v9 = rf_vector_subtract(destination, v13, rhs);
        rf_vector_copy(v39, v12, v9);
        rf_world_collision_sweep(*(char **)(i + 660), (int)&v35, (int)v33, 1);
        if ( v33[0] > 0 )
        {
          glare[165] = i;
          return 0;
        }
      }
    }
    if ( dword_681E38 )
    {
      first_dword = rf_receiver_get_first_dword((void *)dword_681E38);
      for ( j = (_DWORD *)unk_68211C; j != (_DWORD *)&unk_681E90; j = (_DWORD *)j[163] )
      {
        v10 = rf_receiver_get_first_dword(j);
        if ( first_dword == v10 && !rf_entity_has_attached_use_vehicle((int)j) )
        {
          if ( !rf_entity_has_attached_use_vehicle(dword_681E38)
            || (v11 = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(dword_681E38 + 512)), j != v11) )
          {
            if ( rf_glare_model_occludes_segment(j, (int)glare, (int)view_point) )
            {
              glare[164] = j[11];
              return 0;
            }
          }
        }
      }
    }
    v45 = (_DWORD *)rf_object_resolve_handle(glare[12]);
    if ( v45 && rf_glare_model_occludes_segment(v45, (int)glare, (int)view_point) )
    {
      glare[164] = v45[11];
      return 0;
    }
    else
    {
      return 1;
    }
  }
  else
  {
    glare[166] = v33[9];
    return 0;
  }
}

