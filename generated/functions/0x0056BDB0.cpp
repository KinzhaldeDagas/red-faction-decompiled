// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056BDB0 sub_56BDB0
// UNREALRED VERIFIED [combat-native-query-20261104]: Two-sided plane query stores dot(delta,N) asfloat and rejects exactzero; computes stored float signed distance dot(start,N)+d and returns float(-distance/denominator). No fraction interval/front-side restriction here;5170E0 adds its own absolute endpoint tolerance.
char __cdecl sub_56BDB0(float *a1, float *a2, float *a3)
{
  float v4; // [esp+0h] [ebp-8h]
  float v5; // [esp+4h] [ebp-4h]

  v5 = rf_vector_dot(a1 + 3, a2);
  if ( v5 == 0.0 )
    return 0;
  v4 = rf_plane_point_signed_distance(a2, a1);
  *a3 = -v4 / v5;
  return 1;
}

