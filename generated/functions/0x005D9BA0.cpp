// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D9BA0 rf_renderer_draw_rotated_billboard_camera_rectangle
// UNREALRED VERIFIED [renderer-overlays-20261028]: Arguments48-byte camera clipvertexcenter,angle,fullwidth,fullheight,packedstate. Projects center if projectedbit1clear,rejects only if complete flagsbyte0. Uses halfwidth/halfheight directly,without bitmapaspect adjustment. Builds four rotated cameraXY corners scaled by0x18CD3BC/3C0 at centerZ,fullUV,reversed pointerorder. Computes depthoverride using0x581AF0(halfwidth),subtracts only if z>bias. Refreshes corneroutcodes,clears flags,rejects nonzero sharedAND; submits4vertices mask1,overrideenabled1. Unlike aspectbillboard,does not set auxiliarymode16. No size,finite or projectionrejectedbit guard; returns polygon submission result.
char __cdecl rf_renderer_draw_rotated_billboard_camera_rectangle(int a1, float a2, float a3, float a4, int a5)
{
  float v6; // [esp+4h] [ebp-E8h]
  char v7; // [esp+Bh] [ebp-E1h]
  int v8[4]; // [esp+Ch] [ebp-E0h] BYREF
  float v9; // [esp+1Ch] [ebp-D0h]
  float v10; // [esp+20h] [ebp-CCh]
  float v11; // [esp+24h] [ebp-C8h]
  int i; // [esp+28h] [ebp-C4h]
  float v13[12]; // [esp+2Ch] [ebp-C0h] BYREF
  float v14[12]; // [esp+5Ch] [ebp-90h] BYREF
  float v15[12]; // [esp+8Ch] [ebp-60h] BYREF
  float v16[12]; // [esp+BCh] [ebp-30h] BYREF
  float v17; // [esp+FCh] [ebp+10h]
  float v18; // [esp+100h] [ebp+14h]

  rf_vector_construct_no_unwind((char *)v13, 0x30u, 4, rf_vector_prefix_construct_noop);
  v8[0] = (int)v16;
  v8[1] = (int)v15;
  v8[2] = (int)v14;
  v8[3] = (int)v13;
  if ( (*(_BYTE *)(a1 + 25) & 1) == 0 )
    rf_renderer_project_clip_vertex_backend_wrapper(a1);
  if ( !*(_BYTE *)(a1 + 25) )
    return 0;
  v9 = rf_sin_float(a2);
  v6 = rf_cos_float(a2);
  v17 = a3 / 2.0;
  v18 = a4 / 2.0;
  v13[0] = (-v17 * v6 + v18 * v9) * unk_18CD3BC + *(float *)a1;
  v13[1] = (-v17 * v9 - v18 * v6) * unk_18CD3C0 + *(float *)(a1 + 4);
  v13[2] = *(float *)(a1 + 8);
  v13[7] = 0.0;
  v13[8] = 1.0;
  v14[0] = (v17 * v6 + v18 * v9) * unk_18CD3BC + *(float *)a1;
  v14[1] = (v17 * v9 - v18 * v6) * unk_18CD3C0 + *(float *)(a1 + 4);
  v14[2] = *(float *)(a1 + 8);
  v14[7] = 1.0;
  v14[8] = 1.0;
  v15[0] = (v17 * v6 - v18 * v9) * unk_18CD3BC + *(float *)a1;
  v15[1] = (v17 * v9 + v18 * v6) * unk_18CD3C0 + *(float *)(a1 + 4);
  v15[2] = *(float *)(a1 + 8);
  v15[7] = 1.0;
  v15[8] = 0.0;
  v16[0] = (-v17 * v6 - v18 * v9) * unk_18CD3BC + *(float *)a1;
  v16[1] = (-v17 * v9 + v18 * v6) * unk_18CD3C0 + *(float *)(a1 + 4);
  v16[2] = *(float *)(a1 + 8);
  v16[7] = 0.0;
  v16[8] = 0.0;
  v7 = -1;
  v10 = rf_renderer_scale_camera_depth_bias(v17);
  v11 = *(float *)(a1 + 8);
  if ( v11 > (double)v10 )
    v11 = v11 - v10;
  for ( i = 0; i < 4; ++i )
  {
    v7 &= rf_clip_vertex48_update_outcode_backend((int)&v13[12 * i]);
    BYTE1(v13[12 * i + 6]) = 0;
  }
  if ( v7 )
    return 0;
  else
    return rf_renderer_submit_immediate_polygon(4, (int)v8, 1, a5, 1, v11);
}

