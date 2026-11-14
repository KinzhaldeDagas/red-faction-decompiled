// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D49F0 rf_renderer_draw_face_multipass_backend_102
// UNREALRED VERIFIED [renderer-polygons-20261028]: Six arguments context,face,packedstate,basebitmap,lightmapbitmap,combinedoutcode. Rejects if byte0x92DE28 clear or face is portal. Byte0x1DAEDAB overridesstate with0x187CC50. Flushes immediate state,sets worldbatching0x1E014E6=1,lazily initializes five packedstates. Faceflags0x300000 collects atmost16 flag8 and16 ordinary decalpolygons; flag0x200000 enables shared-face decalpasses. Faceflag0x40000 gathers atmost4 eligible projectedlights using plane distance in[-radius,radius),cosine extent and distance-fadedRGB. When byte0x663F06 and combinedoutcode nonzero,builds48 local132-byte extendedUV vertices,clips through0x5C8750,rejects count<3 or rejectedbyte and clears batching on that return. Base/lightmap channels always included; enabled decals/lights add channels without independent combined-capacity guard. Otherwise projects cached
// cameraXYZ from sourcevertex+12. Checks global ringcapacity6000vertices/10000indices and resets cursors if needed. Locks exact40*count vertexbytes and6*(count-2) indexbytes,uploads base/lightmapUV,whitecolor,fog/specularalpha,reciprocaldepth and scaledrhw; writes trianglefan via0x5DF890,unlocks and draws. Actual depth comes from x87 result of0x5DF870 despite misleading pseudocode. Releases temporary clipped vertices after upload. Shared-face decalpasses relock same GPUvertices,restore lightmapUV,set state from decalflags0x20/40/80,write per-decalUV and alpha from owner+76,redraw sameindices; bracket auxiliarymode16 then0 through0x573250 when byte0x92DE28 set. Projectedlight passes bind texture0x664A04,replace UV/color perlight,and redraw; clears faceflag0x40000 whenever projectedlight path enabled,even if zero lights emitted. Finally advances vertexcursor
// bycount,indexcursor3*(count-2),clears batching,and returns1. Ordinary collected decals are not separately drawn in this body. No vertexcount<=48,channelcount<=12,zero-z,degenerate-face or GPU-call failure guards; fixed UVscratch stride24floats pervertex. Leaves packedstate,textures and reused GPUvertex payload modified.
char __cdecl rf_renderer_draw_face_multipass_backend_102(int a1, float *vector, int a3, int a4, int a5, int a6)
{
  float *v7; // eax
  float *v8; // eax
  double v9; // st7
  double v10; // st7
  int v11; // eax
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st7
  double v16; // st7
  int v17; // eax
  float scalar; // [esp+2Ch] [ebp-2DE0h]
  int v19; // [esp+38h] [ebp-2DD4h]
  float *v20; // [esp+3Ch] [ebp-2DD0h]
  int v21; // [esp+40h] [ebp-2DCCh]
  int v22; // [esp+44h] [ebp-2DC8h]
  int v23; // [esp+48h] [ebp-2DC4h]
  float v24; // [esp+4Ch] [ebp-2DC0h]
  float v25; // [esp+50h] [ebp-2DBCh]
  float v26[3]; // [esp+54h] [ebp-2DB8h] BYREF
  float copy_result[3]; // [esp+60h] [ebp-2DACh] BYREF
  float sum_result[3]; // [esp+6Ch] [ebp-2DA0h] BYREF
  float scaled_result[3]; // [esp+78h] [ebp-2D94h] BYREF
  int jj; // [esp+84h] [ebp-2D88h]
  int v31; // [esp+88h] [ebp-2D84h]
  int v32; // [esp+8Ch] [ebp-2D80h]
  int ii; // [esp+90h] [ebp-2D7Ch]
  int v34; // [esp+94h] [ebp-2D78h]
  int n; // [esp+98h] [ebp-2D74h]
  int v36; // [esp+9Ch] [ebp-2D70h]
  int v37; // [esp+A0h] [ebp-2D6Ch]
  int k; // [esp+A4h] [ebp-2D68h]
  float v39; // [esp+A8h] [ebp-2D64h]
  float *v40; // [esp+ACh] [ebp-2D60h]
  int v41; // [esp+B0h] [ebp-2D5Ch]
  float v42[3]; // [esp+B4h] [ebp-2D58h] BYREF
  int v43; // [esp+C0h] [ebp-2D4Ch]
  float *destination; // [esp+C4h] [ebp-2D48h]
  _DWORD *v45; // [esp+C8h] [ebp-2D44h]
  float *v46; // [esp+CCh] [ebp-2D40h]
  char v47[6336]; // [esp+D0h] [ebp-2D3Ch] BYREF
  char v48; // [esp+1990h] [ebp-147Ch] BYREF
  char v49; // [esp+1991h] [ebp-147Bh]
  float out_vector[3]; // [esp+1994h] [ebp-1478h] BYREF
  int v51; // [esp+19A0h] [ebp-146Ch]
  float v52; // [esp+19A4h] [ebp-1468h]
  float *lhs; // [esp+19A8h] [ebp-1464h]
  int m; // [esp+19ACh] [ebp-1460h]
  int v55; // [esp+19B0h] [ebp-145Ch]
  float v56[3]; // [esp+19B4h] [ebp-1458h] BYREF
  float v57; // [esp+19C0h] [ebp-144Ch] BYREF
  float v58; // [esp+19C4h] [ebp-1448h] BYREF
  float v59; // [esp+19C8h] [ebp-1444h]
  int v60; // [esp+19CCh] [ebp-1440h]
  char v61; // [esp+19D3h] [ebp-1439h] BYREF
  float v62; // [esp+19D4h] [ebp-1438h]
  int v63; // [esp+19D8h] [ebp-1434h]
  int v64; // [esp+19DCh] [ebp-1430h]
  float v65; // [esp+19E0h] [ebp-142Ch] BYREF
  int v66; // [esp+19E4h] [ebp-1428h] BYREF
  char v67[4]; // [esp+19E8h] [ebp-1424h] BYREF
  float v68; // [esp+19ECh] [ebp-1420h] BYREF
  int i; // [esp+19F0h] [ebp-141Ch]
  signed int active_world_count; // [esp+19F4h] [ebp-1418h]
  float v71[3]; // [esp+19F8h] [ebp-1414h] BYREF
  float v72[10]; // [esp+1A04h] [ebp-1408h] BYREF
  int v73; // [esp+1A2Ch] [ebp-13E0h] BYREF
  int v74; // [esp+1A30h] [ebp-13DCh]
  int v75; // [esp+1A34h] [ebp-13D8h] BYREF
  _DWORD v76[17]; // [esp+1A38h] [ebp-13D4h] BYREF
  int v77[53]; // [esp+1A7Ch] [ebp-1390h] BYREF
  int v78; // [esp+1B50h] [ebp-12BCh]
  int v79; // [esp+1B54h] [ebp-12B8h]
  _DWORD v80[4]; // [esp+1B58h] [ebp-12B4h]
  float rhs[12]; // [esp+1B68h] [ebp-12A4h] BYREF
  int v82; // [esp+1B98h] [ebp-1274h] BYREF
  int j; // [esp+1B9Ch] [ebp-1270h]
  float v84[1153]; // [esp+1BA0h] [ebp-126Ch] BYREF
  int v85; // [esp+2DA4h] [ebp-68h]
  int v86; // [esp+2DA8h] [ebp-64h]
  int v87; // [esp+2DACh] [ebp-60h]
  _BYTE v88[80]; // [esp+2DB0h] [ebp-5Ch] BYREF
  int v89; // [esp+2E08h] [ebp-4h]

  if ( !rf_fixed_pool_heap_spill_enabled[0] )
    return 0;
  if ( rf_face_is_portal((__int16 *)vector + 20) )
    return 0;
  if ( unk_1DAEDAB )
    a3 = unk_187CC50;
  rf_renderer_flush_immediate_buffers();
  unk_1E014E6 = 1;
  if ( (dword_1E01514 & 1) == 0 )
  {
    dword_1E01514 |= 1u;
    rf_render_state_pack(&dword_1E01510, 6, 1, 3, 3, 1, 0);
    v89 = -1;
  }
  if ( (dword_1E01514 & 2) == 0 )
  {
    dword_1E01514 |= 2u;
    rf_render_state_pack(&dword_1E0150C, 2, 1, 2, 3, 1, 0);
    v89 = -1;
  }
  if ( (dword_1E01514 & 4) == 0 )
  {
    dword_1E01514 |= 4u;
    rf_render_state_pack(&dword_1E01508, 8, 1, 3, 3, 1, 0);
    v89 = -1;
  }
  if ( (dword_1E01514 & 8) == 0 )
  {
    dword_1E01514 |= 8u;
    rf_render_state_pack(&dword_1E01504, 9, 1, 3, 3, 1, 0);
    v89 = -1;
  }
  if ( (dword_1E01514 & 0x10) == 0 )
  {
    dword_1E01514 |= 0x10u;
    rf_render_state_pack(&dword_1E01500, 0, 0, 0, 3, 2, 3);
    v89 = -1;
  }
  v74 = 0;
  v86 = 0;
  v78 = 0;
  v87 = 0;
  v75 = 0;
  v77[0] = 0;
  rf_vector_construct_no_unwind((char *)rhs, 0xCu, 4, rf_vector3_default_construct_noop);
  v79 = 0;
  rf_matrix3_construct((char *)v71);
  v82 = 0;
  rf_vector_construct_no_unwind((char *)v84, 8u, 576, rf_vector3_default_construct_noop);
  v85 = 0;
  if ( ((_DWORD)vector[10] & 0x300000) != 0 )
  {
    if ( ((_DWORD)vector[10] & 0x200000) != 0 )
      v86 = 1;
    v75 = 16;
    v77[0] = 16;
    rf_face_partition_decal_polygons_flag8((int)vector, a1, (int)v76, &v75, (int)v88, v77);
  }
  if ( ((_DWORD)vector[10] & 0x40000) != 0 )
  {
    v78 = 1;
    rf_orientation_matrix_from_direction(v71, vector);
    active_world_count = rf_light_get_active_world_count();
    for ( i = 0; i < active_world_count && v79 < 4; ++i )
    {
      rf_vector3_default_construct_noop(v56);
      rf_light_get_active_entry_position_range_rgb_category(i, v56, (int)v67, &v65, &v68, &v58, &v57, &v61);
      if ( v61 )
      {
        v59 = rf_plane_point_signed_distance(vector, v56);
        if ( v65 > (double)v59 && v59 >= -v65 )
        {
          scalar = -v59;
          v7 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
          v8 = rf_vector_add(v56, sum_result, v7);
          rf_vector_copy(&rhs[3 * v79], copy_result, v8);
          v25 = fabs(v59);
          v59 = v25;
          v24 = v25 * 1.570796370506287 / v65;
          v9 = rf_cos_float(v24);
          v62 = v9 * v65;
          *(float *)&v88[4 * v79 + 64] = v62 + v62;
          *(float *)&v66 = 1.0 - v59 / v65;
          rf_float_clamp_in_place((float *)&v66, 0.0, 1.0);
          *(float *)&v66 = *(float *)&v66 * 255.0;
          v60 = (int)(v68 * *(float *)&v66);
          v63 = (int)(v58 * *(float *)&v66);
          v64 = (int)(v57 * *(float *)&v66);
          if ( v60 > 255 )
            v60 = 255;
          if ( v63 > 255 )
            v63 = 255;
          if ( v64 > 255 )
            v64 = 255;
          v77[v79 + 1] = v60;
          v80[v79] = v63;
          LODWORD(v72[v79++ + 6]) = v64;
        }
      }
    }
  }
  if ( rf_render_state_get_alpha_modulation_selector(&a3) )
    v87 = 1;
  v85 = v75 + v79 + 1;
  if ( byte_663F06 && a6 )
  {
    v45 = dword_18CD298;
    rf_clip_extended_vertex_pool_reset();
    v49 = 0;
    v48 = 0;
    rf_vector_construct_no_unwind(v47, 0x84u, 48, rf_vector_prefix_construct_noop);
    v46 = *((float **)vector + 16);
    v73 = 0;
    while ( v46 )
    {
      destination = (float *)&v47[132 * v73];
      v45[v73] = destination;
      rf_vector_copy(destination, v26, (const float *)(*(_DWORD *)v46 + 12));
      *((_BYTE *)destination + 24) = *(_BYTE *)(*(_DWORD *)v46 + 28);
      *((_BYTE *)destination + 25) = 0;
      v48 |= *((_BYTE *)destination + 24);
      destination[8] = v46[1];
      destination[20] = v46[2];
      destination[9] = v46[3];
      destination[21] = v46[4];
      *((_DWORD *)destination + 7) = 2;
      if ( v86 )
      {
        for ( j = 0; j < v75; ++j )
        {
          v43 = v76[j];
          destination[j + 10] = *(float *)(v43 + 8 * v73);
          destination[j + 22] = *(float *)(v43 + 8 * v73 + 4);
          ++*((_DWORD *)destination + 7);
        }
      }
      if ( v78 )
      {
        for ( j = 0; j < v79; ++j )
        {
          rf_vector_subtract(*(const float **)v46, v42, &rhs[3 * j]);
          v14 = rf_vector_dot(v42, v71);
          destination[v75 + 10 + j] = v14 / *(float *)&v88[4 * j + 64] + 0.5;
          v15 = rf_vector_dot(v42, v72);
          destination[v75 + 22 + j] = v15 / *(float *)&v88[4 * j + 64] + 0.5;
          ++*((_DWORD *)destination + 7);
        }
      }
      if ( *((_DWORD *)v46 + 5) == *((_DWORD *)vector + 16) )
        v20 = nullptr;
      else
        v20 = *((float **)v46 + 5);
      v46 = v20;
      ++v73;
    }
    v45 = rf_clip_polygon_extended_uv_outcode_planes(dword_18CD298, dword_18CD1D0, &v73, &v48, 0);
    if ( v73 < 3 || v49 )
    {
      unk_1E014E6 = 0;
      return 0;
    }
    v74 = v73;
    if ( dword_18CCFBC + v73 > 6000 || unk_18CCFC0 + unk_1E014EC + 3 * (v73 - 2) > 10000 )
    {
      dword_18CCFBC = 0;
      unk_18CCFC0 = 0;
    }
    rf_d3d8_bind_textures_and_apply_state(a3, a4, a5);
    if ( dword_18CCFBC )
      v19 = unk_1DAEE08;
    else
      v19 = unk_1DAEE04;
    v41 = v19;
    (*(void (__stdcall **)(_DWORD *, int, int, int *, int))(*dword_1DAEDB0 + 44))(
      dword_1DAEDB0,
      40 * dword_18CCFBC,
      40 * v73,
      &v82,
      v19);
    (*(void (__stdcall **)(_DWORD *, int, int, void *, int))(*dword_1DAEDB4 + 44))(
      dword_1DAEDB4,
      2 * unk_18CCFC0,
      6 * (v73 - 2),
      &unk_1DAEDBC,
      v41);
    j = 0;
    while ( j < v73 )
    {
      v40 = (float *)v45[j];
      v39 = 1.0 / v40[2];
      v16 = v40[2];
      rf_renderer_depth_from_reciprocal_wrapper(COERCE_INT(v40[2]), v39);
      *(float *)(v82 + 8) = v16;
      *(float *)v82 = *v40 * v39 * unk_18CD35C + unk_18CD358;
      *(float *)(v82 + 4) = v40[1] * v39 * unk_18CD364 + unk_18CD360;
      *(_DWORD *)(v82 + 16) = -1;
      v17 = rf_renderer_linear_depth_fade_byte(v40[2]);
      *(_DWORD *)(v82 + 20) = v17 << 24;
      *(float *)(v82 + 24) = v40[8];
      *(float *)(v82 + 28) = v40[20];
      *(float *)(v82 + 32) = v40[9];
      *(float *)(v82 + 36) = v40[21];
      *(float *)(v82 + 12) = v39 * flt_6649F8;
      v84[24 * j] = v40[9];
      v84[24 * j + 1] = v40[21];
      if ( v86 )
      {
        for ( k = 0; k < v75; ++k )
        {
          v84[24 * j + 2 + 2 * k] = v40[k + 10];
          v84[24 * j + 3 + 2 * k] = v40[k + 22];
        }
      }
      if ( v78 )
      {
        for ( k = 0; k < v79; ++k )
        {
          v37 = v75 + k;
          v84[24 * j + 2 + 2 * v75 + 2 * k] = v40[v75 + 10 + k];
          v84[24 * j + 3 + 2 * v37] = v40[v37 + 22];
        }
      }
      ++j;
      v82 += 40;
    }
    rf_renderer_write_triangle_fan_indices_no_advance(v73);
    (*(void (__thiscall **)(_DWORD *, _DWORD *))(*dword_1DAEDB0 + 48))(dword_1DAEDB0, dword_1DAEDB0);
    (*(void (__stdcall **)(_DWORD *))(*dword_1DAEDB4 + 48))(dword_1DAEDB4);
    (*(void (__thiscall **)(int, int, int, _DWORD, int, _DWORD, int))(*(_DWORD *)dword_1DAEDC4 + 284))(
      dword_1DAEDC4,
      dword_1DAEDC4,
      4,
      dword_18CCFBC,
      v73,
      unk_18CCFC0,
      v73 - 2);
    for ( j = 0; j < v73; ++j )
    {
      if ( (*(_BYTE *)(v45[j] + 25) & 4) != 0 )
        rf_clip_extended_vertex_pool_release(v45[j]);
    }
  }
  else
  {
    v73 = 0;
    for ( m = *((_DWORD *)vector + 16); m; m = v23 )
    {
      ++v73;
      if ( *(_DWORD *)(m + 20) == *((_DWORD *)vector + 16) )
        v23 = 0;
      else
        v23 = *(_DWORD *)(m + 20);
    }
    if ( dword_18CCFBC + v73 > 6000 || unk_18CCFC0 + unk_1E014EC + 3 * (v73 - 2) > 10000 )
    {
      dword_18CCFBC = 0;
      unk_18CCFC0 = 0;
    }
    rf_d3d8_bind_textures_and_apply_state(a3, a4, a5);
    if ( dword_18CCFBC )
      v22 = unk_1DAEE08;
    else
      v22 = unk_1DAEE04;
    v55 = v22;
    (*(void (__stdcall **)(_DWORD *, int, int, int *, int))(*dword_1DAEDB0 + 44))(
      dword_1DAEDB0,
      40 * dword_18CCFBC,
      40 * v73,
      &v82,
      v22);
    (*(void (__thiscall **)(_DWORD *, _DWORD *, int, int, void *, int))(*dword_1DAEDB4 + 44))(
      dword_1DAEDB4,
      dword_1DAEDB4,
      2 * unk_18CCFC0,
      6 * (v73 - 2),
      &unk_1DAEDBC,
      v55);
    m = *((_DWORD *)vector + 16);
    while ( m )
    {
      lhs = *(float **)m;
      v52 = 1.0 / lhs[5];
      v10 = lhs[5];
      rf_renderer_depth_from_reciprocal_wrapper(COERCE_INT(lhs[5]), v52);
      *(float *)(v82 + 8) = v10;
      *(float *)v82 = lhs[3] * v52 * unk_18CD35C + unk_18CD358;
      *(float *)(v82 + 4) = lhs[4] * v52 * unk_18CD364 + unk_18CD360;
      *(_DWORD *)(v82 + 16) = -1;
      v11 = rf_renderer_linear_depth_fade_byte(lhs[5]);
      *(_DWORD *)(v82 + 20) = v11 << 24;
      *(float *)(v82 + 24) = *(float *)(m + 4);
      *(float *)(v82 + 28) = *(float *)(m + 8);
      *(float *)(v82 + 12) = v52 * flt_6649F8;
      *(float *)(v82 + 32) = *(float *)(m + 12);
      *(float *)(v82 + 36) = *(float *)(m + 16);
      if ( rf_detail_textures_enabled == 1 && byte_187CCF0 )
        *(float *)&v77[v74 + 5] = lhs[5] * unk_18CD294;
      v84[24 * v74] = *(float *)(m + 12);
      v84[24 * v74 + 1] = *(float *)(m + 16);
      if ( v86 )
      {
        for ( j = 0; j < v75; ++j )
        {
          v51 = v76[j];
          v84[24 * v74 + 2 + 2 * j] = *(float *)(v51 + 8 * v74);
          v84[24 * v74 + 3 + 2 * j] = *(float *)(v51 + 8 * v74 + 4);
        }
      }
      if ( v78 )
      {
        for ( j = 0; j < v79; ++j )
        {
          rf_vector_subtract(lhs, out_vector, &rhs[3 * j]);
          v12 = rf_vector_dot(out_vector, v71);
          v84[24 * v74 + 2 + 2 * v75 + 2 * j] = v12 / *(float *)&v88[4 * j + 64] + 0.5;
          v13 = rf_vector_dot(out_vector, v72);
          v84[24 * v74 + 3 + 2 * v75 + 2 * j] = v13 / *(float *)&v88[4 * j + 64] + 0.5;
        }
      }
      if ( *(_DWORD *)(m + 20) == *((_DWORD *)vector + 16) )
        v21 = 0;
      else
        v21 = *(_DWORD *)(m + 20);
      m = v21;
      v82 += 40;
      ++v74;
    }
    rf_renderer_write_triangle_fan_indices_no_advance(v73);
    (*(void (__thiscall **)(_DWORD *, _DWORD *))(*dword_1DAEDB0 + 48))(dword_1DAEDB0, dword_1DAEDB0);
    (*(void (__stdcall **)(_DWORD *))(*dword_1DAEDB4 + 48))(dword_1DAEDB4);
    (*(void (__thiscall **)(int, int, int, _DWORD, int, _DWORD, int))(*(_DWORD *)dword_1DAEDC4 + 284))(
      dword_1DAEDC4,
      dword_1DAEDC4,
      4,
      dword_18CCFBC,
      v73,
      unk_18CCFC0,
      v73 - 2);
  }
  if ( v86 )
  {
    if ( rf_fixed_pool_heap_spill_enabled[0] )
      rf_renderer_set_auxiliary_mode_clamped_0_16(16);
    rf_renderer_bind_texture_handle(1, a5, 0, (int)&unk_1E014D4, (int)&unk_1E014CC, 1);
    (*(void (__thiscall **)(_DWORD *, _DWORD *, int, int, int *, _DWORD))(*dword_1DAEDB0 + 44))(
      dword_1DAEDB0,
      dword_1DAEDB0,
      40 * dword_18CCFBC,
      40 * v73,
      &v82,
      0);
    v36 = v82;
    for ( n = 0; n < v74; ++n )
    {
      *(float *)(v36 + 40 * n + 32) = v84[24 * n];
      *(float *)(v36 + 40 * n + 36) = v84[24 * n + 1];
    }
    (*(void (__stdcall **)(_DWORD *))(*dword_1DAEDB0 + 48))(dword_1DAEDB0);
    for ( j = 0; j < v75; ++j )
    {
      v34 = v76[j];
      rf_renderer_bind_texture_handle(
        0,
        *(_DWORD *)(*(_DWORD *)(v34 + 1316) + 60),
        0,
        (int)&flt_1E014DC,
        (int)&flt_1E014D0,
        1);
      if ( (*(_DWORD *)(*(_DWORD *)(v34 + 1316) + 80) & 0x20) != 0 )
      {
        rf_renderer_apply_packed_render_state(dword_1E0150C);
      }
      else if ( (*(_DWORD *)(*(_DWORD *)(v34 + 1316) + 80) & 0x40) != 0 )
      {
        rf_renderer_apply_packed_render_state(dword_1E01508);
      }
      else if ( (*(_DWORD *)(*(_DWORD *)(v34 + 1316) + 80) & 0x80) != 0 )
      {
        rf_renderer_apply_packed_render_state(dword_1E01504);
      }
      else
      {
        rf_renderer_apply_packed_render_state(dword_1E01510);
      }
      (*(void (__stdcall **)(_DWORD *, int, int, int *, _DWORD))(*dword_1DAEDB0 + 44))(
        dword_1DAEDB0,
        40 * dword_18CCFBC,
        40 * v73,
        &v82,
        0);
      v36 = v82;
      for ( ii = 0; ii < v74; ++ii )
      {
        *(float *)(v36 + 40 * ii + 24) = v84[24 * ii + 2 + 2 * j];
        *(float *)(v36 + 40 * ii + 28) = v84[24 * ii + 3 + 2 * j];
        *(_DWORD *)(v36 + 40 * ii + 16) = (unsigned int)&unk_FF0000
                                        | (*(unsigned __int8 *)(*(_DWORD *)(v34 + 1316) + 76) << 24)
                                        | 0xFFFF;
      }
      (*(void (__thiscall **)(_DWORD *, _DWORD *))(*dword_1DAEDB0 + 48))(dword_1DAEDB0, dword_1DAEDB0);
      (*(void (__stdcall **)(int, int, _DWORD, int, _DWORD, int))(*(_DWORD *)dword_1DAEDC4 + 284))(
        dword_1DAEDC4,
        4,
        dword_18CCFBC,
        v73,
        unk_18CCFC0,
        v73 - 2);
    }
    if ( rf_fixed_pool_heap_spill_enabled[0] )
      rf_renderer_set_auxiliary_mode_clamped_0_16(0);
  }
  if ( v78 )
  {
    rf_d3d8_bind_textures_and_apply_state(SLODWORD(rf_particle_glow_billboard_render_state), dword_664A04, -1);
    for ( j = 0; j < v79; ++j )
    {
      v31 = v75 + j;
      (*(void (__thiscall **)(_DWORD *, _DWORD *, int, int, int *, _DWORD))(*dword_1DAEDB0 + 44))(
        dword_1DAEDB0,
        dword_1DAEDB0,
        40 * dword_18CCFBC,
        40 * v73,
        &v82,
        0);
      v32 = v82;
      for ( jj = 0; jj < v74; ++jj )
      {
        *(float *)(v32 + 40 * jj + 24) = v84[24 * jj + 2 + 2 * v31];
        *(float *)(v32 + 40 * jj + 28) = v84[24 * jj + 3 + 2 * v31];
        *(_DWORD *)(v32 + 40 * jj + 16) = (unsigned __int8)LODWORD(v72[j + 6])
                                        | ((unsigned __int8)v80[j] << 8)
                                        | ((unsigned __int8)v77[j + 1] << 16)
                                        | 0xFF000000;
      }
      (*(void (__stdcall **)(_DWORD *))(*dword_1DAEDB0 + 48))(dword_1DAEDB0);
      (*(void (__thiscall **)(int, int, int, _DWORD, int, _DWORD, int))(*(_DWORD *)dword_1DAEDC4 + 284))(
        dword_1DAEDC4,
        dword_1DAEDC4,
        4,
        dword_18CCFBC,
        v73,
        unk_18CCFC0,
        v73 - 2);
    }
    *((_DWORD *)vector + 10) &= ~0x40000u;
  }
  dword_18CCFBC += v73;
  unk_18CCFC0 += 3 * (v73 - 2);
  unk_1E014E6 = 0;
  return 1;
}

