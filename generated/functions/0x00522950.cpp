// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00522950 rf_world_decal_build_broadphase_aabb
// UNREALRED VERIFIED [decal-projection-20261028]: Computes radius=max(dimensions x,y,z)*0.5*1.732049942016602 (sqrt3 approximation). Stores position+radius to decal+200 and position-radius to+188. Bounds are conservative for nonnegative extents; no abs/clamp or orientation use. Return is vector-copy helper result, not radius.
float *__cdecl rf_world_decal_build_broadphase_aabb(float *a1)
{
  float *v1; // eax
  float *v2; // eax
  float v4[3]; // [esp+8h] [ebp-34h] BYREF
  int v5[3]; // [esp+14h] [ebp-28h] BYREF
  float copy_result[3]; // [esp+20h] [ebp-1Ch] BYREF
  int v7[3]; // [esp+2Ch] [ebp-10h] BYREF
  float v8; // [esp+38h] [ebp-4h]

  v8 = rf_float_maximum_two_values(a1[12], a1[13]);
  v8 = rf_float_maximum_two_values(v8, a1[14]);
  v8 = v8 * 0.5;
  v8 = v8 * 1.732049942016602;
  v1 = rf_vector3_add_scalar_to_components(a1, (float *)v7, v8);
  rf_vector_copy(a1 + 50, copy_result, v1);
  v2 = rf_vector3_subtract_scalar_from_components(a1, (float *)v5, v8);
  return rf_vector_copy(a1 + 47, v4, v2);
}

