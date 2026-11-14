// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056AF30 rf_point_within_expanded_aabb
// UNREALRED VERIFIED [general-gap-20260830]: Tests inclusive per-axis containment of a point in [minimum-margin, maximum+margin]. Point and spot world-light admission share this expanded-AABB broad phase; it is not an exact Euclidean sphere/AABB test.
bool __cdecl rf_point_within_expanded_aabb(float *a1, float a2, float *a3, float *a4)
{
  int v5[3]; // [esp+4h] [ebp-18h] BYREF
  int v6[3]; // [esp+10h] [ebp-Ch] BYREF

  rf_vector3_subtract_scalar_from_components(a3, (float *)v6, a2);
  rf_vector3_add_scalar_to_components(a4, (float *)v5, a2);
  return *(float *)v6 <= (double)*a1
      && *(float *)v5 >= (double)*a1
      && *(float *)&v6[1] <= (double)a1[1]
      && *(float *)&v5[1] >= (double)a1[1]
      && *(float *)&v6[2] <= (double)a1[2]
      && *(float *)&v5[2] >= (double)a1[2];
}

