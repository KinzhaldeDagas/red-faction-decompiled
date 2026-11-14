// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559DB0 rf_points_build_ritter_bounding_sphere
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): cdecl(packedXYZ,count,outCenter,outRadius). Tracks actual point at min/max of each axis with strict comparisons, using +/-100000000 sentinels and partially initialized candidate vectors. Picks extreme pair with greatest squared distance (X wins ties, thenY), initializes midpoint sphere, then in input order expands for outside points: newR=(oldR+distance)/2, center=(newR*oldCenter+(distance-newR)*point)/distance. Order-dependent approximate enclosing sphere, not minimum sphere. Count<=0 still uses sentinel candidates; coordinates beyond sentinel range may leave artificial candidates. No count/pointer/finite checks. Stores float radius and returns radius pointer.
float *__cdecl rf_points_build_ritter_bounding_sphere(const float *a1, int a2, float *a3, float *a4)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float v11[3]; // [esp+Ch] [ebp-1B8h] BYREF
  float v12[3]; // [esp+18h] [ebp-1ACh] BYREF
  float v13[3]; // [esp+24h] [ebp-1A0h] BYREF
  float v14[3]; // [esp+30h] [ebp-194h] BYREF
  float v15[3]; // [esp+3Ch] [ebp-188h] BYREF
  float sum_result[3]; // [esp+48h] [ebp-17Ch] BYREF
  float v17[3]; // [esp+54h] [ebp-170h] BYREF
  float v18[3]; // [esp+60h] [ebp-164h] BYREF
  float v19[3]; // [esp+6Ch] [ebp-158h] BYREF
  float v20[3]; // [esp+78h] [ebp-14Ch] BYREF
  float v21[3]; // [esp+84h] [ebp-140h] BYREF
  float v22[3]; // [esp+90h] [ebp-134h] BYREF
  float v23[3]; // [esp+9Ch] [ebp-128h] BYREF
  float v24[3]; // [esp+A8h] [ebp-11Ch] BYREF
  float v25[3]; // [esp+B4h] [ebp-110h] BYREF
  float v26[3]; // [esp+C0h] [ebp-104h] BYREF
  float v27[3]; // [esp+CCh] [ebp-F8h] BYREF
  float out_vector[3]; // [esp+D8h] [ebp-ECh] BYREF
  float v29[3]; // [esp+E4h] [ebp-E0h] BYREF
  float v30[3]; // [esp+F0h] [ebp-D4h] BYREF
  float v31[3]; // [esp+FCh] [ebp-C8h] BYREF
  float v32[3]; // [esp+108h] [ebp-BCh] BYREF
  float v33[3]; // [esp+114h] [ebp-B0h] BYREF
  float copy_result[3]; // [esp+120h] [ebp-A4h] BYREF
  float v35[3]; // [esp+12Ch] [ebp-98h] BYREF
  float v36[3]; // [esp+138h] [ebp-8Ch] BYREF
  float v37; // [esp+144h] [ebp-80h]
  float v38; // [esp+148h] [ebp-7Ch]
  float v39; // [esp+14Ch] [ebp-78h]
  float v40; // [esp+150h] [ebp-74h]
  float v41; // [esp+154h] [ebp-70h]
  float v42; // [esp+158h] [ebp-6Ch] BYREF
  float v43; // [esp+15Ch] [ebp-68h]
  float v44[3]; // [esp+164h] [ebp-60h] BYREF
  float v45; // [esp+170h] [ebp-54h]
  float rhs[3]; // [esp+174h] [ebp-50h] BYREF
  float v47; // [esp+180h] [ebp-44h]
  float lhs[3]; // [esp+184h] [ebp-40h] BYREF
  float v49; // [esp+190h] [ebp-34h]
  float v50[2]; // [esp+194h] [ebp-30h] BYREF
  float v51; // [esp+19Ch] [ebp-28h]
  float destination; // [esp+1A0h] [ebp-24h] BYREF
  float v53; // [esp+1A4h] [ebp-20h]
  float v54[2]; // [esp+1ACh] [ebp-18h] BYREF
  float v55; // [esp+1B4h] [ebp-10h]
  int i; // [esp+1B8h] [ebp-Ch]
  float v57; // [esp+1BCh] [ebp-8h]
  float *source; // [esp+1C0h] [ebp-4h]

  rf_vector3_default_construct_noop(v35);
  rf_vector3_default_construct_noop(lhs);
  rf_vector3_default_construct_noop(&v42);
  rf_vector3_default_construct_noop(v50);
  rf_vector3_default_construct_noop(v36);
  rf_vector3_default_construct_noop(v44);
  rf_vector3_set_components_return_destination(rhs, 0.0, 0.0, 0.0);
  rf_vector3_set_components_return_destination(&destination, 0.0, 0.0, 0.0);
  rf_vector3_set_components_return_destination(v54, 0.0, 0.0, 0.0);
  v55 = 100000000.0;
  v53 = 100000000.0;
  rhs[0] = 100000000.0;
  v51 = -100000000.0;
  v43 = -100000000.0;
  lhs[0] = -100000000.0;
  for ( i = 0; i < a2; ++i )
  {
    source = (float *)&a1[3 * i];
    if ( rhs[0] > (double)*source )
      rf_vector_copy(rhs, copy_result, source);
    if ( lhs[0] < (double)*source )
      rf_vector_copy(lhs, v33, source);
    if ( v53 > (double)source[1] )
      rf_vector_copy(&destination, v32, source);
    if ( v43 < (double)source[1] )
      rf_vector_copy(&v42, v31, source);
    if ( v55 > (double)source[2] )
      rf_vector_copy(v54, v30, source);
    if ( v51 < (double)source[2] )
      rf_vector_copy(v50, v29, source);
  }
  v4 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(v35, v27, v4);
  v45 = rf_vector_length_squared(v35);
  v5 = rf_vector_subtract(&v42, v26, &destination);
  rf_vector_copy(v35, v25, v5);
  v37 = rf_vector_length_squared(v35);
  v6 = rf_vector_subtract(v50, v24, v54);
  rf_vector_copy(v35, v23, v6);
  v57 = rf_vector_length_squared(v35);
  rf_vector_copy(v36, v22, rhs);
  rf_vector_copy(v44, v21, lhs);
  v41 = v45;
  if ( v45 < (double)v37 )
  {
    v41 = v37;
    rf_vector_copy(v36, v20, &destination);
    rf_vector_copy(v44, v19, &v42);
  }
  if ( v41 < (double)v57 )
  {
    v41 = v37;
    rf_vector_copy(v36, v18, v54);
    rf_vector_copy(v44, v17, v50);
  }
  v7 = rf_vector_add(v36, sum_result, v44);
  rf_vector_copy(a3, v15, v7);
  rf_vector3_scale_in_place_return_self(a3, 0.5);
  v8 = rf_vector_subtract(v44, v14, a3);
  rf_vector_copy(v35, v13, v8);
  v47 = rf_vector_length_squared(v35);
  v40 = rf_sqrt_float(v47);
  for ( i = 0; i < a2; ++i )
  {
    source = (float *)&a1[3 * i];
    v9 = rf_vector_subtract(source, v12, a3);
    rf_vector_copy(v35, v11, v9);
    v39 = rf_vector_length_squared(v35);
    if ( v47 < (double)v39 )
    {
      v38 = rf_sqrt_float(v39);
      v40 = (v40 + v38) / 2.0;
      v47 = v40 * v40;
      v49 = v38 - v40;
      *a3 = (v40 * *a3 + v49 * *source) / v38;
      a3[1] = (v40 * a3[1] + v49 * source[1]) / v38;
      a3[2] = (v40 * a3[2] + v49 * source[2]) / v38;
    }
  }
  *a4 = v40;
  return a4;
}

