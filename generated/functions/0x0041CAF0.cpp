// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041CAF0 rf_plane_project_point_assuming_unit_normal
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, glare visibility/reflection and cached-query initialization, native flags/x87 gates and static ownership): Thiscall plane(normalXYZ,D), stack(destinationVec3,sourceVec3),RET8. Copies negative normal to local vector, computes plane signed distance dot(normal,source)+D, rounds scalar to binary32 for cdecl scale helper, and writes source-distance*normal through vector add; returns destination pointer. No division by normal squared length or normalization, so this is true orthogonal plane projection only for unit normals. No null/finite/degenerate-normal check or source-plane mutation.
float *__thiscall rf_plane_project_point_assuming_unit_normal(float *this, float *sum_result, float *lhs)
{
  float *v3; // eax
  float v5; // [esp+0h] [ebp-24h]
  float *v6; // [esp+4h] [ebp-20h]
  float v8[3]; // [esp+Ch] [ebp-18h] BYREF
  float v9[3]; // [esp+18h] [ebp-Ch] BYREF

  v6 = rf_vector_negate(this, v9);
  v5 = rf_plane_point_signed_distance(this, lhs);
  v3 = rf_vector_scale(v8, v5, v6);
  rf_vector_add(lhs, sum_result, v3);
  return sum_result;
}

