// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580C00 rf_volume_box_sample_contribution
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Returns FLOAT in ST0 (old void prototype incorrect). Copy cached cameraLocal124;transform worldPoint-center by inverse orientation24 to local endpoint. Clip segment in-place to bounds92/104 using580D60 in axis orders(0,1,2),(1,2,0),(2,0,1);any reject returns0. Otherwise length=distance(clipped endpoints);f(y)=cached116*y+cached120;result=length*(fA+0.5*(fB-fA))*cached72,with fA=f(endpointA.y),fB=f(endpointB.y),clamp[0,255],return. Linear vertical-density integration through box,not just length. Endpoint order may swap per axis but average invariant. No dimension/orthonormal/finite guards;division occurred in preparation.
float __cdecl rf_volume_box_sample_contribution(const void *a1, const float *a2)
{
  float v4; // [esp+8h] [ebp-30h] BYREF
  float v5; // [esp+Ch] [ebp-2Ch]
  int v6; // [esp+14h] [ebp-24h] BYREF
  float v7; // [esp+18h] [ebp-20h]
  float v8; // [esp+1Ch] [ebp-1Ch]
  float v9; // [esp+20h] [ebp-18h] BYREF
  float v10; // [esp+24h] [ebp-14h]
  float v11; // [esp+2Ch] [ebp-Ch]
  float v12; // [esp+30h] [ebp-8h]
  float v13; // [esp+34h] [ebp-4h]

  rf_vector3_copy_return_destination(&v4, (float *)a1 + 31);
  rf_vector3_copy_return_destination(&v9, (float *)a2);
  rf_vector_subtract_in_place(&v9, (float *)a1 + 2);
  rf_matrix3_inverse_rotate_vector(&v9, (float *)a1 + 6);
  if ( rf_segment_clip_aabb_axis_in_place(&v4, &v9, (int)a1 + 92, (int)a1 + 104, 0, 1, 2) )
  {
    return 0.0;
  }
  else if ( rf_segment_clip_aabb_axis_in_place(&v4, &v9, (int)a1 + 92, (int)a1 + 104, 1, 2, 0) )
  {
    return 0.0;
  }
  else if ( rf_segment_clip_aabb_axis_in_place(&v4, &v9, (int)a1 + 92, (int)a1 + 104, 2, 0, 1) )
  {
    return 0.0;
  }
  else
  {
    v7 = rf_vector_distance(&v4, &v9);
    v11 = v5;
    v12 = v10;
    v8 = *((float *)a1 + 29) * v5 + *((float *)a1 + 30);
    v13 = *((float *)a1 + 29) * v10 + *((float *)a1 + 30);
    *(float *)&v6 = ((v13 - v8) * 0.5 + v8) * v7;
    *(float *)&v6 = *(float *)&v6 * *((float *)a1 + 18);
    rf_float_clamp_in_place((float *)&v6, 0.0, 255.0);
    return *(float *)&v6;
  }
}

