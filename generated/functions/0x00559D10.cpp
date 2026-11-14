// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559D10 rf_vector_interpolate_directions_unit_inputs
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): cdecl(output,from,to,fraction). Crosses input directions, normalizes axis with unchecked reciprocal sqrt, storedAngle=-acos(dot(from,to))*fraction, then rotates from about origin through559BD0. Does not normalize inputs, clamp fraction/dot, guard parallel/antiparallel axis, or normalize output. Return is output pointer bits, corrected saved declaration to float pointer. Uses retail negative stored-angle convention.
float *__cdecl rf_vector_interpolate_directions_unit_inputs(float *a1, const float *a2, const float *a3, float a4)
{
  float *v4; // eax
  float *v6; // [esp+8h] [ebp-40h]
  float v7; // [esp+Ch] [ebp-3Ch]
  float v8; // [esp+10h] [ebp-38h]
  float v9[3]; // [esp+14h] [ebp-34h] BYREF
  float copy_result[3]; // [esp+20h] [ebp-28h] BYREF
  float v11[3]; // [esp+2Ch] [ebp-1Ch] BYREF
  float destination[3]; // [esp+38h] [ebp-10h] BYREF
  float v13; // [esp+44h] [ebp-4h]

  rf_vector3_default_construct_noop(destination);
  v4 = rf_vector_cross((float *)a2, v11, (float *)a3);
  rf_vector_copy(destination, copy_result, v4);
  rf_vector_normalize_reciprocal_sqrt(destination);
  v7 = rf_vector_dot((float *)a2, (float *)a3);
  v13 = -rf_acos_float(v7);
  v6 = rf_vector3_set_components_return_destination(v9, 0.0, 0.0, 0.0);
  v8 = a4 * v13;
  return rf_point_rotate_about_axis_pivot(a1, (float *)a2, v8, v6, destination);
}

