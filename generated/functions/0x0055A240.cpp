// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055A240 rf_polygon_fan_area_and_weighted_centroid
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): cdecl(count,packedXYZ,outCentroid). Always evaluates first triangle(vertices0,1,2), then fan triangles(0,i,i+1) for i2..count-2. Sums nonnegative cross-magnitude/2 areas, then accumulates each triangle arithmetic centroid weighted by its area/total. Returns float total area viaST0 as double. No count>=3, zero-total-area, convexity, planarity or self-intersection guard; small count reads first3 anyway, degenerate area divides0, concave fan can overcount. Corrected triangle helper signature proves all three triangle points.
double __cdecl rf_polygon_fan_area_and_weighted_centroid(int a1, const float *a2, float *a3)
{
  float *v3; // eax
  float *v4; // eax
  float v6; // [esp+4h] [ebp-44h]
  float scalar; // [esp+8h] [ebp-40h]
  float v8[3]; // [esp+Ch] [ebp-3Ch] BYREF
  float scaled_result[3]; // [esp+18h] [ebp-30h] BYREF
  float vector[3]; // [esp+24h] [ebp-24h] BYREF
  float v11; // [esp+30h] [ebp-18h]
  float v12[3]; // [esp+34h] [ebp-14h] BYREF
  float v13; // [esp+40h] [ebp-8h]
  int i; // [esp+44h] [ebp-4h]

  rf_vector3_default_construct_noop(v12);
  rf_vector3_default_construct_noop(vector);
  rf_vector3_zero_return_destination(a3);
  rf_triangle_cross_from_three_points(v12, a2, a2 + 3, a2 + 6);
  v13 = rf_vector3_length(v12) * 0.5;
  for ( i = 2; i < a1 - 1; ++i )
  {
    rf_triangle_cross_from_three_points(v12, a2, &a2[3 * i], &a2[3 * i + 3]);
    v11 = rf_vector3_length(v12) * 0.5;
    v13 = v13 + v11;
  }
  rf_triangle_cross_from_three_points(v12, a2, a2 + 3, a2 + 6);
  v11 = rf_vector3_length(v12) * 0.5;
  rf_vector3_zero_return_destination(vector);
  for ( i = 0; i < 3; ++i )
    rf_vector_accumulate(vector, (float *)&a2[3 * i]);
  rf_vector3_divide_in_place_reciprocal(vector, 3.0);
  scalar = v11 / v13;
  v3 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
  rf_vector_accumulate(a3, v3);
  for ( i = 2; i < a1 - 1; ++i )
  {
    rf_triangle_cross_from_three_points(v12, a2, &a2[3 * i], &a2[3 * i + 3]);
    v11 = rf_vector3_length(v12) * 0.5;
    rf_vector3_zero_return_destination(vector);
    rf_vector_accumulate(vector, (float *)a2);
    rf_vector_accumulate(vector, (float *)&a2[3 * i]);
    rf_vector_accumulate(vector, (float *)&a2[3 * i + 3]);
    rf_vector3_divide_in_place_reciprocal(vector, 3.0);
    v6 = v11 / v13;
    v4 = rf_vector_multiply_scalar(vector, v8, v6);
    rf_vector_accumulate(a3, v4);
  }
  return v13;
}

