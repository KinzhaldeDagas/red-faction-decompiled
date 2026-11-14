// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055A5B0 rf_point2_closest_on_segment_distance_squared
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): cdecl(point,A,B,outClosest). d=B-A,v=point-A,t=dot(v,d)/|d|^2, clamps t with max(t,0) thenmin(t,1), writes A+t*d, returns squared distance(outClosest-point). Zero-length segment divides0 before clamps; no explicit degenerate guard. Final distance reads original point AFTER writing output, so alias outClosest==point yields0. Primary arithmetic is2D only.
double __cdecl rf_point2_closest_on_segment_distance_squared(
        const float *a1,
        const float *a2,
        const float *a3,
        float *a4)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  double v8; // [esp+8h] [ebp-3Ch]
  float v9[2]; // [esp+10h] [ebp-34h] BYREF
  float v10[2]; // [esp+18h] [ebp-2Ch] BYREF
  float v11[2]; // [esp+20h] [ebp-24h] BYREF
  float v12[2]; // [esp+28h] [ebp-1Ch] BYREF
  float v13[2]; // [esp+30h] [ebp-14h] BYREF
  float v14; // [esp+38h] [ebp-Ch]
  float v15; // [esp+3Ch] [ebp-8h]
  float v16; // [esp+40h] [ebp-4h]

  rf_vector2_subtract_to_output((float *)a3, v13, (float *)a2);
  rf_vector2_subtract_to_output((float *)a1, v12, (float *)a2);
  v16 = v12[0] * v13[0];
  v14 = v12[1] * v13[1];
  v8 = v16 + v14;
  v15 = v8 / rf_vector2_length_squared_x87(v13);
  v15 = rf_float_maximum_two_values(v15, 0.0);
  v15 = rf_float_minimum_two_values(v15, 1.0);
  v4 = rf_vector2_scale_to_output(v11, v15, v13);
  v5 = rf_vector2_add_to_output((float *)a2, v10, v4);
  rf_vector2_copy_return_source(a4, v5);
  v6 = rf_vector2_subtract_to_output(a4, v9, (float *)a1);
  return rf_vector2_length_squared_x87(v6);
}

