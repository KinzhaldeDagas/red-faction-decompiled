// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00529E90 rf_renderer_compute_point_light_surface_terms
// UNREALRED VERIFIED [nonworld-byte-rgb-20260903]: Computes sample-to-point-light distance and a positive surface term inside the light range, using normalized N dot L when a normal is supplied and the legacy smoothed fallback otherwise.
float *__cdecl rf_renderer_compute_point_light_surface_terms(
        float *rhs,
        float *a2,
        float *lhs,
        float a4,
        _BYTE *a5,
        float *a6,
        float *a7)
{
  float *v7; // eax
  float scaled_result[3]; // [esp+Ch] [ebp-2Ch] BYREF
  float sum_result[3]; // [esp+18h] [ebp-20h] BYREF
  float out_vector[3]; // [esp+24h] [ebp-14h] BYREF
  float length; // [esp+30h] [ebp-8h]
  float v13; // [esp+34h] [ebp-4h]

  rf_vector_subtract(lhs, out_vector, rhs);
  v13 = 0.0;
  length = rf_vector_normalize_get_length(out_vector);
  if ( a4 > (double)length )
  {
    if ( !a5 || *a5 )
    {
      v13 = rf_vector_dot(a2, out_vector);
    }
    else
    {
      v7 = rf_vector_multiply_scalar(out_vector, scaled_result, 2.0);
      rf_vector_add(v7, sum_result, a2);
      rf_vector3_scale_in_place_return_self(sum_result, 0.33333334);
      v13 = rf_vector_dot(sum_result, out_vector);
    }
  }
  *a6 = v13;
  *a7 = length;
  return a6;
}

