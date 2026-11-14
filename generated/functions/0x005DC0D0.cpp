// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DC0D0 rf_renderer_draw_particle_age_shaped_billboard_or_triangle
// UNREALRED VERIFIED [renderer-lighting-20261028]: Arguments emitterinstance,particleindex,materialtime. Rejects instanceDWORD+20 negative orbit0x40000000; particle36-bytearray pointeratinstance+144,age+0,lifetime+4,angle+8,position+12,velocity+24. Rejects negativeage andlifetime<=age; computes age/lifetime BEFORE lattercheck. Basewidth=2*instancefloat+128,alpha=instancefloat+140; normalizedage envelopes fromdefinition+176/180 widthramp and+184/188 alpharamp. Material200-byteentry selected throughdefinition nestedtable andindex+196. Definitionflags+172 bit0x100 selects velocitytriangle; otherwise billboard. Billboard textureframes use normalizedphase0x5C91F0 whenflag4,else age*15 throughmaterialframehelper. Flag1forceswhiteunlit,else computes nonworlddiffuse atparticleposition,raisesRGB to materialselfilluminationfloor evaluated atmaterialtime. Alpha=shapedalpha*255 castbyte.
// Materialmode0drawsfirsttexture; mode1drawsbothslotswith1-f/f RGB/alphaweights,crossfade evaluated atage/0.06666667; othermodesreturn. Glowstate chosen bymaterialbyte+8 ORdefinitionflag1. Angle fromparticle+8,widthenvelope passed to aspectbillboard0x57E990. Trianglepath copiescurrentviewtransform (actualoutputarguments present inassembly despite missingdecompilerargs),crosses viewmatrixthirdrow withvelocity forside,builds position +/- side*(shapedwidth/4) and trailingpoint position - velocity/15*1.6*widthenvelope*definitionfloat+192. Transforms/projects3vertices,useswhitergb ifflag1 else diffusewithnormal cross(velocity,side),raises toselfillumfloor,multiplies materialRGBbytes+9..11,sets shapedalpha. Submits mask12 using state0x187CC64 whenmaterialbyte+8 else0x1D85DB0; no textureframebinding in trianglebranch. No particleindex,lifetimezero,enveloperampdenominator or materialindex guards;
// leaves color/textures/state changed.
void __cdecl rf_renderer_draw_particle_age_shaped_billboard_or_triangle(float *a1, int a2, float a3)
{
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float scalar; // [esp+10h] [ebp-284h]
  float v12; // [esp+18h] [ebp-27Ch]
  float v13; // [esp+50h] [ebp-244h]
  float v14; // [esp+9Ch] [ebp-1F8h]
  float v15[3]; // [esp+A0h] [ebp-1F4h] BYREF
  float v16[3]; // [esp+ACh] [ebp-1E8h] BYREF
  float v17[3]; // [esp+B8h] [ebp-1DCh] BYREF
  int v18[3]; // [esp+C4h] [ebp-1D0h] BYREF
  float v19[3]; // [esp+D0h] [ebp-1C4h] BYREF
  float v20[3]; // [esp+DCh] [ebp-1B8h] BYREF
  float v21[3]; // [esp+E8h] [ebp-1ACh] BYREF
  float scaled_result[3]; // [esp+F4h] [ebp-1A0h] BYREF
  float v23; // [esp+100h] [ebp-194h]
  float v24; // [esp+104h] [ebp-190h]
  float v25; // [esp+108h] [ebp-18Ch]
  unsigned __int8 v26; // [esp+10Fh] [ebp-185h]
  float v27[3]; // [esp+110h] [ebp-184h] BYREF
  float v28[9]; // [esp+11Ch] [ebp-178h] BYREF
  float v29; // [esp+140h] [ebp-154h]
  float v30; // [esp+144h] [ebp-150h]
  __int16 v31; // [esp+148h] [ebp-14Ch] BYREF
  unsigned __int8 v32; // [esp+14Ah] [ebp-14Ah] BYREF
  unsigned __int8 v33; // [esp+14Bh] [ebp-149h]
  int v34; // [esp+14Ch] [ebp-148h]
  int v35; // [esp+150h] [ebp-144h]
  unsigned __int8 v36; // [esp+157h] [ebp-13Dh]
  int v37[3]; // [esp+158h] [ebp-13Ch] BYREF
  _BYTE *v38; // [esp+164h] [ebp-130h]
  float sum_result[3]; // [esp+168h] [ebp-12Ch] BYREF
  _BYTE v40[48]; // [esp+174h] [ebp-120h] BYREF
  float v41[3]; // [esp+1A4h] [ebp-F0h] BYREF
  float out_vector[3]; // [esp+1B0h] [ebp-E4h] BYREF
  _BYTE v43[48]; // [esp+1BCh] [ebp-D8h] BYREF
  int v44[3]; // [esp+1ECh] [ebp-A8h]
  float v45[3]; // [esp+1F8h] [ebp-9Ch] BYREF
  int v46[3]; // [esp+204h] [ebp-90h] BYREF
  int i; // [esp+210h] [ebp-84h]
  float v48[6]; // [esp+214h] [ebp-80h] BYREF
  float v49[3]; // [esp+22Ch] [ebp-68h] BYREF
  float vector[3]; // [esp+238h] [ebp-5Ch] BYREF
  _BYTE v51[48]; // [esp+244h] [ebp-50h] BYREF
  float v52; // [esp+274h] [ebp-20h]
  float v53; // [esp+278h] [ebp-1Ch]
  float v54; // [esp+27Ch] [ebp-18h]
  float v55; // [esp+280h] [ebp-14h]
  unsigned int *v56; // [esp+284h] [ebp-10h]
  int v57[3]; // [esp+288h] [ebp-Ch] BYREF

  if ( *((int *)a1 + 5) < 0 )
    return;
  if ( ((*((_DWORD *)a1 + 5) >> 30) & 1) != 0 )
    return;
  if ( *(float *)(*((_DWORD *)a1 + 36) + 36 * a2) < 0.0 )
    return;
  rf_vector3_copy_return_destination((float *)v57, (float *)(*((_DWORD *)a1 + 36) + 36 * a2 + 12));
  v54 = a1[32] + a1[32];
  v55 = *(float *)(*((_DWORD *)a1 + 36) + 36 * a2) / *(float *)(*((_DWORD *)a1 + 36) + 36 * a2 + 4);
  if ( *(float *)(*((_DWORD *)a1 + 36) + 36 * a2 + 4) <= (double)*(float *)(*((_DWORD *)a1 + 36) + 36 * a2) )
    return;
  if ( *(float *)(*(_DWORD *)a1 + 176) <= (double)v55 )
  {
    if ( *(float *)(*(_DWORD *)a1 + 180) >= (double)v55 )
      v52 = 1.0;
    else
      v52 = (1.0 - v55) / (1.0 - *(float *)(*(_DWORD *)a1 + 180));
  }
  else
  {
    v52 = v55 / *(float *)(*(_DWORD *)a1 + 176);
  }
  v54 = v54 * v52;
  v53 = a1[35];
  if ( *(float *)(*(_DWORD *)a1 + 184) <= (double)v55 )
  {
    if ( *(float *)(*(_DWORD *)a1 + 188) < (double)v55 )
      v53 = (1.0 - v55) / (1.0 - *(float *)(*(_DWORD *)a1 + 188)) * v53;
  }
  else
  {
    v53 = v55 / *(float *)(*(_DWORD *)a1 + 184) * v53;
  }
  v56 = (unsigned int *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)a1 + 132) + 140) + 200 * *(_DWORD *)(*(_DWORD *)a1 + 196));
  if ( (*(_DWORD *)(*(_DWORD *)a1 + 172) & 0x100) == 0 )
  {
    if ( (*(_DWORD *)(*(_DWORD *)a1 + 172) & 4) != 0 )
    {
      v30 = *(float *)(*((_DWORD *)a1 + 36) + 36 * a2) / *(float *)(*((_DWORD *)a1 + 36) + 36 * a2 + 4);
      v34 = rf_material_texture_slot_frame_from_normalized_phase(v56 + 4, v30);
      v35 = rf_material_texture_slot_frame_from_normalized_phase(v56 + 17, v30);
    }
    else
    {
      v29 = *(float *)(*((_DWORD *)a1 + 36) + 36 * a2) * 15.0;
      v34 = rf_material_texture_slot_select_frame((int)(v56 + 4), v29);
      v35 = rf_material_texture_slot_select_frame((int)(v56 + 17), v29);
    }
    if ( (*(_DWORD *)(*(_DWORD *)a1 + 172) & 1) != 0 )
    {
      v31 = -1;
      v32 = -1;
      v33 = (int)(v53 * 255.0);
    }
    else
    {
      rf_vector3_default_construct_noop(v27);
      rf_matrix3_construct((char *)v28);
      rf_renderer_copy_current_view_transform(v27, v28);
      rf_renderer_compute_nonworld_diffuse_rgb8(&v31, (_BYTE *)&v31 + 1, &v32, 1, (float *)v57, nullptr, -1.0);
      v13 = rf_material_evaluate_self_illumination((int *)v56, a3) * 255.0;
      v26 = rf_round_nonnegative_float_to_int(v13);
      if ( (unsigned __int8)v31 < (int)v26 )
        LOBYTE(v31) = v26;
      if ( HIBYTE(v31) < (int)v26 )
        HIBYTE(v31) = v26;
      if ( v32 < (int)v26 )
        v32 = v26;
      v33 = (int)(v53 * 255.0);
    }
    if ( *v56 )
    {
      if ( *v56 != 1 )
        return;
      v23 = *(float *)(*((_DWORD *)a1 + 36) + 36 * a2) / 0.06666667014360428;
      v25 = rf_material_evaluate_texture_crossfade((int *)v56, v23);
      v24 = 1.0 - v25;
      rf_renderer_set_pending_texture_handles(v34, -1);
      rf_render_color_set_rgba8(
        (int)((double)(unsigned __int8)v31 * v24),
        (int)((double)HIBYTE(v31) * v24),
        (int)((double)v32 * v24),
        (int)((double)v33 * v24));
      if ( *((_BYTE *)v56 + 8) || (*(_DWORD *)(*(_DWORD *)a1 + 172) & 1) != 0 )
        rf_renderer_world_billboard_aspect_backend_dispatch(
          (float *)v57,
          *(float *)(*((_DWORD *)a1 + 36) + 36 * a2 + 8),
          v54,
          SLODWORD(rf_particle_glow_billboard_render_state));
      else
        rf_renderer_world_billboard_aspect_backend_dispatch(
          (float *)v57,
          *(float *)(*((_DWORD *)a1 + 36) + 36 * a2 + 8),
          v54,
          rf_particle_standard_billboard_render_state);
      rf_renderer_set_pending_texture_handles(v35, -1);
      rf_render_color_set_rgba8(
        (int)((double)(unsigned __int8)v31 * v25),
        (int)((double)HIBYTE(v31) * v25),
        (int)((double)v32 * v25),
        (int)((double)v33 * v25));
      if ( *((_BYTE *)v56 + 8) || (*(_DWORD *)(*(_DWORD *)a1 + 172) & 1) != 0 )
      {
LABEL_47:
        rf_renderer_world_billboard_aspect_backend_dispatch(
          (float *)v57,
          *(float *)(*((_DWORD *)a1 + 36) + 36 * a2 + 8),
          v54,
          SLODWORD(rf_particle_glow_billboard_render_state));
        return;
      }
    }
    else
    {
      rf_renderer_set_pending_texture_handles(v34, -1);
      rf_render_color_set_rgba8((unsigned __int8)v31, HIBYTE(v31), v32, v33);
      if ( *((_BYTE *)v56 + 8) || (*(_DWORD *)(*(_DWORD *)a1 + 172) & 1) != 0 )
        goto LABEL_47;
    }
    rf_renderer_world_billboard_aspect_backend_dispatch(
      (float *)v57,
      *(float *)(*((_DWORD *)a1 + 36) + 36 * a2 + 8),
      v54,
      rf_particle_standard_billboard_render_state);
    return;
  }
  rf_vector3_default_construct_noop(v41);
  rf_matrix3_construct((char *)v48);
  rf_renderer_copy_current_view_transform(v41, v48);
  rf_vector_cross(v49, vector, (float *)(*((_DWORD *)a1 + 36) + 36 * a2 + 24));
  rf_vector_normalize(vector);
  v3 = rf_vector_multiply_scalar(vector, scaled_result, v54);
  v4 = rf_vector_multiply_scalar(v3, v21, 0.25);
  rf_vector_add((const float *)(*((_DWORD *)a1 + 36) + 36 * a2 + 12), sum_result, v4);
  v5 = rf_vector_multiply_scalar(vector, v20, v54);
  v6 = rf_vector_multiply_scalar(v5, v19, 0.25);
  rf_vector_subtract((const float *)(*((_DWORD *)a1 + 36) + 36 * a2 + 12), out_vector, v6);
  v12 = *(float *)(*(_DWORD *)a1 + 192);
  scalar = v52;
  v7 = rf_vector_divide((float *)(*((_DWORD *)a1 + 36) + 36 * a2 + 24), (float *)v18, 15.0);
  v8 = rf_vector_multiply_scalar(v7, v17, 1.6);
  v9 = rf_vector_multiply_scalar(v8, v16, scalar);
  v10 = rf_vector_multiply_scalar(v9, v15, v12);
  rf_vector_subtract((const float *)(*((_DWORD *)a1 + 36) + 36 * a2 + 12), v45, v10);
  rf_vector_prefix_construct_noop(v51);
  rf_vector_prefix_construct_noop(v43);
  rf_vector_prefix_construct_noop(v40);
  rf_renderer_transform_world_point_backend_wrapper((int)v51, sum_result);
  rf_renderer_transform_world_point_backend_wrapper((int)v43, out_vector);
  rf_renderer_transform_world_point_backend_wrapper((int)v40, v45);
  rf_renderer_project_clip_vertex_backend_wrapper((int)v51);
  rf_renderer_project_clip_vertex_backend_wrapper((int)v43);
  rf_renderer_project_clip_vertex_backend_wrapper((int)v40);
  v44[0] = (int)sum_result;
  v44[1] = (int)out_vector;
  v44[2] = (int)v45;
  v46[0] = (int)v51;
  v46[1] = (int)v43;
  v46[2] = (int)v40;
  for ( i = 0; i < 3; ++i )
  {
    v38 = (_BYTE *)v46[i];
    if ( (*(_DWORD *)(*(_DWORD *)a1 + 172) & 1) != 0 )
    {
      v38[44] = -1;
      v38[45] = -1;
      v38[46] = -1;
    }
    else
    {
      rf_vector_cross((float *)(*((_DWORD *)a1 + 36) + 36 * a2 + 24), (float *)v37, vector);
      rf_vector_normalize((float *)v37);
      rf_renderer_compute_nonworld_diffuse_rgb8(v38 + 44, v38 + 45, v38 + 46, 1, (float *)v44[i], (float *)v37, -1.0);
      v14 = rf_material_evaluate_self_illumination((int *)v56, a3) * 255.0;
      v36 = rf_round_nonnegative_float_to_int(v14);
      if ( (unsigned __int8)v38[44] < (int)v36 )
        v38[44] = v36;
      if ( (unsigned __int8)v38[45] < (int)v36 )
        v38[45] = v36;
      if ( (unsigned __int8)v38[46] < (int)v36 )
        v38[46] = v36;
    }
    v38[44] = (int)((double)(*((unsigned __int8 *)v56 + 9) * (unsigned __int8)v38[44]) / 255.0);
    v38[45] = (int)((double)(*((unsigned __int8 *)v56 + 10) * (unsigned __int8)v38[45]) / 255.0);
    v38[46] = (int)((double)(*((unsigned __int8 *)v56 + 11) * (unsigned __int8)v38[46]) / 255.0);
    v38[47] = (int)(v53 * 255.0);
  }
  if ( *((_BYTE *)v56 + 8) )
    rf_renderer_submit_immediate_polygon(3, (int)v46, 12, unk_187CC64, 0, 0.0);
  else
    rf_renderer_submit_immediate_polygon(3, (int)v46, 12, unk_1D85DB0, 0, 0.0);
}

