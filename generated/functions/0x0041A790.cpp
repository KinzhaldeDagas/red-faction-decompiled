// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041A790 rf_glare_render_definition_beam_and_corona
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Cdecl(definitionIndex,position,matrix,randomRotateByte), NO index bounds check. Copies full36-byte current-player view matrix: decompiler split24-byte local plus forward vec3 is fully initialized, not an uninitialized read. Let d=normalize(position-cameraPos), forward=matrix row2, angle=acos(dot(forward,-d))*180/pi. Ordered angle>90 folds to180-angle; ordered angle<-90 folds to-angle-180; NaN unchanged. Nonnegative signed volumetric handle+36 submits WHITE beam with alpha=0.5*(clamp((angle-halfCone)/25,-1,1)+1), endpoint position+forward*defLength,height defHeight; no2/255 cutoff here. Then ALWAYS submits corona, even absent/zero corona handle+12: f=(FOV/2-acos(dot(cameraForward,d))*180/pi)/(FOV/2);
// alpha=(f+1)*global0x6612F8*(40/distance), multiplied by (1-(angle-halfCone)/10) only for ordered angle>halfCone, then intensity+20 and clamp[0,1]. Radius=(f+1)*global0x6612FC*defRadiusScale+24, optionally multiplied by (1-(angle-halfCone)/20), lower-clamped to0 only on ordered negative. Packs render state(1,2,3,2,1,3), WHITE/trunc(alpha*255), corona texture; random byte nonzero draws shared random rotation[0,2pi], else0, then submits aspect billboard and returns delegate AL. Def color+8,distanceFactor+28,diminish+32,reflection+48 unused here. No local division/finite/dot/texture validation, occlusion test, fog adjustment or render-state restoration.
char __cdecl rf_glare_render_definition_beam_and_corona(int a1, float *lhs, int a3, char a4)
{
  float *v4; // eax
  float *v5; // eax
  float scalar; // [esp+8h] [ebp-98h]
  float scalara; // [esp+8h] [ebp-98h]
  float scaled_result[3]; // [esp+Ch] [ebp-94h] BYREF
  float v10[3]; // [esp+18h] [ebp-88h] BYREF
  float sum_result[3]; // [esp+24h] [ebp-7Ch] BYREF
  float v12; // [esp+30h] [ebp-70h]
  char *v13; // [esp+34h] [ebp-6Ch]
  float v14; // [esp+38h] [ebp-68h]
  float rhs[3]; // [esp+3Ch] [ebp-64h] BYREF
  float v16; // [esp+48h] [ebp-58h]
  float v17; // [esp+4Ch] [ebp-54h]
  float out_vector[3]; // [esp+50h] [ebp-50h] BYREF
  char v19; // [esp+5Eh] [ebp-42h]
  char v20; // [esp+5Fh] [ebp-41h]
  _BYTE v21[24]; // [esp+60h] [ebp-40h] BYREF
  float v22[3]; // [esp+78h] [ebp-28h] BYREF
  float v23; // [esp+84h] [ebp-1Ch]
  int v24; // [esp+88h] [ebp-18h] BYREF
  float v25; // [esp+8Ch] [ebp-14h]
  int v26; // [esp+90h] [ebp-10h] BYREF
  float v27; // [esp+94h] [ebp-Ch]
  int v28; // [esp+98h] [ebp-8h] BYREF
  int v29; // [esp+9Ch] [ebp-4h]

  v13 = &byte_680DD8[52 * a1];
  v20 = 1;
  *(float *)&v24 = 0.0;
  rf_entity_view_copy_referenced_position(rhs, *(_DWORD *)(unk_87C640 + 196));
  rf_entity_view_copy_referenced_matrix_2016((int)v21, *(_DWORD **)(unk_87C640 + 196));
  rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_normalize_reciprocal_sqrt(out_vector);
  v4 = rf_vector_negate(out_vector, v10);
  scalar = rf_vector_dot((float *)(a3 + 24), v4);
  v14 = rf_acos_float(scalar) * 180.0 / 3.141592741012573;
  if ( v14 <= 90.0 )
  {
    if ( v14 < -90.0 )
      v14 = -v14 - 180.0;
  }
  else
  {
    v14 = 180.0 - v14;
  }
  if ( *((int *)v13 + 9) < 0 )
  {
    v20 = 0;
  }
  else
  {
    *(float *)&v24 = (v14 - *((float *)v13 + 4)) / 25.0;
    rf_float_clamp_in_place((float *)&v24, -1.0, 1.0);
    *(float *)&v24 = (*(float *)&v24 + 1.0) * 0.5;
  }
  if ( v20 )
  {
    rf_render_color_set_rgba8(255, 255, 255, (int)(*(float *)&v24 * 255.0));
    rf_renderer_set_pending_texture_handles(*((_DWORD *)v13 + 9), -1);
    v5 = rf_vector_multiply_scalar((const float *)(a3 + 24), scaled_result, *((float *)v13 + 11));
    rf_vector_add(lhs, sum_result, v5);
    rf_renderer_camera_facing_beam_backend_wrapper(
      sum_result,
      lhs,
      *((float *)v13 + 10),
      rf_particle_glow_billboard_render_state);
  }
  v19 = 1;
  *(float *)&v28 = 1.0;
  v12 = 1.0;
  v23 = 0.0;
  v17 = rf_vector_distance(lhs, rhs);
  v25 = flt_66157C;
  scalara = rf_vector_dot(v22, out_vector);
  v27 = rf_acos_float(scalara) * 180.0 / 3.141592741012573;
  v23 = (v25 * 0.5 - v27) / (v25 * 0.5);
  *(float *)&v28 = 40.0 / v17;
  *(float *)&v28 = (v23 + 1.0) * flt_6612F8 * *(float *)&v28;
  if ( *((float *)v13 + 4) < (double)v14 )
    *(float *)&v28 = (1.0 - (v14 - *((float *)v13 + 4)) / 10.0) * *(float *)&v28;
  *(float *)&v28 = *(float *)&v28 * *((float *)v13 + 5);
  rf_float_clamp_in_place((float *)&v28, 0.0, 1.0);
  v12 = *((float *)v13 + 6);
  v12 = (v23 + 1.0) * flt_6612FC * v12;
  if ( *((float *)v13 + 4) < (double)v14 )
    v12 = (1.0 - (v14 - *((float *)v13 + 4)) / 20.0) * v12;
  if ( v12 < 0.0 )
    v12 = 0.0;
  v29 = (int)(*(float *)&v28 * 255.0);
  rf_render_state_pack(&v26, 1, 2, 3, 2, 1, 3);
  rf_render_color_set_rgba8(255, 255, 255, v29);
  rf_renderer_set_pending_texture_handles(*((_DWORD *)v13 + 3), -1);
  v16 = 0.0;
  if ( a4 )
    v16 = rf_random_float_range(0.0, 6.2831855);
  return rf_renderer_world_billboard_aspect_backend_dispatch((int)lhs, v16, v12, v26);
}

