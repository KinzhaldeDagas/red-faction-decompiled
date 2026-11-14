// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EACA0 rf_renderer_draw_face_batch_backend_102
// UNREALRED VERIFIED [face-batch-20261028]: Main six-argument face-array backend: solid/context,room,count,face pointers,two mode bytes. Computes depth-bias values from0x581AF0(0.05/0.5),flushes prior immediate state if0x1E014E5,set batching byte0x1E014E6=1,clear packet count0x1E41998. Packed base state chosen by arg5 then arg6 then default globals0x18CCFDC/FE0/FF0. Locks40-byte GPU vertex ring (6000 slots),rewinds cursor if>4500. Per face walks circular vertices+64; when vertex stamp+24<context+860 computes camera-space position using global matrix0x18CD4B4 and camera0x18CD5E8. With byte0x663F06 enabled also caches camera outcodes+28; ANDnonzero skips face,ORnonzero chooses software clipping. Otherwise direct projection,without outcode rejection. Resolves base bitmap+48 and optional signed lightmap index+54 into nested bitmap handle. Flushes/relocks/reset cached packet indices when vertex
// cursor>5488 OR packet count+12>=100. Collects max16 flag8 and16 nonflag8 decal polygons per face. Face flag0x40000 builds at most4 projected active-light contributions whose signed face-plane distance lies in[-radius,radius); computes projected centers,cosine extents and distance-faded colors. Clipped path builds48 local132-byte extended UV vertices,dispatches0x5C8750 over outcodebits1..64; direct path uses cached camera coordinates. Both produce40-byte screen vertices with reciprocal-depth scaling0x5DF870,specular-alpha fade0x5A4140,base UV and scratch lightmap/overlay UV. No guarantee of clipping outcode0x80; no general zero-z or per-layer scratch-capacity check. Increments face statistic0xA4205C. Multitexture available OR arg6 emits one base+lightmap packet priority3; otherwise base priority3 then separate lightmap priority4. Flag8 overlays reuse face vertices,alpha from owner+76,mode
// state from flags0x20/0x40/0x80,priority2. Projected lights queue texture0x664A04 priority0; clears face0x40000 only if at least one contribution emitted. If byte0x663F04,ordinary clipped decal polygons are separately transformed/clipped,depth-biased when z>scaled0.5 and submitted priority1 with texture/lightmap. Packet flush draws priorities5..0,so actual draw order is numeric priority,not insertion order. Ends0x5ECF90 and clears batching byte. Does not restore prior packed renderer state,texture bindings or mutated vertex caches. Fixed local clip arrays and per-vertex UV scratch strides have no independent total-overlay clamp.
int __cdecl rf_renderer_draw_face_batch_backend_102(int a1, int a2, int a3, int a4, char a5, char a6)
{
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  double v10; // st7
  int v11; // eax
  double v12; // st7
  double v13; // st7
  double v14; // st7
  int v15; // eax
  double v16; // st7
  int v17; // eax
  double v18; // st7
  double v19; // st7
  unsigned __int8 v20; // al
  int v21; // eax
  double v22; // st7
  int v23; // eax
  double v24; // st7
  int result; // eax
  float scalar; // [esp+2Ch] [ebp-3EA4h]
  int v27; // [esp+38h] [ebp-3E98h]
  float *v28; // [esp+3Ch] [ebp-3E94h]
  char v29; // [esp+40h] [ebp-3E90h]
  char v30; // [esp+44h] [ebp-3E8Ch]
  char v31; // [esp+48h] [ebp-3E88h]
  float v32; // [esp+4Ch] [ebp-3E84h]
  float v33; // [esp+50h] [ebp-3E80h]
  float v34[3]; // [esp+54h] [ebp-3E7Ch] BYREF
  float v35[3]; // [esp+60h] [ebp-3E70h] BYREF
  float v36[3]; // [esp+6Ch] [ebp-3E64h] BYREF
  float v37[3]; // [esp+78h] [ebp-3E58h] BYREF
  float sum_result[3]; // [esp+84h] [ebp-3E4Ch] BYREF
  float scaled_result[3]; // [esp+90h] [ebp-3E40h] BYREF
  float v40[3]; // [esp+9Ch] [ebp-3E34h] BYREF
  float v41[3]; // [esp+A8h] [ebp-3E28h] BYREF
  float copy_result[3]; // [esp+B4h] [ebp-3E1Ch] BYREF
  float out_vector[3]; // [esp+C0h] [ebp-3E10h] BYREF
  float *v44; // [esp+CCh] [ebp-3E04h]
  float v45; // [esp+D0h] [ebp-3E00h]
  float v46; // [esp+D4h] [ebp-3DFCh] BYREF
  float v47; // [esp+D8h] [ebp-3DF8h]
  float v48; // [esp+DCh] [ebp-3DF4h]
  float *v49; // [esp+E0h] [ebp-3DF0h]
  float *v50; // [esp+E4h] [ebp-3DECh]
  float v51; // [esp+E8h] [ebp-3DE8h]
  float *v52; // [esp+ECh] [ebp-3DE4h]
  int v53; // [esp+F0h] [ebp-3DE0h]
  float *v54; // [esp+F4h] [ebp-3DDCh]
  int v55; // [esp+F8h] [ebp-3DD8h]
  float source[12]; // [esp+FCh] [ebp-3DD4h] BYREF
  _DWORD *v57; // [esp+12Ch] [ebp-3DA4h]
  int v58; // [esp+130h] [ebp-3DA0h]
  int v59; // [esp+134h] [ebp-3D9Ch] BYREF
  int v60; // [esp+138h] [ebp-3D98h]
  char v61[2304]; // [esp+13Ch] [ebp-3D94h] BYREF
  float *v62; // [esp+A3Ch] [ebp-3494h]
  char v63; // [esp+A40h] [ebp-3490h] BYREF
  char v64; // [esp+A41h] [ebp-348Fh]
  int v65; // [esp+A44h] [ebp-348Ch]
  int *v66; // [esp+A48h] [ebp-3488h]
  int v67; // [esp+A4Ch] [ebp-3484h]
  int jj; // [esp+A50h] [ebp-3480h]
  int v69; // [esp+A54h] [ebp-347Ch]
  int v70; // [esp+A58h] [ebp-3478h] BYREF
  int ii; // [esp+A5Ch] [ebp-3474h]
  int v72; // [esp+A60h] [ebp-3470h]
  _DWORD *v73; // [esp+A64h] [ebp-346Ch]
  int n; // [esp+A68h] [ebp-3468h]
  int v75; // [esp+A6Ch] [ebp-3464h]
  float v76[3]; // [esp+A70h] [ebp-3460h] BYREF
  int v77; // [esp+A7Ch] [ebp-3454h]
  float v78; // [esp+A80h] [ebp-3450h]
  float *v79; // [esp+A84h] [ebp-344Ch]
  int v80; // [esp+A88h] [ebp-3448h]
  float *v81; // [esp+A8Ch] [ebp-3444h]
  int v82; // [esp+A90h] [ebp-3440h]
  int m; // [esp+A94h] [ebp-343Ch]
  float v84; // [esp+A98h] [ebp-3438h]
  float *v85; // [esp+A9Ch] [ebp-3434h]
  float *v86; // [esp+AA0h] [ebp-3430h]
  float v87[3]; // [esp+AA4h] [ebp-342Ch] BYREF
  int v88; // [esp+AB0h] [ebp-3420h]
  float *v89; // [esp+AB4h] [ebp-341Ch]
  _DWORD *v90; // [esp+AB8h] [ebp-3418h]
  float *v91; // [esp+ABCh] [ebp-3414h]
  int v92; // [esp+AC0h] [ebp-3410h] BYREF
  char v93[6340]; // [esp+AC4h] [ebp-340Ch] BYREF
  char v94; // [esp+2388h] [ebp-1B48h] BYREF
  char v95; // [esp+2389h] [ebp-1B47h]
  float v96; // [esp+238Ch] [ebp-1B44h]
  float *v97; // [esp+2390h] [ebp-1B40h]
  float v98; // [esp+2394h] [ebp-1B3Ch]
  int v99; // [esp+2398h] [ebp-1B38h] BYREF
  int v100; // [esp+239Ch] [ebp-1B34h]
  char *v101; // [esp+23A0h] [ebp-1B30h]
  signed int j; // [esp+23A4h] [ebp-1B2Ch]
  signed int v103; // [esp+23A8h] [ebp-1B28h]
  float *v104; // [esp+23ACh] [ebp-1B24h]
  float *lhs; // [esp+23B0h] [ebp-1B20h]
  int v106; // [esp+23B4h] [ebp-1B1Ch]
  int v107; // [esp+23B8h] [ebp-1B18h]
  int v108; // [esp+23BCh] [ebp-1B14h]
  int v109; // [esp+23C0h] [ebp-1B10h]
  int v110; // [esp+23C4h] [ebp-1B0Ch]
  int v111; // [esp+23C8h] [ebp-1B08h]
  _BYTE v112[16]; // [esp+23CCh] [ebp-1B04h] BYREF
  int i; // [esp+23E0h] [ebp-1AF0h]
  int v114; // [esp+23E4h] [ebp-1AECh]
  float *v115; // [esp+23E8h] [ebp-1AE8h]
  float v116[3]; // [esp+23ECh] [ebp-1AE4h] BYREF
  float v117[6]; // [esp+23F8h] [ebp-1AD8h] BYREF
  int v118; // [esp+2410h] [ebp-1AC0h] BYREF
  int v119; // [esp+2414h] [ebp-1ABCh]
  int v120; // [esp+2418h] [ebp-1AB8h] BYREF
  unsigned int v121; // [esp+241Ch] [ebp-1AB4h] BYREF
  float v122; // [esp+2420h] [ebp-1AB0h]
  _DWORD v123[16]; // [esp+2424h] [ebp-1AACh] BYREF
  int v124; // [esp+2464h] [ebp-1A6Ch] BYREF
  int v125; // [esp+2468h] [ebp-1A68h] BYREF
  unsigned int v126; // [esp+246Ch] [ebp-1A64h] BYREF
  int v127; // [esp+2470h] [ebp-1A60h]
  int v128; // [esp+2474h] [ebp-1A5Ch] BYREF
  unsigned int v129; // [esp+2478h] [ebp-1A58h] BYREF
  float destination; // [esp+247Ch] [ebp-1A54h] BYREF
  float v131; // [esp+2480h] [ebp-1A50h]
  float v132; // [esp+2484h] [ebp-1A4Ch]
  float v133[12]; // [esp+2488h] [ebp-1A48h] BYREF
  float *vector; // [esp+24B8h] [ebp-1A18h]
  int v135; // [esp+24BCh] [ebp-1A14h]
  float v136; // [esp+24C0h] [ebp-1A10h]
  int v137; // [esp+24C4h] [ebp-1A0Ch]
  int v138; // [esp+24C8h] [ebp-1A08h]
  float v139[1153]; // [esp+24CCh] [ebp-1A04h] BYREF
  int k; // [esp+36D0h] [ebp-800h]
  float rhs[3]; // [esp+36D4h] [ebp-7FCh] BYREF
  int v142; // [esp+36E0h] [ebp-7F0h]
  int v143; // [esp+36E4h] [ebp-7ECh] BYREF
  int v144; // [esp+36E8h] [ebp-7E8h]
  float v145[4]; // [esp+36ECh] [ebp-7E4h]
  _BYTE Src[1920]; // [esp+36FCh] [ebp-7D4h] BYREF
  int v147[16]; // [esp+3E7Ch] [ebp-54h] BYREF
  int v148; // [esp+3EBCh] [ebp-14h] BYREF
  int v149; // [esp+3EC0h] [ebp-10h]
  int v150; // [esp+3ECCh] [ebp-4h]

  v122 = rf_renderer_scale_camera_depth_bias(0.050000001);
  v136 = rf_renderer_scale_camera_depth_bias(0.5);
  rf_vector_construct_no_unwind((char *)v133, 0xCu, 4, rf_vector3_default_construct_noop);
  rf_vector_construct_no_unwind((char *)v139, 8u, 576, rf_vector3_default_construct_noop);
  v124 = 0;
  rf_matrix3_construct((char *)v116);
  rf_dword_construct_invalid_minus_one(&v121);
  rf_dword_construct_invalid_minus_one(&v126);
  v128 = -1;
  v125 = -1;
  v143 = -1;
  v148 = -1;
  v118 = -1;
  v137 = -1;
  v138 = -1;
  v114 = -1;
  v144 = -1;
  v129 = unk_187CC4C;
  rf_vector3_default_construct_noop(&destination);
  if ( unk_1E014E5 )
    rf_renderer_flush_immediate_buffers();
  unk_1E014E6 = 1;
  unk_1E41998 = 0;
  if ( a5 )
  {
    v121 = unk_18CCFDC;
  }
  else if ( a6 )
  {
    v121 = unk_18CCFE0;
  }
  else
  {
    v121 = unk_18CCFF0;
  }
  if ( (int)dword_18CCFBC <= 4500 )
  {
    v135 = unk_1DAEE08;
  }
  else
  {
    v135 = unk_1DAEE04;
    dword_18CCFBC = 0;
  }
  unk_1E014E8 = 0;
  (*(void (__thiscall **)(_DWORD *, _DWORD *, int, int, void *, int))(*dword_1DAEDB0 + 44))(
    dword_1DAEDB0,
    dword_1DAEDB0,
    40 * dword_18CCFBC,
    40 * (6000 - dword_18CCFBC),
    &unk_1DAEDB8,
    v135);
  v115 = &flt_18CD4B4;
  v149 = *(_DWORD *)(a1 + 860);
  rf_vector3_copy_return_destination(rhs, &flt_18CD5E8);
  for ( i = 0; i < a3; ++i )
  {
    v107 = -1;
    v111 = 0;
    v119 = 0;
    vector = *(float **)(a4 + 4 * i);
    v108 = *((_DWORD *)vector + 16);
    v106 = v108;
    if ( byte_663F06 )
    {
      do
      {
        lhs = *(float **)v106;
        if ( *((_DWORD *)lhs + 6) < v149 )
        {
          *((_DWORD *)lhs + 6) = v149;
          v6 = rf_vector_subtract(lhs, out_vector, rhs);
          rf_vector_copy(&destination, copy_result, v6);
          lhs[3] = destination * *v115 + v131 * v115[1] + v132 * v115[2];
          lhs[4] = destination * v115[3] + v131 * v115[4] + v132 * v115[5];
          lhs[5] = destination * v115[6] + v131 * v115[7] + v132 * v115[8];
          v142 = (unsigned __int8)rf_camera_frustum_outcode(lhs + 3);
          *((_DWORD *)lhs + 7) = v142;
        }
        else
        {
          v142 = *((_DWORD *)lhs + 7);
        }
        v107 &= v142;
        v111 |= v142;
        v106 = *(_DWORD *)(v106 + 20);
      }
      while ( v106 != v108 );
      if ( v107 )
        continue;
    }
    else
    {
      v111 = 0;
      v107 = 0;
      do
      {
        v104 = *(float **)v106;
        if ( *((_DWORD *)v104 + 6) < v149 )
        {
          *((_DWORD *)v104 + 6) = v149;
          v7 = rf_vector_subtract(v104, v41, rhs);
          rf_vector_copy(&destination, v40, v7);
          v104[3] = destination * *v115 + v131 * v115[1] + v132 * v115[2];
          v104[4] = destination * v115[3] + v131 * v115[4] + v132 * v115[5];
          v104[5] = destination * v115[6] + v131 * v115[7] + v132 * v115[8];
        }
        v106 = *(_DWORD *)(v106 + 20);
      }
      while ( v106 != v108 );
    }
    v110 = *((__int16 *)vector + 27);
    if ( v110 > -1 )
      v110 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(a1 + 192), v110) + 12) + 16);
    v109 = *((_DWORD *)vector + 12);
    if ( (int)dword_18CCFBC > 5488 || unk_1E41998 + 12 >= 100 )
    {
      rf_renderer_flush_world_face_packets();
      dword_18CCFBC = 0;
      unk_1E014E8 = 0;
      (*(void (__stdcall **)(_DWORD *, _DWORD, int, void *, _DWORD))(*dword_1DAEDB0 + 44))(
        dword_1DAEDB0,
        0,
        240000,
        &unk_1DAEDB8,
        unk_1DAEE04);
      unk_1E41998 = 0;
      v128 = -1;
      v125 = -1;
      v143 = -1;
      v148 = -1;
      v118 = -1;
      v137 = -1;
      v144 = -1;
      v138 = -1;
      v114 = -1;
      v129 = unk_187CC4C;
    }
    if ( ((_DWORD)vector[10] & 0x300000) != 0 )
    {
      v124 = 16;
      v120 = 16;
      rf_face_partition_decal_polygons_flag8((int)vector, a1, (int)v123, &v120, (int)v147, &v124);
    }
    else
    {
      v124 = 0;
      v120 = 0;
    }
    v127 = 0;
    if ( ((_DWORD)vector[10] & 0x40000) != 0 )
    {
      rf_orientation_matrix_from_direction(v116, vector);
      v103 = rf_light_active_world_count;
      v101 = v112;
      for ( j = 0; j < v103 && v127 < 4; ++j )
      {
        v97 = (float *)rf_light_active_world_records[j];
        v96 = rf_plane_point_signed_distance(vector, v97 + 3);
        if ( v97[15] > (double)v96 && v96 >= -v97[15] )
        {
          scalar = -v96;
          v8 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
          v9 = rf_vector_add(v97 + 3, sum_result, v8);
          rf_vector_copy(&v133[3 * v127], v37, v9);
          v33 = fabs(v96);
          v96 = v33;
          v32 = v33 * 1.570796370506287 / v97[15];
          v10 = rf_cos_float(v32);
          v98 = v10 * v97[15];
          v145[v127] = v98 + v98;
          *(float *)&v99 = 255.0 - v96 * 255.0 / v97[15];
          rf_float_clamp_in_place((float *)&v99, 0.0, 255.0);
          v11 = (int)(v97[18] * *(float *)&v99);
          v100 = v11;
          if ( v11 <= 255 )
            v31 = v100;
          else
            v31 = -1;
          *v101 = v31;
          v100 = (int)(v97[17] * *(float *)&v99);
          if ( v100 <= 255 )
            v30 = v100;
          else
            v30 = -1;
          v101[1] = v30;
          v100 = (int)(v97[16] * *(float *)&v99);
          if ( v100 <= 255 )
            v29 = v100;
          else
            v29 = -1;
          v101[2] = v29;
          v101[3] = -1;
          ++v127;
          v101 += 4;
        }
      }
    }
    if ( v111 )
    {
      v90 = dword_18CD298;
      rf_clip_extended_vertex_pool_reset();
      v95 = 0;
      v94 = 0;
      rf_vector_construct_no_unwind(v93, 0x84u, 48, rf_vector_prefix_construct_noop);
      v91 = *((float **)vector + 16);
      v92 = 0;
      while ( v91 )
      {
        v89 = (float *)&v93[132 * v92];
        v90[v92] = v89;
        rf_vector_copy(v89, v36, (const float *)(*(_DWORD *)v91 + 12));
        *((_BYTE *)v89 + 24) = *(_BYTE *)(*(_DWORD *)v91 + 28);
        *((_BYTE *)v89 + 25) = 0;
        v94 |= *((_BYTE *)v89 + 24);
        v89[8] = v91[1];
        v89[20] = v91[2];
        v89[9] = v91[3];
        v89[21] = v91[4];
        *((_DWORD *)v89 + 7) = 2;
        if ( v120 )
        {
          for ( k = 0; k < v120; ++k )
          {
            v88 = v123[k];
            v89[k + 10] = *(float *)(v88 + 8 * v92);
            v89[k + 22] = *(float *)(v88 + 8 * v92 + 4);
            ++*((_DWORD *)v89 + 7);
          }
        }
        if ( v127 )
        {
          for ( k = 0; k < v127; ++k )
          {
            rf_vector_subtract(*(const float **)v91, v87, &v133[3 * k]);
            v12 = rf_vector_dot(v87, v116);
            v89[v120 + 10 + k] = v12 / v145[k] + 0.5;
            v13 = rf_vector_dot(v87, v117);
            v89[v120 + 22 + k] = v13 / v145[k] + 0.5;
            ++*((_DWORD *)v89 + 7);
          }
        }
        if ( *((_DWORD *)v91 + 5) == *((_DWORD *)vector + 16) )
          v28 = nullptr;
        else
          v28 = *((float **)v91 + 5);
        v91 = v28;
        ++v92;
      }
      v90 = rf_clip_polygon_extended_uv_outcode_planes(dword_18CD298, dword_18CD1D0, &v92, &v94, 0);
      if ( v92 < 3 || v95 )
        continue;
      v119 = v92;
      v86 = (float *)Src;
      k = 0;
      while ( k < v92 )
      {
        v85 = (float *)v90[k];
        v84 = 1.0 / v85[2];
        v14 = v85[2];
        rf_renderer_depth_from_reciprocal_wrapper(COERCE_INT(v85[2]), v84);
        v86[2] = v14;
        *v86 = *v85 * v84 * unk_18CD35C + unk_18CD358;
        v86[1] = v85[1] * v84 * unk_18CD364 + unk_18CD360;
        v86[4] = NAN;
        v15 = rf_renderer_linear_depth_fade_byte(v85[2]);
        *((_DWORD *)v86 + 5) = v15 << 24;
        v86[6] = v85[8];
        v86[7] = v85[20];
        v86[3] = v84 * flt_6649F8;
        v139[24 * k] = v85[9];
        v139[24 * k + 1] = v85[21];
        if ( v120 )
        {
          for ( m = 0; m < v120; ++m )
          {
            v139[24 * k + 2 + 2 * m] = v85[m + 10];
            v139[24 * k + 3 + 2 * m] = v85[m + 22];
          }
        }
        if ( v127 )
        {
          for ( m = 0; m < v127; ++m )
          {
            v82 = v120 + m;
            v139[24 * k + 2 + 2 * v120 + 2 * m] = v85[v120 + 10 + m];
            v139[24 * k + 3 + 2 * v82] = v85[v82 + 22];
          }
        }
        ++k;
        v86 += 10;
      }
      for ( k = 0; k < v92; ++k )
      {
        if ( (*(_BYTE *)(v90[k] + 25) & 4) != 0 )
          rf_clip_extended_vertex_pool_release(v90[k]);
      }
    }
    else
    {
      v81 = (float *)Src;
      v80 = *((_DWORD *)vector + 16);
      while ( v80 )
      {
        v79 = *(float **)v80;
        v78 = 1.0 / v79[5];
        v16 = v79[5];
        rf_renderer_depth_from_reciprocal_wrapper(COERCE_INT(v79[5]), v78);
        v81[2] = v16;
        *v81 = v79[3] * v78 * unk_18CD35C + unk_18CD358;
        v81[1] = v79[4] * v78 * unk_18CD364 + unk_18CD360;
        v81[4] = NAN;
        v17 = rf_renderer_linear_depth_fade_byte(v79[5]);
        *((_DWORD *)v81 + 5) = v17 << 24;
        v81[6] = *(float *)(v80 + 4);
        v81[7] = *(float *)(v80 + 8);
        v81[3] = v78 * flt_6649F8;
        v139[24 * v119] = *(float *)(v80 + 12);
        v139[24 * v119 + 1] = *(float *)(v80 + 16);
        if ( v120 )
        {
          for ( k = 0; k < v120; ++k )
          {
            v77 = v123[k];
            v139[24 * v119 + 2 + 2 * k] = *(float *)(v77 + 8 * v119);
            v139[24 * v119 + 3 + 2 * k] = *(float *)(v77 + 8 * v119 + 4);
          }
        }
        if ( v127 )
        {
          for ( k = 0; k < v127; ++k )
          {
            rf_vector_subtract(v79, v76, &v133[3 * k]);
            v18 = rf_vector_dot(v76, v116);
            v139[24 * v119 + 2 + 2 * v120 + 2 * k] = v18 / v145[k] + 0.5;
            v19 = rf_vector_dot(v76, v117);
            v139[24 * v119 + 3 + 2 * v120 + 2 * k] = v19 / v145[k] + 0.5;
          }
        }
        if ( *(_DWORD *)(v80 + 20) == *((_DWORD *)vector + 16) )
          v27 = 0;
        else
          v27 = *(_DWORD *)(v80 + 20);
        v80 = v27;
        v81 += 10;
        ++v119;
      }
    }
    ++*(_DWORD *)&byte_98967F[756189];
    if ( rf_d3d8_multitexture_available || a6 )
    {
      if ( v109 != v138 || v110 != v137 )
        v143 = -1;
      for ( k = 0; k < v119; ++k )
      {
        *(float *)&Src[40 * k + 32] = v139[24 * k];
        *(float *)&Src[40 * k + 36] = v139[24 * k + 1];
      }
      rf_renderer_append_world_face_packet_wrapper(&v143, Src, v119, v109, v110, v121, 3);
    }
    else
    {
      if ( v109 != v138 )
        v128 = -1;
      rf_renderer_append_world_face_packet_wrapper(&v128, Src, v119, v109, -1, unk_187CD20, 3);
      for ( k = 0; k < v119; ++k )
      {
        *(float *)&Src[40 * k + 24] = v139[24 * k];
        *(float *)&Src[40 * k + 28] = v139[24 * k + 1];
      }
      if ( v110 != v137 )
        v125 = -1;
      rf_renderer_append_world_face_packet_wrapper(&v125, Src, v119, v110, -1, unk_182ABA4, 4);
    }
    if ( v120 )
    {
      for ( k = 0; k < v119; ++k )
      {
        *(float *)&Src[40 * k + 32] = v139[24 * k];
        *(float *)&Src[40 * k + 36] = v139[24 * k + 1];
      }
      if ( v144 != v110 )
        v118 = -1;
      for ( k = 0; k < v120; ++k )
      {
        v75 = v123[k];
        for ( n = 0; n < v119; ++n )
        {
          *(float *)&Src[40 * n + 24] = v139[24 * n + 2 + 2 * k];
          *(float *)&Src[40 * n + 28] = v139[24 * n + 3 + 2 * k];
          *(_DWORD *)&Src[40 * n + 16] = (unsigned int)&unk_FFFFFF
                                       | (*(unsigned __int8 *)(*(_DWORD *)(v75 + 1316) + 76) << 24);
        }
        if ( (*(_DWORD *)(*(_DWORD *)(v75 + 1316) + 80) & 0x20) != 0 )
        {
          v126 = unk_18CCFE8;
        }
        else if ( (*(_DWORD *)(*(_DWORD *)(v75 + 1316) + 80) & 0x40) != 0 )
        {
          v126 = unk_18CCFD4;
        }
        else if ( (*(_DWORD *)(*(_DWORD *)(v75 + 1316) + 80) & 0x80) != 0 )
        {
          v126 = unk_18CCFCC;
        }
        else
        {
          v126 = unk_18CCFEC;
        }
        if ( v114 != *(_DWORD *)(*(_DWORD *)(v75 + 1316) + 60) || !rf_packed_state_word_equal(&v126, &v129) )
          v118 = -1;
        rf_renderer_append_world_face_packet(&v118, Src, v119, *(_DWORD *)(*(_DWORD *)(v75 + 1316) + 60), v110, v126, 2);
        v114 = *(_DWORD *)(*(_DWORD *)(v75 + 1316) + 60);
        v129 = v126;
        v137 = v110;
      }
      v144 = v110;
    }
    v138 = v109;
    v137 = v110;
    if ( v127 )
    {
      v73 = v112;
      k = 0;
      while ( k < v127 )
      {
        v72 = v120 + k;
        for ( ii = 0; ii < v119; ++ii )
        {
          *(float *)&Src[40 * ii + 24] = v139[24 * ii + 2 + 2 * v72];
          *(float *)&Src[40 * ii + 28] = v139[24 * ii + 3 + 2 * v72];
          *(_DWORD *)&Src[40 * ii + 16] = *v73;
        }
        rf_renderer_append_world_face_packet_wrapper(
          &v148,
          Src,
          v119,
          dword_664A04,
          -1,
          SLODWORD(rf_particle_glow_billboard_render_state),
          0);
        ++k;
        ++v73;
      }
      *((_DWORD *)vector + 10) &= ~0x40000u;
    }
    if ( byte_663F04 && v124 )
    {
      if ( (dword_1F670F4 & 1) == 0 )
      {
        dword_1F670F4 |= 1u;
        v150 = 0;
        rf_render_state_pack(&unk_1F670F0, 6, 1, 3, 3, 1, 0);
        v150 = -1;
      }
      v69 = -1;
      v67 = -1;
      v70 = -1;
      for ( k = 0; k < v124; ++k )
      {
        v66 = (int *)v147[k];
        v65 = v66[329];
        if ( *(_DWORD *)(v65 + 60) != v69 || v66[51] != v67 )
        {
          v69 = *(_DWORD *)(v65 + 60);
          v67 = v66[51];
          v70 = -1;
        }
        if ( v111 )
        {
          v58 = -1;
          v60 = 0;
          for ( jj = 0; jj < v66[52]; ++jj )
          {
            v55 = (int)&v66[11 * jj + 53];
            rf_vector_prefix_construct_noop(source);
            v20 = rf_renderer_transform_world_point_to_clip_vertex((int)source, (float *)(v55 + 16));
            *(_DWORD *)(v55 + 40) = v20;
            rf_vector_copy((float *)(v55 + 28), v35, source);
            v58 &= *(_DWORD *)(v55 + 40);
            v60 |= *(_DWORD *)(v55 + 40);
          }
          if ( !v58 )
          {
            rf_clip_vertex48_pool_reset();
            v57 = unk_18CD040;
            v64 = 0;
            v63 = 0;
            rf_vector_construct_no_unwind(v61, 0x30u, 48, rf_vector_prefix_construct_noop);
            v59 = v66[52];
            for ( jj = 0; jj < v66[52]; ++jj )
            {
              v54 = (float *)&v61[48 * jj];
              v53 = (int)&v66[11 * jj + 53];
              v57[jj] = v54;
              rf_vector_copy(v54, v34, (const float *)(v53 + 28));
              *((_BYTE *)v54 + 24) = *(_BYTE *)(v53 + 40);
              *((_BYTE *)v54 + 25) = 0;
              v63 |= *((_BYTE *)v54 + 24);
              v54[7] = *(float *)v53;
              v54[8] = *(float *)(v53 + 4);
              v54[9] = *(float *)(v53 + 8);
              v54[10] = *(float *)(v53 + 12);
            }
            v57 = rf_clip_polygon_outcode_planes_48(unk_18CD040, unk_18CD108, &v59, &v63, 3);
            if ( v59 >= 3 && !v64 )
            {
              v62 = (float *)Src;
              jj = 0;
              while ( jj < v59 )
              {
                v52 = (float *)v57[jj];
                v51 = 1.0 / v52[2];
                *v62 = *v52 * v51 * unk_18CD35C + unk_18CD358;
                v62[1] = v52[1] * v51 * unk_18CD364 + unk_18CD360;
                *((_DWORD *)v62 + 4) = (unsigned int)&unk_FFFFFF | (*(unsigned __int8 *)(v65 + 76) << 24);
                v21 = rf_renderer_linear_depth_fade_byte(v52[2]);
                *((_DWORD *)v62 + 5) = v21 << 24;
                v62[6] = flt_664AF8 * v52[7];
                v62[7] = flt_664AF8 * v52[8];
                v62[8] = flt_664AF8 * v52[9];
                v62[9] = flt_664AF8 * v52[10];
                if ( v136 < (double)v52[2] )
                  v51 = 1.0 / (v52[2] - v122);
                v22 = rf_renderer_scale_reciprocal_depth(v51);
                v62[2] = v22;
                v62[3] = v51 * flt_6649F8;
                ++jj;
                v62 += 10;
              }
              rf_renderer_append_world_face_packet(&v70, Src, v59, *(_DWORD *)(v65 + 60), v66[51], unk_1F670F0, 1);
              for ( jj = 0; jj < v59; ++jj )
              {
                if ( (*(_BYTE *)(v57[jj] + 25) & 4) != 0 )
                  rf_clip_vertex48_pool_release(v57[jj]);
              }
            }
          }
        }
        else
        {
          for ( jj = 0; jj < v66[52]; ++jj )
          {
            v49 = (float *)&v66[11 * jj + 53];
            rf_vector_subtract((const float *)&v66[11 * jj + 57], &v46, &flt_18CD5E8);
            v49[7] = v46 * *v115 + v47 * v115[1] + v48 * v115[2];
            v49[8] = v46 * v115[3] + v47 * v115[4] + v48 * v115[5];
            v49[9] = v46 * v115[6] + v47 * v115[7] + v48 * v115[8];
          }
          v50 = (float *)Src;
          jj = 0;
          while ( jj < v66[52] )
          {
            v44 = (float *)&v66[11 * jj + 53];
            v45 = 1.0 / *(float *)&v66[11 * jj + 62];
            *v50 = *(float *)&v66[11 * jj + 60] * v45 * unk_18CD35C + unk_18CD358;
            v50[1] = v44[8] * v45 * unk_18CD364 + unk_18CD360;
            *((_DWORD *)v50 + 4) = (unsigned int)&unk_FFFFFF | (*(unsigned __int8 *)(v65 + 76) << 24);
            v23 = rf_renderer_linear_depth_fade_byte(v44[9]);
            *((_DWORD *)v50 + 5) = v23 << 24;
            v50[6] = flt_664AF8 * *v44;
            v50[7] = flt_664AF8 * v44[1];
            v50[8] = flt_664AF8 * v44[2];
            v50[9] = flt_664AF8 * v44[3];
            if ( v136 < (double)v44[9] )
              v45 = 1.0 / (v44[9] - v122);
            v24 = rf_renderer_scale_reciprocal_depth(v45);
            v50[2] = v24;
            v50[3] = v45 * flt_6649F8;
            ++jj;
            v50 += 10;
          }
          rf_renderer_append_world_face_packet(&v70, Src, v66[52], *(_DWORD *)(v65 + 60), v66[51], unk_1F670F0, 1);
        }
      }
    }
  }
  result = rf_renderer_flush_world_face_packets();
  unk_1E014E6 = 0;
  return result;
}

