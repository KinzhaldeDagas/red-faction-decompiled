// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005292C0 rf_renderer_light_distance_and_direction
// UNREALRED VERIFIED [nonworld-byte-rgb-20260903]: Subtracts the sample position from the selected light position, returns the vector length, and optionally writes the normalized sample-to-light direction.
double __cdecl rf_renderer_light_distance_and_direction(float *rhs, float *lhs, float *destination)
{
  float copy_result[3]; // [esp+0h] [ebp-1Ch] BYREF
  float out_vector[3]; // [esp+Ch] [ebp-10h] BYREF
  float v6; // [esp+18h] [ebp-4h]

  rf_vector_subtract(lhs, out_vector, rhs);
  v6 = rf_vector3_normalize_return_length(out_vector);
  if ( destination )
    rf_vector_copy(destination, copy_result, out_vector);
  return v6;
}

