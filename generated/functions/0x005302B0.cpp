// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005302B0 rf_collision_face_cache_append_if_overlap
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Cdecl face,queryMin,queryMax. Call48BE10 on face bounds16/28, requiring six strict ordered comparisons (touching or NaN fails). If true AND SIGNED global count<1024, store raw face pointer at cachedFaces[count], increment count; if new count==1024 set bypassBYTE1. No count>=0 guard or pointer dedup. Already-full count does not itself set bypass, and misses do not clear it. Return AL is overlap-helper byte on miss/full path, but on append it is LOW BYTE OF FACE POINTER left inEAX, possibly0 even after successful append. Corrected stored bool to unsigned-byte ABI; not a success/count result. No face mutation or allocation.
unsigned __int8 __cdecl rf_collision_face_cache_append_if_overlap(int a1, float *a2, float *a3)
{
  unsigned __int8 result; // al

  result = rf_aabb_overlap_strict_ordered((float *)(a1 + 16), (float *)(a1 + 28), a2, a3);
  if ( result && rf_collision_cached_face_count < 1024 )
  {
    result = a1;
    rf_collision_cached_faces[rf_collision_cached_face_count++] = a1;
    if ( rf_collision_cached_face_count == 1024 )
      rf_collision_cache_bypass = 1;
  }
  return result;
}

