// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041A300 rf_glare_render_runtime_volumetric_beam
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Cdecl glare. Player-owner+716=0 admits; nonzero requires equality to current player0x87C640, view-wrapper DWORD8==0, common flags+124 mask2 clear and resolved player entity not dead. Resolves common owner+48; admits missing owner, missing room DWORD0, or nonzero room byte+353. Definition pointer+684 is assumed valid. Signed volumetric bitmap+36<0 suppresses draw; otherwise normalizes glarePos-cameraPos, computes acos(dot(glareForward,-direction))*180/pi, then alpha=0.5*(clamp((angle-halfCone)/25,-1,1)+1). Ordered alpha<2/255 suppresses; NaN survives clamp/threshold. Owner class flags+724 mask0x800 with runtime mask2 clear additionally modulates length/height from owner or first attached-entity input
// vector+1812: length<=0.0001 OR unordered suppresses; transformed normalized direction dot ownerForward<0 suppresses, unordered dot proceeds. Length=max(0.3,definitionLength*dot) with ordered lower clamp, then random[-.05,.05]; height=0.3+(definitionHeight-.3)*(length/definitionLength), no zero divisor guard. ALWAYS writes common radius+120=max(defHeight,defLength) after admitted work, even with draw suppressed. Draw enables doubled fog/far helper0x442AE0, sets WHITE RGBA with trunc(alpha*255), sets volumetric texture, submits beam from glarePos+forward*length to glarePos at computed height, then restores configured fog/far via helper0. No previous render-state save, unwind restoration, null current-player guard or local dot clamp.
void __cdecl rf_glare_render_runtime_volumetric_beam(int a1)
{
  float *v1; // eax
  float *v2; // eax
  double v3; // st7
  float *v4; // eax
  float scalar; // [esp+4h] [ebp-E8h]
  float scaled_result[3]; // [esp+8h] [ebp-E4h] BYREF
  char v7[12]; // [esp+14h] [ebp-D8h] BYREF
  float v8[3]; // [esp+20h] [ebp-CCh] BYREF
  float v9[3]; // [esp+2Ch] [ebp-C0h] BYREF
  float copy_result[3]; // [esp+38h] [ebp-B4h] BYREF
  char v11[12]; // [esp+44h] [ebp-A8h] BYREF
  float sum_result[3]; // [esp+50h] [ebp-9Ch] BYREF
  int v13; // [esp+5Ch] [ebp-90h]
  float v14; // [esp+60h] [ebp-8Ch]
  char v15[12]; // [esp+64h] [ebp-88h] BYREF
  int v16; // [esp+70h] [ebp-7Ch]
  float v17; // [esp+74h] [ebp-78h]
  int v18; // [esp+78h] [ebp-74h]
  float destination[3]; // [esp+7Ch] [ebp-70h] BYREF
  float v20; // [esp+88h] [ebp-64h]
  float rhs[3]; // [esp+8Ch] [ebp-60h] BYREF
  float out_vector[3]; // [esp+98h] [ebp-54h] BYREF
  char v23[36]; // [esp+A4h] [ebp-48h] BYREF
  int first_dword; // [esp+C8h] [ebp-24h]
  int v25; // [esp+CCh] [ebp-20h]
  float v26; // [esp+D0h] [ebp-1Ch]
  float v27; // [esp+D4h] [ebp-18h]
  int v28; // [esp+D8h] [ebp-14h]
  int v29; // [esp+DCh] [ebp-10h]
  char v30; // [esp+E3h] [ebp-9h]
  int v31; // [esp+E4h] [ebp-8h] BYREF
  void *v32; // [esp+E8h] [ebp-4h]

  if ( !*(_DWORD *)(a1 + 716)
    || *(_DWORD *)(a1 + 716) == unk_87C640
    && !rf_view_wrapper_get_dword8(*(_DWORD *)(*(_DWORD *)(a1 + 716) + 196))
    && (*(_DWORD *)(a1 + 124) & 2) == 0
    && (v25 = rf_entity_resolve_handle(*(_DWORD *)(*(_DWORD *)(a1 + 716) + 20)), !rf_entity_is_dead(v25)) )
  {
    v32 = (void *)rf_object_resolve_handle(*(_DWORD *)(a1 + 48));
    if ( !v32 || (first_dword = rf_receiver_get_first_dword(v32)) == 0 || *(_BYTE *)(first_dword + 353) )
    {
      v28 = *(_DWORD *)(a1 + 684);
      v30 = 1;
      *(float *)&v31 = 0.0;
      if ( *(int *)(v28 + 36) < 0 )
      {
        v30 = 0;
      }
      else
      {
        rf_entity_view_copy_referenced_position(rhs, *(_DWORD *)(unk_87C640 + 196));
        rf_entity_view_copy_referenced_matrix_2016((int)v23, *(_DWORD **)(unk_87C640 + 196));
        rf_vector_subtract((const float *)(a1 + 60), out_vector, rhs);
        rf_vector_normalize_reciprocal_sqrt(out_vector);
        v1 = rf_vector_negate(out_vector, (float *)v11);
        scalar = rf_vector_dot((float *)(a1 + 96), v1);
        v20 = rf_acos_float(scalar) * 180.0 / 3.141592741012573;
        *(float *)&v31 = (v20 - *(float *)(v28 + 16)) / 25.0;
        rf_float_clamp_in_place((float *)&v31, -1.0, 1.0);
        *(float *)&v31 = (*(float *)&v31 + 1.0) * 0.5;
        if ( *(float *)&v31 < 0.007843137718737125 )
        {
          *(float *)&v31 = 0.0;
          v30 = 0;
        }
      }
      v26 = *(float *)(v28 + 44);
      v27 = *(float *)(v28 + 40);
      v29 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 48));
      if ( v29 && rf_entity_class_flags724_has_mask800(v29) && !rf_glare_runtime_flags692_has_mask2(a1) )
      {
        v16 = sub_435170(v29);
        v18 = rf_entity_resolve_handle(v16);
        rf_vector3_default_construct_noop(destination);
        rf_vector3_copy_return_destination((float *)v15, (float *)(v29 + 96));
        if ( v18 )
        {
          if ( sub_438AC0(v18) )
            rf_vector_copy(destination, copy_result, (const float *)(v29 + 1812));
          else
            rf_vector_copy(destination, v9, (const float *)(v18 + 1812));
        }
        else
        {
          rf_vector_copy(destination, v8, (const float *)(v29 + 1812));
        }
        v17 = rf_vector3_length(destination);
        if ( v17 <= 0.00009999999747378752 )
        {
          v30 = 0;
        }
        else
        {
          rf_vector_rotate_translate_in_place(destination, v29 + 60, v29 + 72);
          rf_vector_subtract_in_place(destination, (float *)(v29 + 60));
          v2 = (float *)rf_vector3_normalized_copy_unchecked(destination, (int)v7);
          v14 = rf_vector_dot(v2, (float *)v15);
          if ( v14 >= 0.0 )
          {
            v26 = v26 * v14;
            if ( v26 < 0.300000011920929 )
              v26 = 0.30000001;
            v3 = rf_random_float_range(-0.050000001, 0.050000001);
            v26 = v3 + v26;
            v27 = (*(float *)(v28 + 40) - 0.300000011920929) * (v26 / *(float *)(v28 + 44)) + 0.300000011920929;
          }
          else
          {
            v30 = 0;
          }
        }
      }
      *(float *)(a1 + 120) = rf_float_maximum_two_values(*(float *)(v28 + 40), *(float *)(v28 + 44));
      if ( v30 )
      {
        rf_renderer_set_configured_fog_far_for_glare_pass(1);
        v13 = (int)(*(float *)&v31 * 255.0);
        rf_render_color_set_rgba8(255, 255, 255, v13);
        rf_renderer_set_pending_texture_handles(*(_DWORD *)(v28 + 36), -1);
        v4 = rf_vector_multiply_scalar((const float *)(a1 + 96), scaled_result, v26);
        rf_vector_add((const float *)(a1 + 60), sum_result, v4);
        rf_renderer_camera_facing_beam_backend_wrapper(
          sum_result,
          (float *)(a1 + 60),
          v27,
          rf_particle_glow_billboard_render_state);
        rf_renderer_set_configured_fog_far_for_glare_pass(0);
      }
    }
  }
}

