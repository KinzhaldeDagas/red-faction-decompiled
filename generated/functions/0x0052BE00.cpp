// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052BE00 rf_aabb_min_max_points_inside_aabb
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl innerBoundsContiguousMinMax,outerMin,outerMax ALbool. Return inclusive containment(inner.min0,outer) AND containment(inner.max12,outer), short-circuit onfirstfalse. No overlapclassification2 return; caller separately uses0partial/1contained/2outside states. No min<=max normalization, finitecheck or mutation.
bool __cdecl rf_aabb_min_max_points_inside_aabb(float *a1, float *a2, float *a3)
{
  return rf_aabb_contains_point_inclusive(a1, a2, a3) && rf_aabb_contains_point_inclusive(a1 + 3, a2, a3);
}

