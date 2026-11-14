// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D78B0 rf_d3d8_submit_mesh_faces
// UNREALRED VERIFIED [nonworld-byte-rgb-20260903]: Mesh-face submission consumer for the decoded RGB8 paths. It computes ambient/diffuse vertex bytes with 0x0052A000, requests specular bytes from 0x0052A1E0 when material field +0x84 is positive, and—when that helper's point-hit flag is set—emits a separate pass whose alpha is the arithmetic mean of specular R, G, and B.
// UNREALRED VERIFIED [reflection-uv-20260903]: When material reflection-stage field +0xB4 is positive, computes per-vertex spherical reflection UV with 0x0052A870, copies it to packet offsets +0x1C/+0x20, derives pass alpha from material reflection amount +0x8C times mesh fade, packs state (1,1,0,3,1,0), and submits primitive mode 1.
// UNREALRED VERIFIED [self-illumination-20260903]: After ordinary non-world diffuse lighting, evaluates material self-illumination, computes round(255*value), and raises each vertex RGB byte independently to at least that common floor. Material type 2 then modulates the resulting RGB by its per-channel bytes at +0x09..+0x0B.
// UNREALRED VERIFIED [material-animation-20260903]: Evaluates material alpha once per face and multiplies it into all pass alpha. Type 0 submits one selected texture frame; type 1 binds and submits slot 0 at weight 1-crossfade, then slot 1 at crossfade; type 2 submits vertex color without a texture. Texture-slot frame selection uses each slot's start, speed, and playback mode.
// UNREALRED VERIFIED [reflection-binding-20260903]: Corrected reflection texture lifetime: material +0xB4 is only a positive presence gate. The reflection branch never passes or selects that handle; immediate drawing binds stage 0 from pending primary handle 0x0187CCE8, left by the last base-slot bind (slot 0 for type 0, slot 1 for type 1, and potentially prior state for untextured type 2). This is retail behavior, not an inferred environment-map bind.
// UNREALRED VERIFIED [material-type2-tint-20260903]: Material type 2 is untextured and submits the computed vertex RGB8. After diffuse lighting and the self-illumination byte floor, it multiplies R/G/B independently by unsigned material bytes +0x09/+0x0A/+0x0B, divides each product by 255, truncates toward zero, and stores the low byte.
// UNREALRED VERIFIED [material-alpha-byte-20260903]: Evaluates the clamped material alpha once per face, then rounds each effective pass alpha to RGB8. Type 0 and type 2 use round(alpha*255); type 1 independently rounds alpha*255*(1-crossfade) and alpha*255*crossfade. The specular pass uses round(alpha*255), while reflection uses round(reflection_amount*alpha*255).
// UNREALRED VERIFIED [material-type1-vertex-weight-20260903]: Type 1 evaluates one clamped crossfade w, then constructs two separate textured passes. For every vertex it multiplies each already-lit unsigned RGB8 channel by 1-w for slot 0 and by w for slot 1, forces x87 truncation toward zero, and stores the low byte before each slot is submitted.
// UNREALRED VERIFIED [material-type1-pass-composition-20260903]: Type 1 submits slot 0 before slot 1. Each slot receives an independently rounded global alpha byte, round(material_alpha*255*(1-w)) then round(material_alpha*255*w). Non-additive slots select blend mode 3 (source alpha over inverse source alpha on the normal device path), while material flag +8 selects blend mode 2 (source alpha over one) for both slots.
// UNREALRED VERIFIED [material-type1-source-over-color-20260903]: Type 1 submits slot 0 then slot 1 with packet flags 5. Each source RGB is texture times its independently truncated weighted vertex RGB; each source alpha is its independently rounded renderer alpha, additionally multiplied by texture alpha only for alpha-bearing textures. Non-additive framebuffer composition is ordered source-over.
// UNREALRED VERIFIED [material-type1-additive-composition-20260903]: Material type 1 with flag +8 submits slot 0 then slot 1 through the same additive state. Each slot has independently truncated weighted vertex RGB and independently rounded global alpha. The framebuffer result is D + S0*A0 + S1*A1, with texture alpha included in each Ai for alpha-bearing textures.
// UNREALRED VERIFIED [material-type1-additive-depth-20260903]: Material type 1 with flag +8 loads the same fixed packed state at 0x0187CC60 for slot 0 and slot 1. There is no alternate per-section depth-state selection inside either additive branch.
// UNREALRED VERIFIED [material-type2-alpha-ownership-20260903]: Material type 2 rounds materialAlpha*255, publishes that byte as current renderer alpha with white current RGB, then submits its independently tinted vertex RGB using packet flags 4 and the untextured state at 0x0187CD30. Base-pass coverage therefore owns material alpha only, not vertex or texture alpha.
// UNREALRED VERIFIED [material-type2-fixed-state-20260903]: The material-type dispatch routes type 2 directly to an immediate base submission using flags 4 and the immutable packed state at 0x0187CD30. The type-2 base pass therefore cannot inherit generic additive or no-depth section presentation flags.
// UNREALRED VERIFIED [material-type1-source-over-depth-20260903]: For each non-additive type-1 slot, texture alpha selects state 0x0187CC50 and opaque texture selects 0x0187CC8C. Both fixed states use source-over blend selector 3 and depth selector 4; no section-level no-depth selector participates.
// UNREALRED VERIFIED [material-type0-alpha-ownership-20260903]: Material type 0 rounds materialAlpha*255 into current renderer alpha, then every textured LOD-override, additive, alpha-texture, or opaque-texture branch submits packet flags 5. Coverage owns material alpha and, where alpha selector 3 applies, texture alpha; no branch admits vertex alpha.
// UNREALRED VERIFIED [material-type0-fixed-state-20260903]: Material type 0 first gives mesh LOD flag 0x8 priority, forcing source-over state (1,2,3,3,1,0). Otherwise material additive byte +8 selects (1,2,3,2,1,3); an alpha texture selects (1,2,3,3,5,0); and an opaque texture selects (1,2,0,3,4,0).
// UNREALRED VERIFIED [material-type0-alpha-test-threshold-20260903]: Only ordinary material type 0 with a texture classified as alpha-bearing dynamically packs depth/alpha selector 5. LOD-override, additive, and opaque-texture branches select other fixed states.
float *__cdecl rf_d3d8_submit_mesh_faces(float *a1, float a2)
{
  float *result; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  char v8; // bl
  unsigned __int8 v9; // al
  unsigned __int8 v10; // al
  unsigned __int8 v11; // al
  unsigned __int8 v12; // al
  unsigned __int8 v13; // al
  int *v14; // eax
  unsigned __int8 v15; // al
  int *v16; // eax
  float v17; // [esp+14h] [ebp-210h]
  float v18; // [esp+18h] [ebp-20Ch]
  float v19; // [esp+1Ch] [ebp-208h]
  float v20; // [esp+50h] [ebp-1D4h]
  float v21; // [esp+84h] [ebp-1A0h]
  float v22; // [esp+88h] [ebp-19Ch]
  float v23; // [esp+8Ch] [ebp-198h]
  int v24; // [esp+90h] [ebp-194h]
  float v25; // [esp+C4h] [ebp-160h]
  float v26; // [esp+C8h] [ebp-15Ch]
  int v27; // [esp+CCh] [ebp-158h] BYREF
  int v28; // [esp+D0h] [ebp-154h] BYREF
  int v29; // [esp+D4h] [ebp-150h]
  int v30; // [esp+D8h] [ebp-14Ch] BYREF
  float v31[3]; // [esp+DCh] [ebp-148h] BYREF
  float v32[3]; // [esp+E8h] [ebp-13Ch] BYREF
  float sum_result[3]; // [esp+F4h] [ebp-130h] BYREF
  float v34[9]; // [esp+100h] [ebp-124h] BYREF
  float copy_result[3]; // [esp+124h] [ebp-100h] BYREF
  float v36[3]; // [esp+130h] [ebp-F4h] BYREF
  float out_vector[3]; // [esp+13Ch] [ebp-E8h] BYREF
  int i1; // [esp+148h] [ebp-DCh]
  int nn; // [esp+14Ch] [ebp-D8h]
  int n; // [esp+150h] [ebp-D4h]
  int jj; // [esp+154h] [ebp-D0h]
  int ii; // [esp+158h] [ebp-CCh]
  float v43; // [esp+15Ch] [ebp-C8h]
  float v44; // [esp+160h] [ebp-C4h]
  int v45; // [esp+164h] [ebp-C0h]
  int mm; // [esp+168h] [ebp-BCh]
  int kk; // [esp+16Ch] [ebp-B8h]
  int v48; // [esp+170h] [ebp-B4h]
  unsigned __int8 v49; // [esp+177h] [ebp-ADh]
  int v50; // [esp+178h] [ebp-ACh]
  int v51; // [esp+17Ch] [ebp-A8h]
  int m; // [esp+180h] [ebp-A4h]
  int v53; // [esp+184h] [ebp-A0h]
  int v54; // [esp+188h] [ebp-9Ch] BYREF
  float v55; // [esp+18Ch] [ebp-98h]
  _DWORD *v56; // [esp+190h] [ebp-94h]
  int v57; // [esp+194h] [ebp-90h] BYREF
  int v58; // [esp+198h] [ebp-8Ch]
  int *v59; // [esp+19Ch] [ebp-88h]
  float v60[4]; // [esp+1A0h] [ebp-84h] BYREF
  int k; // [esp+1B0h] [ebp-74h]
  char v62; // [esp+1B7h] [ebp-6Dh]
  float v63[3]; // [esp+1B8h] [ebp-6Ch] BYREF
  int v64[3]; // [esp+1C4h] [ebp-60h] BYREF
  int v65; // [esp+1D0h] [ebp-54h]
  int j; // [esp+1D4h] [ebp-50h]
  float destination[3]; // [esp+1D8h] [ebp-4Ch] BYREF
  int v68; // [esp+1E4h] [ebp-40h]
  bool v69; // [esp+1EBh] [ebp-39h]
  float v70[9]; // [esp+1ECh] [ebp-38h] BYREF
  int v71; // [esp+210h] [ebp-14h]
  float v72[3]; // [esp+214h] [ebp-10h] BYREF
  int i; // [esp+220h] [ebp-4h]

  v69 = rf_vector_length_squared(a1 + 20) != 0.0;
  result = a1;
  if ( !*(_DWORD *)(*(_DWORD *)a1 + 180) )
    return result;
  rf_vector3_copy_return_destination(v72, a1 + 1);
  rf_vector3_set_components_return_destination(destination, 0.0, 0.0, 0.0);
  rf_matrix3_construct((char *)v70);
  if ( v69 )
  {
    rf_vector_rotate_by_matrix3(v72, a1 + 23);
    if ( unk_930A38 && *(_DWORD *)&byte_98967F[756197] )
    {
      v3 = rf_vector_subtract(a1 + 20, out_vector, &flt_A420BC);
      rf_vector_accumulate(v72, v3);
      rf_matrix3_inverse_rotate_vector(v72, *(float **)&byte_98967F[756197]);
      rf_vector_accumulate(v72, unk_18CD4A8);
      v4 = rf_vector_subtract(a1 + 20, v36, &flt_A420BC);
      rf_vector_copy(destination, copy_result, v4);
      rf_matrix3_inverse_rotate_vector(destination, *(float **)&byte_98967F[756197]);
      rf_vector_accumulate(destination, unk_18CD4A8);
      v5 = rf_matrix3_argument_times_receiver_to_output(&flt_A5A0C8, v34, a1 + 23);
      rf_matrix3_copy(v70, v5);
    }
    else
    {
      v6 = rf_vector_add(a1 + 20, sum_result, &flt_A5A0EC);
      rf_vector_accumulate(v72, v6);
      v7 = rf_vector_add(a1 + 20, v32, &flt_A5A0EC);
      rf_vector_copy(destination, v31, v7);
      rf_matrix3_copy(v70, a1 + 23);
    }
    rf_renderer_push_instance_transform_dispatch((int)destination, (int)v70);
  }
  if ( unk_930A38 )
    *(_DWORD *)(*(_DWORD *)a1 + 276) |= 0x10u;
  else
    rf_light_sync_active_receiver_space_if_enabled();
  for ( i = 0; i < *(_DWORD *)(*(_DWORD *)a1 + 176); ++i )
  {
    unk_182ABE1[48 * i] = 0;
    unk_182ABE3[48 * i] = 0;
  }
  dword_1D6D248 = 0;
  v68 = *(_DWORD *)(*(_DWORD *)a1 + 196);
  for ( i = 0; i < v68; ++i )
  {
    v65 = *(_DWORD *)(*(_DWORD *)a1 + 200) + 44 * i;
    *(_DWORD *)(v65 + 8) = 0;
    *(_BYTE *)(v65 + 24) = 0;
  }
  for ( i = 0; i < *(_DWORD *)(*(_DWORD *)a1 + 180); ++i )
  {
    for ( j = 0; j < 3; ++j )
    {
      *(float *)(*(_DWORD *)(*(_DWORD *)a1 + 184) + 144 * i + 4 * j + 36) = *(float *)(*((_DWORD *)a1 + 33)
                                                                                     + 24 * i
                                                                                     + 4 * j);
      *(float *)(*(_DWORD *)(*(_DWORD *)a1 + 184) + 144 * i + 4 * j + 48) = *(float *)(*((_DWORD *)a1 + 33)
                                                                                     + 24 * i
                                                                                     + 4 * j
                                                                                     + 12);
    }
    *(_DWORD *)(*(_DWORD *)(*(_DWORD *)a1 + 184) + 144 * i + 124) = 0;
    rf_renderer_queue_visible_indexed_triangle(
      (int *)(*(_DWORD *)(*(_DWORD *)a1 + 184) + 144 * i),
      *((_DWORD *)a1 + 32));
  }
  rf_record16_shell_sort_descending((int)&unk_1CF7C28, dword_1D6D248, 1);
  v71 = dword_1D6D248;
  rf_render_color_set_rgba8(255, 255, 255, 255);
  for ( i = 0; i < v71; ++i )
  {
    v62 = 0;
    v56 = (_DWORD *)unk_1CF7C34[4 * i];
    if ( (int)v56[8] < 0 || v56[8] >= *(_DWORD *)(*(_DWORD *)a1 + 188) )
      continue;
    v58 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)a1 + 192) + 4 * v56[8]);
    v59 = (int *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)a1 + 132) + 140) + 200 * v58);
    v64[0] = (int)&unk_182ABC8 + 48 * v56[5];
    v64[1] = (int)&unk_182ABC8 + 48 * v56[6];
    v64[2] = (int)&unk_182ABC8 + 48 * v56[7];
    for ( k = 0; k < 3; ++k )
    {
      v53 = v56[k + 33];
      if ( !*(_DWORD *)(v53 + 8) )
      {
        *(_DWORD *)(v53 + 8) = 1;
        rf_vector3_zero_return_destination((float *)(v53 + 12));
        v51 = *(_DWORD *)(v53 + 36);
        for ( m = 0; m < v51; ++m )
        {
          v50 = *(_DWORD *)(*(_DWORD *)(v53 + 40) + 4 * m);
          rf_vector_accumulate((float *)(v53 + 12), (float *)(v50 + 96));
        }
        v26 = 1.0 / (double)v51;
        rf_vector3_scale_in_place_return_self((float *)(v53 + 12), v26);
        rf_vector_normalize((float *)(v53 + 12));
      }
      if ( !*(_BYTE *)(v53 + 24) )
      {
        *(_BYTE *)(v53 + 24) = 1;
        if ( (*(_DWORD *)(*(_DWORD *)a1 + 276) & 0x10) != 0 )
        {
          *(_BYTE *)(v53 + 25) = -1;
          *(_BYTE *)(v53 + 26) = -1;
          *(_BYTE *)(v53 + 27) = -1;
        }
        else
        {
          rf_renderer_compute_nonworld_diffuse_rgb8(
            (_BYTE *)(v53 + 25),
            (_BYTE *)(v53 + 26),
            (_BYTE *)(v53 + 27),
            1,
            (float *)(*((_DWORD *)a1 + 32) + 12 * *(_DWORD *)(v53 + 4)),
            (float *)(v53 + 12),
            2.0);
          v25 = rf_material_evaluate_self_illumination(v59, a2) * 255.0;
          v49 = rf_round_nonnegative_float_to_int(v25);
          if ( *(unsigned __int8 *)(v53 + 25) < (int)v49 )
            *(_BYTE *)(v53 + 25) = v49;
          if ( *(unsigned __int8 *)(v53 + 26) < (int)v49 )
            *(_BYTE *)(v53 + 26) = v49;
          if ( *(unsigned __int8 *)(v53 + 27) < (int)v49 )
            *(_BYTE *)(v53 + 27) = v49;
        }
        if ( *v59 == 2 )
        {
          *(_BYTE *)(v53 + 25) = (int)((double)(*((unsigned __int8 *)v59 + 9) * *(unsigned __int8 *)(v53 + 25)) / 255.0);
          *(_BYTE *)(v53 + 26) = (int)((double)(*((unsigned __int8 *)v59 + 10) * *(unsigned __int8 *)(v53 + 26)) / 255.0);
          *(_BYTE *)(v53 + 27) = (int)((double)(*((unsigned __int8 *)v59 + 11) * *(unsigned __int8 *)(v53 + 27)) / 255.0);
        }
      }
      if ( *((float *)v59 + 33) > 0.0 )
      {
        v8 = v62;
        v62 = rf_renderer_compute_mesh_vertex_specular_rgb8(
                (float *)(*((_DWORD *)a1 + 32) + 12 * *(_DWORD *)(v53 + 4)),
                (float *)(v53 + 12),
                (_BYTE *)&v60[3] + k,
                (_BYTE *)&v54 + k,
                (_BYTE *)&v57 + k,
                *((float *)v59 + 33),
                *((float *)v59 + 34),
                1)
            | v8;
      }
      if ( v59[45] > 0 )
        rf_renderer_compute_reflection_uv(
          &v63[k],
          &v60[k],
          (float *)(*((_DWORD *)a1 + 32) + 12 * *(_DWORD *)(v53 + 4)),
          (float *)(v53 + 12));
    }
    v55 = rf_material_evaluate_alpha(v59, a2);
    v24 = *v59;
    if ( *v59 )
    {
      if ( v24 != 1 )
      {
        if ( v24 == 2 )
        {
          for ( n = 0; n < 3; ++n )
          {
            *(_BYTE *)(v64[n] + 44) = *(_BYTE *)(v56[n + 33] + 25);
            *(_BYTE *)(v64[n] + 45) = *(_BYTE *)(v56[n + 33] + 26);
            *(_BYTE *)(v64[n] + 46) = *(_BYTE *)(v56[n + 33] + 27);
          }
          v19 = v55 * 255.0;
          v12 = rf_round_nonnegative_float_to_int(v19);
          rf_render_color_set_rgba8(255, 255, 255, v12);
          rf_renderer_submit_immediate_polygon(3, (int)v64, 4, unk_187CD30, 0, 0.0);
        }
        goto LABEL_91;
      }
      v22 = a2 - *(float *)(*(_DWORD *)a1 + 168);
      v44 = rf_material_evaluate_texture_crossfade(v59, v22);
      v43 = 1.0 - v44;
      v45 = rf_material_texture_slot_select_frame((int)(v59 + 4), a2);
      rf_renderer_set_pending_texture_handles(v45, -1);
      v21 = v55 * 255.0 * v43;
      v10 = rf_round_nonnegative_float_to_int(v21);
      rf_render_color_set_rgba8(255, 255, 255, v10);
      for ( ii = 0; ii < 3; ++ii )
      {
        *(_BYTE *)(v64[ii] + 44) = (int)((double)*(unsigned __int8 *)(v56[ii + 33] + 25) * v43);
        *(_BYTE *)(v64[ii] + 45) = (int)((double)*(unsigned __int8 *)(v56[ii + 33] + 26) * v43);
        *(_BYTE *)(v64[ii] + 46) = (int)((double)*(unsigned __int8 *)(v56[ii + 33] + 27) * v43);
        *(float *)(v64[ii] + 28) = *(float *)&v56[ii + 9];
        *(float *)(v64[ii] + 32) = *(float *)&v56[ii + 12];
      }
      if ( *((_BYTE *)v59 + 8) )
      {
        rf_renderer_submit_immediate_polygon(3, (int)v64, 5, unk_187CC60, 0, 0.0);
      }
      else if ( rf_bitmap_resolved_format_is_4_5_7(v45) )
      {
        rf_renderer_submit_immediate_polygon(3, (int)v64, 5, unk_187CC50, 0, 0.0);
      }
      else
      {
        rf_renderer_submit_immediate_polygon(3, (int)v64, 5, unk_187CC8C, 0, 0.0);
      }
      v45 = rf_material_texture_slot_select_frame((int)(v59 + 17), a2);
      rf_renderer_set_pending_texture_handles(v45, -1);
      v20 = v55 * 255.0 * v44;
      v11 = rf_round_nonnegative_float_to_int(v20);
      rf_render_color_set_rgba8(255, 255, 255, v11);
      for ( jj = 0; jj < 3; ++jj )
      {
        *(_BYTE *)(v64[jj] + 44) = (int)((double)*(unsigned __int8 *)(v56[jj + 33] + 25) * v44);
        *(_BYTE *)(v64[jj] + 45) = (int)((double)*(unsigned __int8 *)(v56[jj + 33] + 26) * v44);
        *(_BYTE *)(v64[jj] + 46) = (int)((double)*(unsigned __int8 *)(v56[jj + 33] + 27) * v44);
      }
      if ( !*((_BYTE *)v59 + 8) )
      {
        if ( rf_bitmap_resolved_format_is_4_5_7(v45) )
          rf_renderer_submit_immediate_polygon(3, (int)v64, 5, unk_187CC50, 0, 0.0);
        else
          rf_renderer_submit_immediate_polygon(3, (int)v64, 5, unk_187CC8C, 0, 0.0);
        goto LABEL_91;
      }
      goto LABEL_66;
    }
    v48 = rf_material_texture_slot_select_frame((int)(v59 + 4), a2);
    for ( kk = 0; kk < 3; ++kk )
    {
      *(_BYTE *)(v64[kk] + 44) = *(_BYTE *)(v56[kk + 33] + 25);
      *(_BYTE *)(v64[kk] + 45) = *(_BYTE *)(v56[kk + 33] + 26);
      *(_BYTE *)(v64[kk] + 46) = *(_BYTE *)(v56[kk + 33] + 27);
    }
    v23 = v55 * 255.0;
    v9 = rf_round_nonnegative_float_to_int(v23);
    rf_render_color_set_rgba8(255, 255, 255, v9);
    if ( v48 < 0 )
    {
      rf_renderer_submit_immediate_polygon(3, (int)v64, 4, unk_187CD30, 0, 0.0);
      goto LABEL_91;
    }
    for ( mm = 0; mm < 3; ++mm )
    {
      *(float *)(v64[mm] + 28) = *(float *)&v56[mm + 9];
      *(float *)(v64[mm] + 32) = *(float *)&v56[mm + 12];
    }
    rf_renderer_set_pending_texture_handles(v48, -1);
    if ( (*(_DWORD *)(*(_DWORD *)a1 + 276) & 8) == 0 )
    {
      if ( !*((_BYTE *)v59 + 8) )
      {
        if ( rf_bitmap_resolved_format_is_4_5_7(v48) )
          v29 = *rf_render_state_pack(&v30, 1, 2, 3, 3, 5, 0);
        else
          v29 = unk_187CC8C;
        rf_renderer_submit_immediate_polygon(3, (int)v64, 5, v29, 0, 0.0);
        goto LABEL_91;
      }
LABEL_66:
      rf_renderer_submit_immediate_polygon(3, (int)v64, 5, unk_187CC60, 0, 0.0);
      goto LABEL_91;
    }
    rf_renderer_submit_immediate_polygon(3, (int)v64, 5, unk_187CC54, 0, 0.0);
LABEL_91:
    if ( v62 )
    {
      for ( nn = 0; nn < 3; ++nn )
      {
        *(_BYTE *)(v64[nn] + 44) = *((_BYTE *)&v60[3] + nn);
        *(_BYTE *)(v64[nn] + 45) = *((_BYTE *)&v54 + nn);
        *(_BYTE *)(v64[nn] + 46) = *((_BYTE *)&v57 + nn);
        *(_BYTE *)(v64[nn] + 47) = (*((unsigned __int8 *)&v57 + nn)
                                  + *((unsigned __int8 *)&v54 + nn)
                                  + *((unsigned __int8 *)&v60[3] + nn))
                                 / 3;
      }
      v18 = v55 * 255.0;
      v13 = rf_round_nonnegative_float_to_int(v18);
      rf_render_color_set_rgba8(255, 255, 255, v13);
      v14 = rf_render_state_pack(&v28, 0, 0, 0, 2, 1, 0);
      rf_renderer_submit_immediate_polygon(3, (int)v64, 12, *v14, 0, 0.0);
    }
    if ( v59[45] > 0 )
    {
      for ( i1 = 0; i1 < 3; ++i1 )
      {
        *(float *)(v64[i1] + 28) = v63[i1];
        *(float *)(v64[i1] + 32) = v60[i1];
      }
      v17 = *((float *)v59 + 35) * 255.0 * v55;
      v15 = rf_round_nonnegative_float_to_int(v17);
      rf_render_color_set_rgba8(255, 255, 255, v15);
      v16 = rf_render_state_pack(&v27, 1, 1, 0, 3, 1, 0);
      rf_renderer_submit_immediate_polygon(3, (int)v64, 1, *v16, 0, 0.0);
    }
  }
  result = (float *)v69;
  if ( v69 )
    return (float *)rf_renderer_pop_instance_transform_dispatch();
  return result;
}

