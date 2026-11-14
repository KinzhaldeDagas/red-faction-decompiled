// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C4D10 rf_renderer_set_camera_projection_backend102
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric states, stack ABI and callers): Five cdecl inputs: orientation3x3 pointer, camera-position pointer, lens float, depth-clear control byte and perspective byte. Stores perspective mode, resets instance-stack depth, captures viewport dimensions/half extents/center, resets clip-vertex pool, forwards depth-clear control byte to 571CC0, and increments view generation. Perspective lens>=2 uses tan(lens*pi/180/2), but lens<2 is used directly as a tangent; orthographic uses lens/2. Separately depth scalar 6649F4 always uses degree/tan interpretation in perspective, or fixed 0.00058800011 otherwise. Copies position to 18CD5E8 and orientation to 18CD4B4/18CD7E0, caches original position at18CD4A8, resets instance orientation/origin. Sets normalized depth 0.98000002 and clamps far-distance global18CD36C to [31.25,1000]
// in663F34. zScale=0.98/clampedDistance in perspective else0.98; xScale=zScale/lensTerm, yScale=zScale/(aspect*lensTerm), aspect=viewportHeight*187CCA8/viewportWidth. Derives default depth bias=zScale*0.025, replaces enabled bias, caches reciprocal zScale. Saves unscaled basis to18CD398, scales active matrix rows by x/y/z scales, rebuilds world clip planes. No zero-dimension, lens or pointer guards.
// [UnrealRed retained room-view state 2026-11-12; full original-byte view/far caller closure] View setup copies UNSCALED basis rows18CD398/3A4/3B0 (5C4FE3..4FED), derives individually scaled matrix rows4B4/4C0/4CC, and resets native temporary clip pool. RawWorldFar36C is distinct from clamped31.25..1000 float663F34 used ONLY forDepthScale=float(0.9800000190734863/clampedFar). Worldclipplanes/scaledFar370 use UNCLAMPED36C. Later5813D0 changes raw far+planes but does not regenerate scaled matrix, so complete room projection inputs are an ORDERED RETAINED renderer snapshot, not one stateless camera/far pair.
void __cdecl rf_renderer_set_camera_projection_backend102(
        const float *a1,
        const float *a2,
        float a3,
        unsigned __int8 a4,
        unsigned __int8 a5)
{
  float v5; // [esp+4h] [ebp-38h]
  float v6; // [esp+8h] [ebp-34h]
  float v7; // [esp+Ch] [ebp-30h]
  float v8; // [esp+10h] [ebp-2Ch]
  float v9; // [esp+14h] [ebp-28h]
  float v10[3]; // [esp+18h] [ebp-24h] BYREF
  float copy_result[3]; // [esp+24h] [ebp-18h] BYREF
  float v12; // [esp+30h] [ebp-Ch]
  float v13; // [esp+34h] [ebp-8h]
  float v14; // [esp+38h] [ebp-4h]

  byte_663F39 = a5;
  if ( a5 )
  {
    v9 = a3 * 3.141592741012573 / 180.0 * 0.5;
    flt_6649F4 = 0.0005880001117475331 / rf_tan_float(v9);
  }
  else
  {
    flt_6649F4 = 0.00058800011;
  }
  unk_18CD388 = 0;
  unk_18CD104 = dword_187CCC4;
  unk_18CD1CC = dword_187CCC8;
  unk_18CD1C8 = (double)dword_187CCC4 * 0.5;
  unk_18CD290 = (double)dword_187CCC8 * 0.5;
  v13 = (double)dword_187CCC8 * unk_187CCA8 / (double)dword_187CCC4;
  rf_clip_vertex48_pool_reset();
  unk_18CD358 = (double)unk_187CCBC + unk_18CD1C8;
  unk_18CD360 = (double)unk_187CCC0 + unk_18CD290;
  unk_18CD35C = unk_18CD1C8;
  unk_18CD364 = -unk_18CD290;
  rf_renderer_set_depth_clear_enabled(a4);
  ++unk_18CD38C;
  v12 = 0.0;
  if ( byte_663F39 )
  {
    if ( a3 >= 2.0 )
    {
      v8 = a3 * 3.141592741012573 / 180.0 * 0.5;
      v12 = rf_tan_float(v8);
    }
    else
    {
      v12 = a3;
    }
  }
  else
  {
    v12 = a3 * 0.5;
  }
  rf_vector_copy(&flt_18CD5E8, copy_result, a2);
  rf_matrix3_copy(&flt_18CD4B4, a1);
  rf_matrix3_copy(&flt_18CD7E0, &flt_18CD4B4);
  rf_vector_copy(unk_18CD4A8, v10, &flt_18CD5E8);
  rf_identity_orientation_matrix(&flt_18CD5B8);
  rf_vector3_zero_return_destination(unk_18CD804);
  unk_18CD380 = 0.98000002;
  if ( flt_18CD36C >= 31.25 )
    v7 = flt_18CD36C;
  else
    v7 = 31.25;
  if ( v7 >= 1000.0 )
  {
    v5 = 1000.0;
  }
  else
  {
    if ( flt_18CD36C >= 31.25 )
      v6 = flt_18CD36C;
    else
      v6 = 31.25;
    v5 = v6;
  }
  flt_663F34 = v5;
  if ( byte_663F39 )
    v14 = unk_18CD380 / flt_663F34;
  else
    v14 = unk_18CD380;
  unk_18CD3BC = v14 / v12;
  unk_18CD3C0 = v14 / (v13 * v12);
  unk_18CD3C4 = v14;
  unk_1DAEDFC = v14 * 0.02500000037252903;
  if ( unk_1DAEE00 != 0.0 )
    unk_1DAEE00 = unk_1DAEDFC;
  unk_18CD294 = 1.0 / unk_18CD3C4;
  rf_matrix3_copy(unk_18CD398, &flt_18CD4B4);
  rf_vector3_scale_in_place_return_self(&flt_18CD4B4, unk_18CD3BC);
  rf_vector3_scale_in_place_return_self(&flt_18CD4C0, unk_18CD3C0);
  rf_vector3_scale_in_place_return_self(&flt_18CD4CC, unk_18CD3C4);
  rf_renderer_rebuild_world_clip_planes();
}

