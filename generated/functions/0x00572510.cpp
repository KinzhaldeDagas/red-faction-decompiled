// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00572510 rf_bitmap_draw_rotated_screen_quad
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Binds bitmap with secondary=-1; gets dimensions and computes half width/height times scale. Uses sin/cos(angle) directly (radians) to rotate four corners around supplied center. Builds four 48-byte preprojected vertices with screen XY, reciprocal depth1 and UVs (0,0),(1,0),(1,1),(0,1), then submits pointer order reversed from local construction to polygon wrapper(count4,textured1,mode). Does not CPU-clip the quad or reject zero/negative scale. Vertex no-op constructors leave unused fields unchanged.
int __cdecl rf_bitmap_draw_rotated_screen_quad(int a1, float a2, float a3, float a4, float a5, int a6)
{
  int v7; // [esp+4h] [ebp-E8h] BYREF
  float v8; // [esp+8h] [ebp-E4h]
  float v9; // [esp+Ch] [ebp-E0h]
  float v10; // [esp+10h] [ebp-DCh]
  _DWORD v11[4]; // [esp+14h] [ebp-D8h] BYREF
  float v12; // [esp+24h] [ebp-C8h]
  int v13; // [esp+28h] [ebp-C4h] BYREF
  char v14[12]; // [esp+2Ch] [ebp-C0h] BYREF
  float v15; // [esp+38h] [ebp-B4h]
  float v16; // [esp+3Ch] [ebp-B0h]
  float v17; // [esp+40h] [ebp-ACh]
  float v18; // [esp+48h] [ebp-A4h]
  float v19; // [esp+4Ch] [ebp-A0h]
  char v20; // [esp+5Ch] [ebp-90h] BYREF
  float v21; // [esp+68h] [ebp-84h]
  float v22; // [esp+6Ch] [ebp-80h]
  float v23; // [esp+70h] [ebp-7Ch]
  float v24; // [esp+78h] [ebp-74h]
  float v25; // [esp+7Ch] [ebp-70h]
  char v26; // [esp+8Ch] [ebp-60h] BYREF
  float v27; // [esp+98h] [ebp-54h]
  float v28; // [esp+9Ch] [ebp-50h]
  float v29; // [esp+A0h] [ebp-4Ch]
  float v30; // [esp+A8h] [ebp-44h]
  float v31; // [esp+ACh] [ebp-40h]
  char v32; // [esp+BCh] [ebp-30h] BYREF
  float v33; // [esp+C8h] [ebp-24h]
  float v34; // [esp+CCh] [ebp-20h]
  float v35; // [esp+D0h] [ebp-1Ch]
  float v36; // [esp+D8h] [ebp-14h]
  float v37; // [esp+DCh] [ebp-10h]

  rf_renderer_set_pending_texture_handles(a1, -1);
  rf_vector_construct_no_unwind(v14, 0x30u, 4, rf_vector_prefix_construct_noop);
  v11[0] = &v32;
  v11[1] = &v26;
  v11[2] = &v20;
  v11[3] = v14;
  v12 = rf_sin_float(a5);
  v8 = rf_cos_float(a5);
  rf_bitmap_get_resolved_dimensions(a1, &v7, &v13);
  v9 = (double)v7 * a4 * 0.5;
  v10 = (double)v13 * a4 * 0.5;
  v15 = -v9 * v8 + v10 * v12 + a2;
  v16 = -v9 * v12 - v10 * v8 + a3;
  v17 = 1.0;
  v18 = 0.0;
  v19 = 0.0;
  v21 = v9 * v8 + v10 * v12 + a2;
  v22 = v9 * v12 - v10 * v8 + a3;
  v23 = 1.0;
  v24 = 1.0;
  v25 = 0.0;
  v27 = v9 * v8 - v10 * v12 + a2;
  v28 = v9 * v12 + v10 * v8 + a3;
  v29 = 1.0;
  v30 = 1.0;
  v31 = 1.0;
  v33 = -v9 * v8 - v10 * v12 + a2;
  v34 = -v9 * v12 + v10 * v8 + a3;
  v35 = 1.0;
  v36 = 0.0;
  v37 = 1.0;
  return rf_renderer_draw_preprojected_polygon_backend_wrapper(4, (int)v11, 1, a6);
}

