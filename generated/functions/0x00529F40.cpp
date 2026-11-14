// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00529F40 rf_renderer_compute_spot_light_surface_terms
// UNREALRED VERIFIED [nonworld-byte-rgb-20260903]: Computes the spot sample distance, positive surface term, and sample-direction dot spot-axis value used by cone admission and interpolation.
float *__cdecl rf_renderer_compute_spot_light_surface_terms(
        float *rhs,
        float *a2,
        float *lhs,
        float *a4,
        float a5,
        _BYTE *a6,
        float *a7,
        float *a8,
        float *a9)
{
  float sum_result[3]; // [esp+4h] [ebp-24h] BYREF
  float out_vector[3]; // [esp+10h] [ebp-18h] BYREF
  float length; // [esp+1Ch] [ebp-Ch]
  float v13; // [esp+20h] [ebp-8h]
  float v14; // [esp+24h] [ebp-4h]

  v13 = 0.0;
  v14 = 0.0;
  rf_vector_subtract(lhs, out_vector, rhs);
  length = rf_vector_normalize_get_length(out_vector);
  if ( a5 > (double)length )
  {
    if ( !a6 || *a6 )
    {
      v13 = rf_vector_dot(a2, out_vector);
    }
    else
    {
      rf_vector_add(out_vector, sum_result, a2);
      rf_vector3_scale_in_place_return_self(sum_result, 0.5);
      v13 = rf_vector_dot(sum_result, out_vector);
    }
    v14 = rf_vector_dot(out_vector, a4);
  }
  *a7 = v13;
  *a8 = v14;
  *a9 = length;
  return a7;
}

