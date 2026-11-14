// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D9790 rf_renderer_draw_rotated_billboard_camera_aspect
// UNREALRED VERIFIED [renderer-overlays-20261028]: Arguments48-byte camera clipvertexcenter,angle,size,packedstate. Projects center if flagbit1clear; rejects only if entire flagsbyte remains0,not explicit rejectedbit2. With pendingbitmap0x187CCE8 signed>=0,queries dimensions; width0 rejects,but height0 unguarded. Size is halfextent; expands shorter texture-axis geometry so width<height expandsY,sizeXunchanged; width>height expandsX,sizeYunchanged. Without bitmap uses squarehalfextents=size. Rotates four cameraXY offsets bysin/cos(angle),scales via0x18CD3BC/3C0,keeps centerZ,assigns full0..1UV and reversed pointerorder. Computes depthoverride=centerZ minus scaledbias0x581AF0(size) only when z>bias. Refreshes allcorneroutcodes via0x581750,clears cornerflags+25,and rejects nonzero sharedAND. Sets auxiliarymode16 and submits4vertices,mask1,state,overrideenabled1,depthoverride. Does not restore
// auxiliarymode or test returned projectionbit after centerprojection; uses current pendingtexture/color.
// UNREALRED VERIFIED [combat-particle-vbm-20261104]: Confirms shared billboard size is HALFextent, not full diameter. Pendingtexturewidth<height keepsHalfWidth=size andexpandsHalfHeight=size*height/width; width>height expandsHalfWidth=size*width/height andkeepsHalfHeight=size. FullUVs0..1, rotationafteraspect. Thus VBM prototype2*effectSize yields2*size RF-unit halfextent beforeaspect. Radius0/negative stay signeduntil particleupdatepositive-radiusgate; no spawn floor. Renderer clip/depthbias semantics remain separate from this size contract.
char __cdecl rf_renderer_draw_rotated_billboard_camera_aspect(int a1, float a2, float a3, int a4)
{
  char updated; // al
  int v6; // [esp+4h] [ebp-F8h] BYREF
  int v7; // [esp+8h] [ebp-F4h] BYREF
  float v8; // [esp+Ch] [ebp-F0h]
  float v9; // [esp+10h] [ebp-ECh]
  float v10; // [esp+14h] [ebp-E8h]
  char v11; // [esp+1Bh] [ebp-E1h]
  int v12[4]; // [esp+1Ch] [ebp-E0h] BYREF
  float v13; // [esp+2Ch] [ebp-D0h]
  float v14; // [esp+30h] [ebp-CCh]
  float v15; // [esp+34h] [ebp-C8h]
  int i; // [esp+38h] [ebp-C4h]
  float v17[12]; // [esp+3Ch] [ebp-C0h] BYREF
  float v18[12]; // [esp+6Ch] [ebp-90h] BYREF
  float v19[12]; // [esp+9Ch] [ebp-60h] BYREF
  float v20[12]; // [esp+CCh] [ebp-30h] BYREF

  rf_vector_construct_no_unwind((char *)v17, 0x30u, 4, rf_vector_prefix_construct_noop);
  v12[0] = (int)v20;
  v12[1] = (int)v19;
  v12[2] = (int)v18;
  v12[3] = (int)v17;
  if ( (*(_BYTE *)(a1 + 25) & 1) == 0 )
    rf_renderer_project_clip_vertex_backend_wrapper(a1);
  if ( !*(_BYTE *)(a1 + 25) )
    return 0;
  v13 = rf_sin_float(a2);
  v8 = rf_cos_float(a2);
  if ( (int)dword_187CCE8 <= -1 )
  {
    v10 = a3;
    v9 = a3;
  }
  else
  {
    rf_bitmap_get_resolved_dimensions(dword_187CCE8, &v6, &v7);
    if ( !v6 )
      return 0;
    if ( v6 >= v7 )
    {
      v10 = a3;
      if ( v6 <= v7 )
        v9 = a3;
      else
        v9 = (double)v6 * a3 / (double)v7;
    }
    else
    {
      v9 = a3;
      v10 = (double)v7 * a3 / (double)v6;
    }
  }
  v17[0] = (-v9 * v8 + v10 * v13) * unk_18CD3BC + *(float *)a1;
  v17[1] = (-v9 * v13 - v10 * v8) * unk_18CD3C0 + *(float *)(a1 + 4);
  v17[2] = *(float *)(a1 + 8);
  v17[7] = 0.0;
  v17[8] = 1.0;
  v18[0] = (v9 * v8 + v10 * v13) * unk_18CD3BC + *(float *)a1;
  v18[1] = (v9 * v13 - v10 * v8) * unk_18CD3C0 + *(float *)(a1 + 4);
  v18[2] = *(float *)(a1 + 8);
  v18[7] = 1.0;
  v18[8] = 1.0;
  v19[0] = (v9 * v8 - v10 * v13) * unk_18CD3BC + *(float *)a1;
  v19[1] = (v9 * v13 + v10 * v8) * unk_18CD3C0 + *(float *)(a1 + 4);
  v19[2] = *(float *)(a1 + 8);
  v19[7] = 1.0;
  v19[8] = 0.0;
  v20[0] = (-v9 * v8 - v10 * v13) * unk_18CD3BC + *(float *)a1;
  v20[1] = (-v9 * v13 + v10 * v8) * unk_18CD3C0 + *(float *)(a1 + 4);
  v20[2] = *(float *)(a1 + 8);
  v20[7] = 0.0;
  v20[8] = 0.0;
  v11 = -1;
  v14 = rf_renderer_scale_camera_depth_bias(a3);
  v15 = *(float *)(a1 + 8);
  if ( v15 > (double)v14 )
    v15 = v15 - v14;
  for ( i = 0; i < 4; ++i )
  {
    updated = rf_clip_vertex48_update_outcode_backend((int)&v17[12 * i]);
    v11 &= updated;
    BYTE1(v17[12 * i + 6]) = 0;
  }
  if ( v11 )
    return 0;
  rf_renderer_set_auxiliary_mode_clamped_0_16(16);
  return rf_renderer_submit_immediate_polygon(4, (int)v12, 1, a4, 1, v15);
}

