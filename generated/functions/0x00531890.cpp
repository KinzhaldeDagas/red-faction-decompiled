// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00531890 rf_geomod_point_to_face_edge_distance_squared
// UNREALRED VERIFIED [combat-polygon-boundary-20261104]: Forms edge B-A; stores40CFA0 length asfloat. Length<0.0001f uses distanceSquared(A,query). Otherwise scales edge by float(1/length), constructs plane with that normalized edge and query point via41CA80/41CAB0 (d=float(-dot(edge,query))), stores41CB40 signed distance at A asfloat, projects A-edge*distance, then5598C0 distanceSquared(projectedPoint,query). No [0,1] or endpoint clamp. Point beyond the edge endpoints can have zero line distance and trigger5317F0; algebraically collapsed dot/lengthSquared is not the native store order.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, boundary x87 failure reproduction, fixed stack ABI, line projection, exact PE thresholds and original bytes): Corrected saved VOID/variadic ABI to fixed36-byte cdecl stack containing THREE by-value XYZ triples A,B,Q (represented as9float words in prototype),floating ST0 return. No varargs walk or incoming x87 argument. u=B-A,L=float vector length. Ordered L<0.00009999999747378752 returns squaredDistance(A,Q);otherwise (including unordered comparison)u/=L,construct plane(u,Q),d=dot(u,A-Q),P=A-u*d,returns squaredDistance(P,Q). This is distance to INFINITE SUPPORTING LINE throughA/B,not clamped finite segment;Q beyond either endpoint can still have zero line distance. Small-edge fallback usesA only. Caller passes current corner,next corner,query using36bytes. No normal/finite guard or interpolation clamp;new
// vector-distance-squared signature supplies return rather than bogus undefined ST0.
double __cdecl rf_geomod_point_to_face_edge_distance_squared(
        float rhs,
        float a2,
        float a3,
        float lhs,
        float a5,
        float a6,
        float a7,
        float a8,
        float a9)
{
  float *v10; // eax
  float v11; // [esp+4h] [ebp-40h]
  float scaled_result[3]; // [esp+8h] [ebp-3Ch] BYREF
  float scalar; // [esp+14h] [ebp-30h]
  float v14; // [esp+18h] [ebp-2Ch]
  float out_vector[3]; // [esp+1Ch] [ebp-28h] BYREF
  float v16[3]; // [esp+28h] [ebp-1Ch] BYREF
  float v17[4]; // [esp+34h] [ebp-10h] BYREF

  rf_vector_subtract(&lhs, out_vector, &rhs);
  v14 = rf_vector3_length(out_vector);
  if ( v14 < 0.00009999999747378752 )
    return rf_vector_distance_squared(&rhs, &a7);
  v11 = 1.0 / v14;
  rf_vector3_scale_in_place_return_self(out_vector, v11);
  rf_plane_construct_from_normal_point(v17, out_vector, (int)&a7);
  scalar = rf_plane_point_signed_distance(v17, &rhs);
  v10 = rf_vector_multiply_scalar(out_vector, scaled_result, scalar);
  rf_vector_subtract(&rhs, v16, v10);
  return rf_vector_distance_squared(v16, &a7);
}

