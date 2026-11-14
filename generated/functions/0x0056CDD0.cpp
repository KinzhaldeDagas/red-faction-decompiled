// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056CDD0 rf_projected_shadow_compute_cone_extent
// UNREALRED VERIFIED [projected-shadow-cone-20260903]: Given two axis points distance D apart and radius R with 0<R<D, computes the tangent-circle terms sqrt((D/R)^2-1)/(D/R), R/(D/R), and full angular diameter 2*acos(sqrt((D/R)^2-1)/(D/R)). The shadow builder calls it with D=3R.
char __cdecl rf_projected_shadow_compute_cone_extent(float *a1, float *a2, float a3, float *a4, float *a5, float *a6)
{
  float v7; // [esp+8h] [ebp-48h]
  float v8; // [esp+Ch] [ebp-44h]
  float out_vector[3]; // [esp+10h] [ebp-40h] BYREF
  float v10; // [esp+1Ch] [ebp-34h]
  float rhs[3]; // [esp+20h] [ebp-30h] BYREF
  float lhs[3]; // [esp+2Ch] [ebp-24h] BYREF
  float v13[3]; // [esp+38h] [ebp-18h] BYREF
  float v14[3]; // [esp+44h] [ebp-Ch] BYREF

  v10 = rf_vector_distance(a1, a2);
  if ( v10 <= 0.0 || a3 <= 0.0 || a3 >= (double)v10 )
    return 0;
  v10 = v10 / a3;
  v8 = v10 * v10 - 1.0;
  *a4 = rf_sqrt_float(v8) / v10;
  *a6 = 1.0 / v10;
  rf_vector3_set_components_return_destination(rhs, 0.0, v10, 0.0);
  rf_vector3_set_components_return_destination(lhs, 0.0, *a6, 0.0);
  rf_vector3_set_components_return_destination(v14, *a4, *a6, 0.0);
  rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_subtract(v14, v13, rhs);
  rf_vector_normalize_reciprocal_sqrt(out_vector);
  rf_vector_normalize_reciprocal_sqrt(v13);
  v7 = rf_vector_dot(out_vector, v13);
  *a5 = rf_acos_float(v7) * 2.0;
  *a4 = *a4 * a3;
  *a6 = *a6 * a3;
  return 1;
}

