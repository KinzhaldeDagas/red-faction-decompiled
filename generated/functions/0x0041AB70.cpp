// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041AB70 rf_glare_update_fade_and_render_corona
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, glare visibility/reflection and cached-query initialization, native flags/x87 gates and static ownership): Cdecl(glare,localPlayerIndex), no local index/two-slot bound. Returns immediately when definition+12 corona handle is0. Resolves common owner+48 and admits absent owner/room or nonzero room byte+353. Copies full36-byte player view matrix; split locals include initialized forward and right rows. Computes normalized d=glarePos-cameraPos and angle=acos(dot(glareForward,-d))*180/pi without local dot clamp. Occluded defaults true. Only enabled byte+652 allows a visibility query: player pointer+716 nonzero tests its model+52 with transform matrix+4084/position+4120, query radius0/flags1, and no hit clears occlusion. Otherwise active GeoMod clears nonzero cached face+664; only when global DWORD0x18092E0 parity equals
// glare UID+44 parity does0x41B2A0 refresh cached visibility byte+653. Occlusion is inverse of retained byte+653; alternate parity reuses it. Disabled byte652 therefore fades cached values rather than calculating fresh visibility. Occluded path requires BOTH cached alpha+668+4*i and radius+676+4*i ordered >0; <=0 OR unordered suppresses draw without clearing those values. Otherwise decay alpha*0.800000011920929 and radius*0.6000000238418579; if either ordered result<0.05000000074505806, zero both caches and suppress. Visible path: distance D; f=(FOV/2-viewAngle)/(FOV/2); alpha=(f+1)*global6612F8*40/D, optionally attenuated by1-(angle-halfCone)/10 for ordered angle>halfCone, times intensity, clamp[0,1], then average with old alpha. Radius=(sqrt(D)*defDistanceFactor28-defDiminish32)*defRadiusScale24*(f+1)*global6612FC, optionally angle attenuation /20, ordered lower clamp0, then average old
// radius. Tint factor is clamp(((12-D)/D)*intensity*max_literal(f,0)*max_literal((halfCone-angle)/halfCone,0),0,1), squared; ordered positive tint plus RED byte+8 nonzero and player pointer+716==0 calls HUD tint with RGB+8..10 and trunc(tintSquared*64*intensity). Native tests RED three times, not any-RGB. Draw stores caches, grows common radius via max_literal(newRadius,oldRadius), computes roll=(1-f)*0.5 negated only for ordered dot(cameraRight,d)<0, packs state(1,2,3,2,0,3), WHITE/trunc(alpha*255), texture+12. Byte+720 selects padded beam endpoints+724/+736, otherwise position billboard. No division/finite/null-view/index guard, fog adjustment or state restoration; unordered max_literal selects SECOND argument.
void __cdecl rf_glare_update_fade_and_render_corona(_DWORD *glare, int a2)
{
  float *v2; // eax
  float *v3; // eax
  double v4; // st7
  double v5; // st7
  double v6; // st7
  float v7; // [esp+8h] [ebp-154h]
  float v8; // [esp+8h] [ebp-154h]
  float v9; // [esp+Ch] [ebp-150h]
  float v10[3]; // [esp+10h] [ebp-14Ch] BYREF
  float v11[3]; // [esp+1Ch] [ebp-140h] BYREF
  float v12[3]; // [esp+28h] [ebp-134h] BYREF
  float copy_result[3]; // [esp+34h] [ebp-128h] BYREF
  float v14[3]; // [esp+40h] [ebp-11Ch] BYREF
  float v15; // [esp+4Ch] [ebp-110h]
  int v16; // [esp+50h] [ebp-10Ch] BYREF
  float v17; // [esp+54h] [ebp-108h]
  int v18; // [esp+58h] [ebp-104h]
  float v19; // [esp+5Ch] [ebp-100h]
  float v20; // [esp+60h] [ebp-FCh]
  float v21; // [esp+64h] [ebp-F8h]
  int v22; // [esp+68h] [ebp-F4h] BYREF
  _BYTE v23[32]; // [esp+6Ch] [ebp-F0h] BYREF
  float v24[3]; // [esp+8Ch] [ebp-D0h] BYREF
  float v25[9]; // [esp+98h] [ebp-C4h] BYREF
  float destination[3]; // [esp+BCh] [ebp-A0h] BYREF
  float v27[12]; // [esp+C8h] [ebp-94h] BYREF
  int first_dword; // [esp+F8h] [ebp-64h]
  float v29; // [esp+FCh] [ebp-60h]
  int v30; // [esp+100h] [ebp-5Ch]
  float v31; // [esp+104h] [ebp-58h]
  float rhs[3]; // [esp+108h] [ebp-54h] BYREF
  char v33; // [esp+117h] [ebp-45h]
  float out_vector[3]; // [esp+118h] [ebp-44h] BYREF
  float v35[6]; // [esp+124h] [ebp-38h] BYREF
  float v36[3]; // [esp+13Ch] [ebp-20h] BYREF
  float v37; // [esp+148h] [ebp-14h]
  void *v38; // [esp+14Ch] [ebp-10h]
  int v39; // [esp+150h] [ebp-Ch] BYREF
  int v40; // [esp+154h] [ebp-8h]
  bool v41; // [esp+15Bh] [ebp-1h]

  if ( *(_DWORD *)(glare[171] + 12) )
  {
    v30 = glare[171];
    v33 = 1;
    v38 = (void *)rf_object_resolve_handle(glare[12]);
    if ( !v38 || (first_dword = rf_receiver_get_first_dword(v38)) == 0 || *(_BYTE *)(first_dword + 353) )
    {
      *(float *)&v39 = 1.0;
      v29 = 1.0;
      rf_entity_view_copy_referenced_position(rhs, *(_DWORD *)(unk_87C640 + 196));
      rf_entity_view_copy_referenced_matrix_2016((int)v35, *(_DWORD **)(unk_87C640 + 196));
      rf_vector_subtract((const float *)glare + 15, out_vector, rhs);
      rf_vector_normalize_reciprocal_sqrt(out_vector);
      v2 = rf_vector_negate(out_vector, v14);
      v7 = rf_vector_dot((float *)glare + 24, v2);
      v31 = rf_acos_float(v7) * 180.0 / 3.141592741012573;
      v37 = 0.0;
      v41 = 1;
      if ( *((_BYTE *)glare + 652) )
      {
        if ( glare[179] )
        {
          rf_model_collision_query_construct_noop((char *)v24);
          rf_model_collision_result_construct_noop((int)v23);
          rf_vector_copy(destination, copy_result, rhs);
          v3 = rf_vector_subtract((const float *)glare + 15, v12, rhs);
          rf_vector_copy(v27, v11, v3);
          LODWORD(v27[4]) = 1;
          v27[3] = 0.0;
          rf_matrix3_copy(v25, (const float *)(glare[179] + 4084));
          rf_vector_copy(v24, v10, (const float *)(glare[179] + 4120));
          if ( !rf_model_handle_collide_all_adapter(*(_DWORD **)(glare[179] + 52), (int)v24, (int)v23, 1) )
            v41 = 0;
        }
        else
        {
          if ( rf_geomod_boolean_is_active() && glare[166] )
            glare[166] = 0;
          if ( (MEMORY[0x18092E0] & 1) == (glare[11] & 1) )
            *((_BYTE *)glare + 653) = rf_glare_line_of_sight_with_caches(glare, rhs);
          v41 = *((_BYTE *)glare + 653) == 0;
        }
      }
      if ( v41 )
      {
        if ( *(float *)&glare[a2 + 167] <= 0.0 || *(float *)&glare[a2 + 169] <= 0.0 )
        {
          v33 = 0;
        }
        else
        {
          *(float *)&v39 = *(float *)&glare[a2 + 167] * 0.800000011920929;
          v29 = *(float *)&glare[a2 + 169] * 0.6000000238418579;
          if ( *(float *)&v39 < 0.05000000074505806 || v29 < 0.05000000074505806 )
          {
            *(float *)&glare[a2 + 167] = 0.0;
            *(float *)&glare[a2 + 169] = 0.0;
            v33 = 0;
          }
        }
      }
      else
      {
        v19 = rf_vector_distance((const float *)glare + 15, rhs);
        v20 = flt_66157C;
        v8 = rf_vector_dot(v36, out_vector);
        v21 = rf_acos_float(v8) * 180.0 / 3.141592741012573;
        v37 = (v20 * 0.5 - v21) / (v20 * 0.5);
        *(float *)&v39 = 40.0 / v19;
        *(float *)&v39 = (v37 + 1.0) * flt_6612F8 * *(float *)&v39;
        if ( *(float *)(v30 + 16) < (double)v31 )
          *(float *)&v39 = (1.0 - (v31 - *(float *)(v30 + 16)) / 10.0) * *(float *)&v39;
        *(float *)&v39 = *(float *)&v39 * *(float *)(v30 + 20);
        rf_float_clamp_in_place((float *)&v39, 0.0, 1.0);
        *(float *)&v39 = (*(float *)&v39 + *(float *)&glare[a2 + 167]) * 0.5;
        v4 = rf_sqrt_float(v19);
        v29 = v4 * *(float *)(v30 + 28) - *(float *)(v30 + 32);
        v29 = v29 * *(float *)(v30 + 24);
        v29 = (v37 + 1.0) * flt_6612FC * v29;
        if ( *(float *)(v30 + 16) < (double)v31 )
          v29 = (1.0 - (v31 - *(float *)(v30 + 16)) / 20.0) * v29;
        if ( v29 < 0.0 )
          v29 = 0.0;
        v29 = (v29 + *(float *)&glare[a2 + 169]) * 0.5;
        *(float *)&v22 = (12.0 - v19) / v19 * *(float *)(v30 + 20);
        v5 = rf_float_maximum_two_values(v37, 0.0);
        *(float *)&v22 = v5 * *(float *)&v22;
        v9 = (*(float *)(v30 + 16) - v31) / *(float *)(v30 + 16);
        v6 = rf_float_maximum_two_values(v9, 0.0);
        *(float *)&v22 = v6 * *(float *)&v22;
        rf_float_clamp_in_place((float *)&v22, 0.0, 1.0);
        *(float *)&v22 = *(float *)&v22 * *(float *)&v22;
        if ( *(float *)&v22 > 0.0 )
        {
          v18 = (int)(*(float *)&v22 * 64.0 * *(float *)(v30 + 20));
          if ( *(_BYTE *)(v30 + 8) )
          {
            if ( !glare[179] )
              rf_player_hud_screen_tint_set(
                unk_87C640,
                *(_BYTE *)(v30 + 8),
                *(_BYTE *)(v30 + 9),
                *(_BYTE *)(v30 + 10),
                v18);
          }
        }
      }
      v40 = (int)(*(float *)&v39 * 255.0);
      if ( v33 )
      {
        glare[a2 + 167] = v39;
        *(float *)&glare[a2 + 169] = v29;
        *((float *)glare + 30) = rf_float_maximum_two_values(v29, *((float *)glare + 30));
        v15 = (1.0 - v37) * 0.5;
        v17 = rf_vector_dot(v35, out_vector);
        if ( v17 < 0.0 )
          v15 = -v15;
        rf_render_state_pack(&v16, 1, 2, 3, 2, 0, 3);
        rf_render_color_set_rgba8(255, 255, 255, v40);
        rf_renderer_set_pending_texture_handles(*(_DWORD *)(v30 + 12), -1);
        if ( *((_BYTE *)glare + 720) )
          rf_renderer_padded_beam_backend_wrapper((int)(glare + 181), (int)(glare + 184), v29, v16);
        else
          rf_renderer_world_billboard_aspect_backend_dispatch((int)(glare + 15), v15, v29, v16);
      }
    }
  }
}

