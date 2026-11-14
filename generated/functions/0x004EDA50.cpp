// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EDA50 rf_player_render_thermal_weapon_screen
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, thermal renderer x87 branches, native stack aliases, localization pool writes and skin-profile selection): Cdecl player; returned AL is branch/helper residue, not a uniform success flag. Assumes nonNULL player, resolves entity handle20; missing entity returns0. Negative selected weapon676 or missing mask0x800 in weapon DWORD612 sets player counter4236=2 and returns; attached vehicle/turret predicates any nonzero do likewise. No selected-weapon upper-bound or local-player equality check. If global66301C nonzero, same weapon4240 increments32-bit counter4236, changed weapon updates4240 and sets counter2; signed counter<2 skips, otherwise counter=0. Global0 renders without throttle updates. Local nine-float orientation is EBP-34h..-14h: decompiler vector at EBP-1Ch is its initialized THIRD ROW, not an uninitialized
// independent vector. If model52 nonNULL and node64!=-1, composes node world transform from player orientation4084/position4120; subtracts forward row times2 for shoulder cannon,1 otherwise. Else copies matrix and position from camera196 referenced entity, without backward shift. Viewport64x64 for shoulder cannon,64x48 otherwise; clears black and sets projection45,flags1,1. Entity ring head68211C/sentinel681E90,next652: skips own entity and inactive predicate AL exactly1. Requires normalized direction dot forward>=double0.17000000178813934 OR unordered; radius120>=distance OR unordered substitutes float0.001, otherwise subtracts radius. Requires effective distance<=13 OR unordered. Attenuation=float(1-distance*global float87FBD0), value=float(entity class660 float5092*attenuation); value>=0 OR unordered passes. Corpse ring sentinel681AF8,next652 requires corpse float688>=0 OR unordered;
// same dot/range/value gates but uses CENTER distance without radius subtraction, intensity688 and class index672,stride5396. Both map finite values0..20 to paletteA*(value/20),20..100 to A+(B-A)*((value-20)/80),>100 to B+(255-B)*((value-100)/30); each interpolation fraction rounded float, conversion via __ftol2_sse, A=bytes87FBC8..CA,B=87FBCC..CE. No upper clamp; final RGBA helper stores low bytes. Unordered value reaches explicit RGB0 branch. LOD loop reads class threshold5052+4*j BEFORE signed count5048 check, increments while ordered threshold<scaled distance and j<count; then increments once more if j<count-1. Unordered threshold/distance stops loop. Constructs options,flags11,LOD j,RGBA at+12; renders model128 at position60/orientation72, marks anyDraw regardless of delegate outcome. No world/occlusion trace here. If anyDraw OR signed bitmap4232<0, draws white interlace663018
// at64x64, binds screen material and captures64x64 shoulder/64x48 otherwise into EXISTING bitmap4232 passed by value; clears byte4228=0. Negative bitmap does not allocate a new handle. Else, only if byte4228==0, fills black64x64, binds screen, captures64x64 EVEN for nonshoulder viewport64x48, sets4228=1. Does not restore viewport/projection/render color.
char __cdecl rf_player_render_thermal_weapon_screen(int a1)
{
  int v1; // eax
  const float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float v9[3]; // [esp+54h] [ebp-1D4h] BYREF
  float v10[3]; // [esp+60h] [ebp-1C8h] BYREF
  float v11[3]; // [esp+6Ch] [ebp-1BCh] BYREF
  float v12[3]; // [esp+78h] [ebp-1B0h] BYREF
  float out_vector[3]; // [esp+84h] [ebp-1A4h] BYREF
  float scaled_result[3]; // [esp+90h] [ebp-198h] BYREF
  float copy_result[3]; // [esp+9Ch] [ebp-18Ch] BYREF
  char v16[12]; // [esp+A8h] [ebp-180h] BYREF
  char v17[36]; // [esp+B4h] [ebp-174h] BYREF
  float v18; // [esp+D8h] [ebp-150h]
  float v19; // [esp+DCh] [ebp-14Ch]
  float v20; // [esp+E0h] [ebp-148h]
  float v21; // [esp+E4h] [ebp-144h]
  float v22[3]; // [esp+E8h] [ebp-140h] BYREF
  int v23; // [esp+F4h] [ebp-134h]
  float v24; // [esp+F8h] [ebp-130h]
  float v25; // [esp+FCh] [ebp-12Ch]
  float v26; // [esp+100h] [ebp-128h]
  int v27; // [esp+104h] [ebp-124h]
  int v28; // [esp+108h] [ebp-120h]
  int m; // [esp+10Ch] [ebp-11Ch]
  _DWORD v30[3]; // [esp+110h] [ebp-118h] BYREF
  _BYTE v31[68]; // [esp+11Ch] [ebp-10Ch] BYREF
  float v32; // [esp+160h] [ebp-C8h]
  float v33; // [esp+164h] [ebp-C4h]
  float v34; // [esp+168h] [ebp-C0h]
  float v35; // [esp+16Ch] [ebp-BCh]
  float v36[3]; // [esp+170h] [ebp-B8h] BYREF
  int v37; // [esp+17Ch] [ebp-ACh]
  float v38; // [esp+180h] [ebp-A8h]
  float v39; // [esp+184h] [ebp-A4h]
  float v40; // [esp+188h] [ebp-A0h]
  int v41; // [esp+18Ch] [ebp-9Ch]
  int v42; // [esp+190h] [ebp-98h]
  int j; // [esp+194h] [ebp-94h]
  _DWORD v44[3]; // [esp+198h] [ebp-90h] BYREF
  _BYTE v45[68]; // [esp+1A4h] [ebp-84h] BYREF
  float lhs[3]; // [esp+1E8h] [ebp-40h] BYREF
  float v47[6]; // [esp+1F4h] [ebp-34h] BYREF
  float vector[3]; // [esp+20Ch] [ebp-1Ch] BYREF
  int i; // [esp+218h] [ebp-10h]
  char v50; // [esp+21Fh] [ebp-9h]
  int k; // [esp+220h] [ebp-8h]
  int v52; // [esp+224h] [ebp-4h]

  v1 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  v52 = v1;
  if ( !v1 )
    return v1;
  if ( *(int *)(v52 + 676) < 0 || (unk_912264[340 * *(_DWORD *)(v52 + 676)] & 0x800) == 0 )
  {
    *(_DWORD *)(a1 + 4236) = 2;
    LOBYTE(v1) = a1;
    return v1;
  }
  LOBYTE(v1) = rf_entity_has_attached_use_vehicle(v52);
  if ( (_BYTE)v1 || (LOBYTE(v1) = rf_entity_has_attached_use_turret(v52), (_BYTE)v1) )
  {
    *(_DWORD *)(a1 + 4236) = 2;
    return v1;
  }
  if ( byte_66301C )
  {
    if ( *(_DWORD *)(v52 + 676) == *(_DWORD *)(a1 + 4240) )
    {
      v1 = *(_DWORD *)(a1 + 4236) + 1;
      *(_DWORD *)(a1 + 4236) = v1;
    }
    else
    {
      v1 = *(_DWORD *)(v52 + 676);
      *(_DWORD *)(a1 + 4240) = v1;
      *(_DWORD *)(a1 + 4236) = 2;
    }
    if ( *(int *)(a1 + 4236) < 2 )
      return v1;
    *(_DWORD *)(a1 + 4236) = 0;
  }
  rf_matrix3_construct((char *)v47);
  rf_vector3_default_construct_noop(lhs);
  if ( *(_DWORD *)(a1 + 52) && *(_DWORD *)(a1 + 64) != -1 )
  {
    rf_vmesh_compose_prop_world_transform(
      *(_DWORD *)(a1 + 52),
      *(_DWORD *)(a1 + 64),
      (float *)(a1 + 4084),
      a1 + 4120,
      (int)v47,
      lhs);
    if ( *(_DWORD *)(v52 + 676) == rf_weapon_id_shoulder_cannon )
    {
      v4 = rf_vector_multiply_scalar(vector, scaled_result, 2.0);
      v5 = rf_vector_subtract(lhs, out_vector, v4);
      rf_vector_copy(lhs, v12, v5);
    }
    else
    {
      v6 = rf_vector_multiply_scalar(vector, v11, 1.0);
      v7 = rf_vector_subtract(lhs, v10, v6);
      rf_vector_copy(lhs, v9, v7);
    }
  }
  else
  {
    v2 = (const float *)rf_entity_view_copy_referenced_matrix_2016((int)v17, *(_DWORD **)(a1 + 196));
    rf_matrix3_copy(v47, v2);
    v3 = rf_entity_view_copy_referenced_position((float *)v16, *(_DWORD *)(a1 + 196));
    rf_vector_copy(lhs, copy_result, v3);
  }
  if ( *(_DWORD *)(v52 + 676) == rf_weapon_id_shoulder_cannon )
    rf_renderer_set_viewport_and_relative_clip(0, 0, 64, 64);
  else
    rf_renderer_set_viewport_and_relative_clip(0, 0, 64, 48);
  rf_render_color_set_rgba8(0, 0, 0, 255);
  rf_renderer_clear_color_backend_dispatch();
  rf_renderer_set_camera_projection_dispatch((int)v47, (int)lhs, 45.0, 1, 1);
  v50 = 0;
  for ( i = dword_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
  {
    if ( i != v52 && !rf_object_has_respawn_inactive_flag(i) )
    {
      rf_vector_subtract((const float *)(i + 60), v36, lhs);
      rf_vector_normalize_reciprocal_sqrt(v36);
      if ( rf_vector_dot(vector, v36) >= 0.1700000017881393 )
      {
        v39 = rf_vector_distance((const float *)(i + 60), lhs);
        v39 = *(float *)(i + 120) >= (double)v39 ? 0.001 : v39 - *(float *)(i + 120);
        if ( v39 <= 13.0 )
        {
          v35 = 1.0 - v39 * unk_87FBD0;
          v40 = *(float *)(*(_DWORD *)(i + 660) + 5092) * v35;
          if ( v40 >= 0.0 )
          {
            if ( v40 <= 100.0 )
            {
              if ( v40 <= 20.0 )
              {
                if ( v40 < 0.0 )
                {
                  v42 = 0;
                  v41 = 0;
                  v37 = 0;
                }
                else
                {
                  v32 = (v40 - 0.0) / 20.0;
                  v37 = (int)((double)unk_87FBC8 * v32);
                  v41 = (int)((double)unk_87FBC9 * v32);
                  v42 = (int)((double)unk_87FBCA * v32);
                }
              }
              else
              {
                v33 = (v40 - 20.0) / 80.0;
                v37 = unk_87FBC8 + (int)((double)(unk_87FBCC - unk_87FBC8) * v33);
                v41 = unk_87FBC9 + (int)((double)(unk_87FBCD - unk_87FBC9) * v33);
                v42 = unk_87FBCA + (int)((double)(unk_87FBCE - unk_87FBCA) * v33);
              }
            }
            else
            {
              v34 = (v40 - 100.0) / 30.0;
              v37 = unk_87FBCC + (int)((double)(255 - unk_87FBCC) * v34);
              v41 = unk_87FBCD + (int)((double)(255 - unk_87FBCD) * v34);
              v42 = unk_87FBCE + (int)((double)(255 - unk_87FBCE) * v34);
            }
            v38 = rf_renderer_lod_distance_scaled((const float *)(i + 60));
            for ( j = 0;
                  *(float *)(*(_DWORD *)(i + 660) + 4 * j + 5052) < (double)v38
               && j < *(_DWORD *)(*(_DWORD *)(i + 660) + 5048);
                  ++j )
            {
              ;
            }
            if ( j < *(_DWORD *)(*(_DWORD *)(i + 660) + 5048) - 1 )
              ++j;
            rf_model_render_options_construct((char *)v44);
            v44[0] = 11;
            v44[1] = j;
            rf_color4_set_bytes_return_destination(v45, v37, v41, v42, 255);
            rf_model_handle_render_all_adapter(*(_DWORD *)(i + 128), i + 60, i + 72, (int)v44);
            v50 = 1;
          }
        }
      }
    }
  }
  for ( k = rf_corpse_list_head; (_UNKNOWN *)k != &unk_681AF8; k = *(_DWORD *)(k + 652) )
  {
    if ( *(float *)(k + 688) >= 0.0 )
    {
      rf_vector_subtract((const float *)(k + 60), v22, lhs);
      rf_vector_normalize_reciprocal_sqrt(v22);
      if ( rf_vector_dot(vector, v22) >= 0.1700000017881393 )
      {
        v25 = rf_vector_distance((const float *)(k + 60), lhs);
        if ( v25 <= 13.0 )
        {
          v21 = 1.0 - v25 * unk_87FBD0;
          v26 = *(float *)(k + 688) * v21;
          if ( v26 >= 0.0 )
          {
            if ( v26 <= 100.0 )
            {
              if ( v26 <= 20.0 )
              {
                if ( v26 < 0.0 )
                {
                  v28 = 0;
                  v27 = 0;
                  v23 = 0;
                }
                else
                {
                  v18 = (v26 - 0.0) / 20.0;
                  v23 = (int)((double)unk_87FBC8 * v18);
                  v27 = (int)((double)unk_87FBC9 * v18);
                  v28 = (int)((double)unk_87FBCA * v18);
                }
              }
              else
              {
                v19 = (v26 - 20.0) / 80.0;
                v23 = unk_87FBC8 + (int)((double)(unk_87FBCC - unk_87FBC8) * v19);
                v27 = unk_87FBC9 + (int)((double)(unk_87FBCD - unk_87FBC9) * v19);
                v28 = unk_87FBCA + (int)((double)(unk_87FBCE - unk_87FBCA) * v19);
              }
            }
            else
            {
              v20 = (v26 - 100.0) / 30.0;
              v23 = unk_87FBCC + (int)((double)(255 - unk_87FBCC) * v20);
              v27 = unk_87FBCD + (int)((double)(255 - unk_87FBCD) * v20);
              v28 = unk_87FBCE + (int)((double)(255 - unk_87FBCE) * v20);
            }
            v24 = rf_renderer_lod_distance_scaled((const float *)(k + 60));
            for ( m = 0;
                  unk_684904[1349 * *(_DWORD *)(k + 672) + m] < (double)v24
               && m < unk_684900[1349 * *(_DWORD *)(k + 672)];
                  ++m )
            {
              ;
            }
            if ( m < unk_684900[1349 * *(_DWORD *)(k + 672)] - 1 )
              ++m;
            rf_model_render_options_construct((char *)v30);
            v30[0] = 11;
            v30[1] = m;
            rf_color4_set_bytes_return_destination(v31, v23, v27, v28, 255);
            rf_model_handle_render_all_adapter(*(_DWORD *)(k + 128), k + 60, k + 72, (int)v30);
            v50 = 1;
          }
        }
      }
    }
  }
  if ( v50 || *(int *)(a1 + 4232) < 0 )
  {
    rf_render_color_set_rgba8(255, 255, 255, 255);
    rf_bitmap_blit_subrectangle_backend_dispatch(dword_663018, 0, 0, 64, 64, 0, 0, 64, 64, 0, 0, unk_187CD38);
    rf_renderer_get_backend_code();
    rf_player_bind_weapon_screen_material(a1);
    if ( *(_DWORD *)(v52 + 676) == rf_weapon_id_shoulder_cannon )
      LOBYTE(v1) = rf_bitmap_capture_backbuffer_into_bitmap(0, 0, 64, 64, *(_DWORD *)(a1 + 4232));
    else
      LOBYTE(v1) = rf_bitmap_capture_backbuffer_into_bitmap(0, 0, 64, 48, *(_DWORD *)(a1 + 4232));
    *(_BYTE *)(a1 + 4228) = 0;
  }
  else
  {
    LOBYTE(v1) = *(_BYTE *)(a1 + 4228);
    if ( !(_BYTE)v1 )
    {
      rf_render_color_set_rgba8(0, 0, 0, 255);
      rf_renderer_fill_rectangle_clipped(0, 0, 64, 64, dword_182ABB8);
      rf_renderer_get_backend_code();
      rf_player_bind_weapon_screen_material(a1);
      LOBYTE(v1) = rf_bitmap_capture_backbuffer_into_bitmap(0, 0, 64, 64, *(_DWORD *)(a1 + 4232));
      *(_BYTE *)(a1 + 4228) = 1;
    }
  }
  return v1;
}

