// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B1960 rf_plane_intersects_aabb_closed
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, character state/action time advancement, hold/event/ownership edges, AABB support/corner math, sort comparator and original x87/stack ABI): Cdecl(boundsMin,boundsMax,plane),12-byte caller cleanup. Selects min/max support corner indices via5B1830,builds min corner and returnsfalse only when its signed plane distance is ORDERED>0. Then builds max corner; returns true when distance is ordered>=0 OR UNORDERED(raw5B19E3 TEST AH,5/JP). Thus finite valid bounds return true exactly when plane straddles/touches box,minDistance<=0<=maxDistance; entirely front or entirely behind returnfalse. This is a plane INTERSECTION predicate,not a positive-halfspace/frustum acceptance test. Equality included at both boundaries. NaN is not rejected: unordered minimum proceeds and unordered maximum returns true,unlike decompiled >=0
// expression. No output writes,bounds ordering/normal normalization/pointer guard; corrected corner-selector type removes false pointer locals.
bool __cdecl rf_plane_intersects_aabb_closed(float *bounds_min, float *bounds_max, float *a3)
{
  unsigned int v4; // [esp+0h] [ebp-14h] BYREF
  float out_vector[3]; // [esp+4h] [ebp-10h] BYREF
  unsigned int corner_index; // [esp+10h] [ebp-4h] BYREF

  rf_vector3_default_construct_noop(out_vector);
  rf_plane_select_aabb_support_corners(a3, &corner_index, &v4);
  rf_aabb_select_corner_by_index(out_vector, corner_index, bounds_min, bounds_max);
  if ( rf_plane_point_signed_distance(a3, out_vector) > 0.0 )
    return 0;
  rf_aabb_select_corner_by_index(out_vector, v4, bounds_min, bounds_max);
  return rf_plane_point_signed_distance(a3, out_vector) >= 0.0;
}

