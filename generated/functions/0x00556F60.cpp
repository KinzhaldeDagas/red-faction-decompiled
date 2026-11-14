// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556F60 rf_face_aabb_inside_bounds_inclusive
// UNREALRED VERIFIED [particle-contact-geometry-20261104] Returns true only when both face AABB corners at +16 and +28 are inclusively inside the supplied candidate bounds, via 0x56AD40. Used by 0x557050 for child assignment. Because that caller tests the high half first, a face exactly on the partition plane that fits both halves goes to the high child.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Tests BOTH face AABB corners16 and28 against supplied min/max via inclusive point predicate56AD40, short-circuiting false. No plane/actual-corner geometry test. Tree split checks high half first, so face exactly on split and fitting both goes to high child.
bool __cdecl rf_face_aabb_inside_bounds_inclusive(int a1, float *a2, float *a3)
{
  return rf_aabb_contains_point_inclusive((float *)(a1 + 16), a2, a3)
      && rf_aabb_contains_point_inclusive((float *)(a1 + 28), a2, a3);
}

