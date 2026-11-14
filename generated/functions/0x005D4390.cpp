// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D4390 rf_renderer_draw_single_face_backend_102
// UNREALRED VERIFIED [face-batch-20261028]: Inputs context,face,packed state,bitmap,combined outcode. Nonzero outcode builds25 local48-byte clip vertices from cached camera coordinates at sourcevertex+12,clipcode+28 and face-corner UV+4/+8,then clips active bits via rf_clip_polygon_outcode_planes_48(attribute mask1). Rejects fewer than3 results or adjacent rejected byte; otherwise applies packed state,binds texture0 and ensures GPU limits6000 vertices/10000 indices through0x5DF4A0. Projects x/y by reciprocal z,stores depth from0x5DF870,RGBA from current global color,specular-alpha from0x5A4140,texture-scaledUV; appends fanindices0x5DF7B0. Releases temporary clipped vertices flagged+25 bit4. Zero outcode follows same upload using original circular face vertices without clipping. Returns1 after submission,0 when clipped away. No face vertex<=25,zero-z or empty-loop count guard; current
// decompiler void depth wrapper is misleading.
char __cdecl rf_renderer_draw_single_face_backend_102(int a1, int a2, int a3, int a4, int a5)
{
  double v5; // st7
  double v7; // st7
  int v8; // eax
  int v9; // [esp+8h] [ebp-504h]
  int v10; // [esp+Ch] [ebp-500h]
  int v11; // [esp+10h] [ebp-4FCh]
  float copy_result[3]; // [esp+14h] [ebp-4F8h] BYREF
  float v13; // [esp+20h] [ebp-4ECh]
  float *v14; // [esp+24h] [ebp-4E8h]
  int v15; // [esp+28h] [ebp-4E4h]
  float *destination; // [esp+2Ch] [ebp-4E0h]
  float v17; // [esp+30h] [ebp-4DCh]
  float *v18; // [esp+34h] [ebp-4D8h]
  int j; // [esp+38h] [ebp-4D4h]
  int v20; // [esp+3Ch] [ebp-4D0h]
  int v21; // [esp+40h] [ebp-4CCh]
  _DWORD *v22; // [esp+44h] [ebp-4C8h]
  int v23; // [esp+48h] [ebp-4C4h]
  char v24[1200]; // [esp+4Ch] [ebp-4C0h] BYREF
  int v25; // [esp+4FCh] [ebp-10h] BYREF
  char v26; // [esp+503h] [ebp-9h]
  int i; // [esp+504h] [ebp-8h]
  char v28; // [esp+508h] [ebp-4h] BYREF
  char v29; // [esp+509h] [ebp-3h]

  if ( a5 )
  {
    v22 = unk_18CD040;
    rf_clip_vertex48_pool_reset();
    v29 = 0;
    v28 = 0;
    rf_vector_construct_no_unwind(v24, 0x30u, 25, rf_vector_prefix_construct_noop);
    v23 = *(_DWORD *)(a2 + 64);
    v25 = 0;
    while ( v23 )
    {
      destination = (float *)&v24[48 * v25];
      v22[v25++] = destination;
      rf_vector_copy(destination, copy_result, (const float *)(*(_DWORD *)v23 + 12));
      *((_BYTE *)destination + 24) = *(_BYTE *)(*(_DWORD *)v23 + 28);
      *((_BYTE *)destination + 25) = 0;
      v28 |= *((_BYTE *)destination + 24);
      destination[7] = *(float *)(v23 + 4);
      destination[8] = *(float *)(v23 + 8);
      if ( *(_DWORD *)(v23 + 20) == *(_DWORD *)(a2 + 64) )
        v9 = 0;
      else
        v9 = *(_DWORD *)(v23 + 20);
      v23 = v9;
    }
    v22 = rf_clip_polygon_outcode_planes_48(unk_18CD040, unk_18CD108, &v25, &v28, 1);
    v26 = 0;
    if ( v25 >= 3 && !v29 )
    {
      rf_renderer_apply_packed_render_state(a3);
      rf_renderer_bind_texture_handle(0, a4, 0, (int)&flt_1E014DC, (int)&flt_1E014D0, 1);
      if ( v25 + dword_18CCFBC > 6000 || 3 * (v25 - 2) + unk_1E014EC + unk_18CCFC0 > 10000 )
        rf_renderer_begin_immediate_buffers(4, 3);
      v15 = unk_1DAEDB8 + 40 * unk_1E014E8;
      for ( i = 0; i < v25; ++i )
      {
        v14 = (float *)v22[i];
        v13 = 1.0 / v14[2];
        *(float *)(v15 + 12) = v13;
        v7 = v14[2];
        rf_renderer_depth_from_reciprocal_wrapper(COERCE_INT(v14[2]), v13);
        *(float *)(v15 + 8) = v7;
        *(float *)v15 = *v14 * v13 * unk_18CD35C + unk_18CD358;
        *(float *)(v15 + 4) = v14[1] * v13 * unk_18CD364 + unk_18CD360;
        *(_DWORD *)(v15 + 16) = rf_render_current_blue
                              | (rf_render_current_green << 8)
                              | (rf_render_current_red << 16)
                              | (rf_render_current_alpha << 24);
        v8 = rf_renderer_linear_depth_fade_byte(v14[2]);
        *(_DWORD *)(v15 + 20) = v8 << 24;
        *(float *)(v15 + 24) = v14[7] * flt_1E014DC;
        *(float *)(v15 + 28) = v14[8] * flt_1E014D0;
        v15 += 40;
      }
      rf_renderer_append_immediate_triangle_fan_indices(v25);
      v26 = 1;
      for ( i = 0; i < v25; ++i )
      {
        if ( (*(_BYTE *)(v22[i] + 25) & 4) != 0 )
          rf_clip_vertex48_pool_release(v22[i]);
      }
    }
    return v26;
  }
  else
  {
    rf_renderer_apply_packed_render_state(a3);
    rf_renderer_bind_texture_handle(0, a4, 0, (int)&flt_1E014DC, (int)&flt_1E014D0, 1);
    v20 = 0;
    for ( j = *(_DWORD *)(a2 + 64); j; j = v11 )
    {
      ++v20;
      if ( *(_DWORD *)(j + 20) == *(_DWORD *)(a2 + 64) )
        v11 = 0;
      else
        v11 = *(_DWORD *)(j + 20);
    }
    if ( v20 + dword_18CCFBC > 6000 || 3 * (v20 - 2) + unk_1E014EC + unk_18CCFC0 > 10000 )
      rf_renderer_begin_immediate_buffers(4, 3);
    v21 = unk_1DAEDB8 + 40 * unk_1E014E8;
    for ( j = *(_DWORD *)(a2 + 64); j; j = v10 )
    {
      v18 = *(float **)j;
      v17 = 1.0 / v18[5];
      *(float *)(v21 + 12) = v17;
      v5 = v18[5];
      rf_renderer_depth_from_reciprocal_wrapper(COERCE_INT(v18[5]), v17);
      *(float *)(v21 + 8) = v5;
      *(float *)v21 = v18[3] * v17 * unk_18CD35C + unk_18CD358;
      *(float *)(v21 + 4) = v18[4] * v17 * unk_18CD364 + unk_18CD360;
      *(_DWORD *)(v21 + 16) = rf_render_current_blue
                            | (rf_render_current_green << 8)
                            | (rf_render_current_red << 16)
                            | (rf_render_current_alpha << 24);
      *(_DWORD *)(v21 + 20) = rf_renderer_linear_depth_fade_byte(v18[5]) << 24;
      *(float *)(v21 + 24) = *(float *)(j + 4) * flt_1E014DC;
      *(float *)(v21 + 28) = *(float *)(j + 8) * flt_1E014D0;
      v21 += 40;
      if ( *(_DWORD *)(j + 20) == *(_DWORD *)(a2 + 64) )
        v10 = 0;
      else
        v10 = *(_DWORD *)(j + 20);
    }
    rf_renderer_append_immediate_triangle_fan_indices(v20);
    return 1;
  }
}

