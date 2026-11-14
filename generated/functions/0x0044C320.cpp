// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044C320 rf_hud_world_target_brackets_render
// UNREALRED VERIFIED [hud-world-targets] Renders switch-clutter target brackets after player status and before countdown. It applies trigger range, behind-camera, staggered occlusion, projection, exact pulse/segment constants, and green/red eligibility state.
_DWORD *__cdecl rf_hud_world_target_brackets_render(int a1)
{
  _DWORD *result; // eax
  float *v2; // eax
  double v3; // st7
  char is_obstructed; // al
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // [esp+10h] [ebp-1A4h]
  float *v15; // [esp+10h] [ebp-1A4h]
  float v16; // [esp+14h] [ebp-1A0h]
  float v17; // [esp+18h] [ebp-19Ch]
  float v18; // [esp+1Ch] [ebp-198h]
  float v19; // [esp+20h] [ebp-194h]
  float v20; // [esp+24h] [ebp-190h]
  float v21; // [esp+28h] [ebp-18Ch]
  float v22; // [esp+2Ch] [ebp-188h]
  float v23; // [esp+30h] [ebp-184h]
  float v24; // [esp+34h] [ebp-180h]
  int v25; // [esp+38h] [ebp-17Ch]
  int v26; // [esp+3Ch] [ebp-178h] BYREF
  int v27; // [esp+40h] [ebp-174h] BYREF
  float v28[3]; // [esp+44h] [ebp-170h] BYREF
  float v29[3]; // [esp+50h] [ebp-164h] BYREF
  float v30[3]; // [esp+5Ch] [ebp-158h] BYREF
  float v31[3]; // [esp+68h] [ebp-14Ch] BYREF
  float v32[3]; // [esp+74h] [ebp-140h] BYREF
  float v33[3]; // [esp+80h] [ebp-134h] BYREF
  float v34[3]; // [esp+8Ch] [ebp-128h] BYREF
  float v35[3]; // [esp+98h] [ebp-11Ch] BYREF
  float scaled_result[3]; // [esp+A4h] [ebp-110h] BYREF
  float sum_result[3]; // [esp+B0h] [ebp-104h] BYREF
  float v38[3]; // [esp+BCh] [ebp-F8h] BYREF
  float v39[3]; // [esp+C8h] [ebp-ECh] BYREF
  float copy_result[3]; // [esp+D4h] [ebp-E0h] BYREF
  float out_vector[3]; // [esp+E0h] [ebp-D4h] BYREF
  char v42[72]; // [esp+ECh] [ebp-C8h] BYREF
  int *v43; // [esp+134h] [ebp-80h]
  int v44; // [esp+138h] [ebp-7Ch] BYREF
  int first_dword; // [esp+13Ch] [ebp-78h]
  float v46; // [esp+140h] [ebp-74h]
  char v47; // [esp+146h] [ebp-6Eh]
  char v48; // [esp+147h] [ebp-6Dh]
  float v49; // [esp+148h] [ebp-6Ch]
  float v50; // [esp+14Ch] [ebp-68h]
  float v51[3]; // [esp+150h] [ebp-64h] BYREF
  char v52[40]; // [esp+15Ch] [ebp-58h] BYREF
  int v53; // [esp+184h] [ebp-30h]
  float v54; // [esp+188h] [ebp-2Ch] BYREF
  float v55; // [esp+18Ch] [ebp-28h] BYREF
  float v56; // [esp+190h] [ebp-24h] BYREF
  int i; // [esp+194h] [ebp-20h]
  float v58; // [esp+198h] [ebp-1Ch]
  _DWORD *v59; // [esp+19Ch] [ebp-18h]
  float destination[3]; // [esp+1A0h] [ebp-14h] BYREF
  float v61; // [esp+1ACh] [ebp-8h] BYREF
  int v62; // [esp+1B0h] [ebp-4h]

  result = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  v59 = result;
  if ( result )
  {
    rf_vector3_default_construct_noop(destination);
    rf_solid_collision_result_construct_noop((int)v52);
    v62 = SLODWORD(flt_18092A0[16]) % 3;
    for ( i = 0; ; ++i )
    {
      result = (_DWORD *)i;
      if ( i >= rf_hud_world_target_count )
        return result;
      v53 = rf_object_resolve_handle(rf_hud_world_target_object_uids[4 * i]);
      if ( v53 )
      {
        first_dword = rf_receiver_get_first_dword((void *)v53);
        if ( first_dword )
        {
          if ( *(_BYTE *)(first_dword + 353) )
          {
            v2 = rf_vector_subtract((const float *)(v53 + 60), out_vector, (const float *)v59 + 501);
            rf_vector_copy(destination, copy_result, v2);
            rf_vector_normalize_reciprocal_sqrt(destination);
            v58 = rf_vector_dot(destination, (float *)v59 + 510);
            v3 = v58;
            if ( v58 >= 0.0 )
            {
              v43 = (int *)rf_trigger_find_by_uid(rf_hud_world_target_trigger_uids[4 * i]);
              if ( v43 )
              {
                v25 = v43[165];
                if ( v25 )
                  v47 = v25 == 1 ? rf_trigger_volume_contains_entity((int)v43, (int)v59) : 0;
                else
                  v47 = rf_trigger_sphere_contains_entity(v3, (int)v43, (int)v59);
                if ( v47 )
                {
                  if ( i % 3 == v62 )
                  {
                    rf_physics_hit_record_construct_noop(v42);
                    is_obstructed = rf_geometry_segment_is_obstructed(v53 + 60, (int)(v59 + 501), 1, (int)v42);
                    rf_hud_world_target_occlusion_bytes[16 * i] = is_obstructed;
                  }
                  if ( rf_hud_world_target_occlusion_bytes[16 * i] != 1 )
                  {
                    v48 = rf_renderer_project_world_point_screen_dispatch(v53 + 60, (int)&v55, (int)&v56);
                    if ( v48 )
                    {
                      v5 = rf_vector_multiply_scalar((const float *)v59 + 18, scaled_result, *(float *)(v53 + 120));
                      v14 = rf_vector_multiply_scalar(v5, v35, 0.60000002);
                      v6 = rf_vector_multiply_scalar((const float *)v59 + 21, v39, *(float *)(v53 + 120));
                      v7 = rf_vector_multiply_scalar(v6, v38, 0.60000002);
                      v8 = rf_vector_add((const float *)(v53 + 60), sum_result, v7);
                      rf_vector_add(v8, v51, v14);
                      v48 = rf_renderer_project_world_point_screen_dispatch((int)v51, (int)&v54, (int)&v61);
                      if ( !v48 )
                      {
                        v9 = rf_vector_multiply_scalar((const float *)v59 + 18, v31, *(float *)(v53 + 120));
                        v15 = rf_vector_multiply_scalar(v9, v30, 0.60000002);
                        v10 = rf_vector_multiply_scalar((const float *)v59 + 21, v34, *(float *)(v53 + 120));
                        v11 = rf_vector_multiply_scalar(v10, v33, 0.60000002);
                        v12 = rf_vector_subtract((const float *)(v53 + 60), v32, v11);
                        v13 = rf_vector_subtract(v12, v29, v15);
                        rf_vector_copy(v51, v28, v13);
                        v48 = rf_renderer_project_world_point_screen_dispatch((int)v51, (int)&v54, (int)&v61);
                        if ( !v48 )
                          continue;
                        v54 = (v55 - v54) * 2.0 + v54;
                        v61 = (v56 - v61) * 2.0 + v61;
                      }
                      v24 = rf_hud_world_target_pulse_frequency * unk_6FC42C;
                      v46 = rf_sin_float(v24) * rf_hud_world_target_pulse_amplitude;
                      v54 = v54 + v46;
                      v61 = v61 - v46;
                      v49 = v54 - (v54 - v55) * 2.0;
                      v50 = v61 - (v61 - v56) * 2.0;
                      rf_render_color_set_rgba8(32, 192, 32, 255);
                      rf_render_state_pack(&v44, 0, 0, 0, 1, 0, 0);
                      if ( rf_replicator_is_armed(&rf_hud_world_target_red_deadlines[4 * i]) )
                      {
                        if ( rf_replicator_has_elapsed(&rf_hud_world_target_red_deadlines[4 * i]) )
                        {
                          rf_replicator_reset(&rf_hud_world_target_red_deadlines[4 * i]);
                        }
                        else
                        {
                          rf_render_color_set_rgba8(192, 32, 32, 128);
                          v44 = *rf_render_state_pack(&v27, 0, 0, 0, 3, 0, 0);
                        }
                      }
                      if ( !v43 || !rf_trigger_activation_eligible(v43, v59, 1) )
                      {
                        rf_render_color_set_rgba8(192, 32, 32, 128);
                        v44 = *rf_render_state_pack(&v26, 0, 0, 0, 3, 0, 0);
                      }
                      v23 = (v54 - v49) * 0.2000000029802322 + v49;
                      rf_renderer_draw_screen_line_clipped(v49, v61, v23, v61, v44);
                      v22 = v54 - (v54 - v49) * 0.2000000029802322;
                      rf_renderer_draw_screen_line_clipped(v54, v61, v22, v61, v44);
                      v21 = (v50 - v61) * 0.2000000029802322 + v61;
                      rf_renderer_draw_screen_line_clipped(v54, v61, v54, v21, v44);
                      v20 = v50 - (v50 - v61) * 0.2000000029802322;
                      rf_renderer_draw_screen_line_clipped(v54, v50, v54, v20, v44);
                      v19 = v54 - (v54 - v49) * 0.2000000029802322;
                      rf_renderer_draw_screen_line_clipped(v54, v50, v19, v50, v44);
                      v18 = (v54 - v49) * 0.2000000029802322 + v49;
                      rf_renderer_draw_screen_line_clipped(v49, v50, v18, v50, v44);
                      v17 = (v54 - v49) * 0.2000000029802322 + v61;
                      rf_renderer_draw_screen_line_clipped(v49, v61, v49, v17, v44);
                      v16 = v50 - (v54 - v49) * 0.2000000029802322;
                      rf_renderer_draw_screen_line_clipped(v49, v50, v49, v16, v44);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return result;
}

