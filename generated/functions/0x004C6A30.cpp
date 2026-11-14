// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C6A30 rf_glass_find_first_room_face_segment_hit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, persistent shard pool and keyed buckets, launch-delay/damage cadence, first-hit face traversal, native ordered branches and settling ownership): 
// Cdecl(room,segmentMin,segmentMax,startDeltaPair,result40). Strict ordered AABB overlap(segment bounds,room min8/max20), then source-order face chain from room list40 via
// next_room_link. Each strict face AABB16/28 overlap ->one-sided front-plane helper569600(startPair0,delta12,face,&t). Requires STRICT ORDERED t<1; equality/NaN skips, no independent
// t>=0 test here. Computes F32candidate=start+delta*t and writes result.point8 BEFORE projected polygon containment; failed containment can therefore modify point on final AL0.
// FIRST contained candidate immediately copies face normal0 to result.normal20, fraction4=t,face36=face and returnsAL1. No nearest-hit scan or comparison to incoming result.fraction;
// result.count0 and edge32 NOT written, so AL is authoritative even if count remains0. Other fields remain untouched on false except attempted candidate points. No face
// material/portal/liquid exclusion, roomNULL/list-cycle/finite guard or zero-area fallback in this body.
char __cdecl rf_glass_find_first_room_face_segment_hit(float *a1, float *a2, float *a3, float *lhs, int a5)
{
  float *v5; // eax
  float *v6; // eax
  float v8[3]; // [esp+4h] [ebp-38h] BYREF
  float copy_result[3]; // [esp+10h] [ebp-2Ch] BYREF
  float sum_result[3]; // [esp+1Ch] [ebp-20h] BYREF
  float scaled_result[3]; // [esp+28h] [ebp-14h] BYREF
  float scalar; // [esp+34h] [ebp-8h] BYREF
  float *source; // [esp+38h] [ebp-4h]

  if ( rf_aabb_overlap_strict_ordered(a2, a3, a1 + 2, a1 + 5) )
  {
    for ( source = (float *)rf_receiver_get_first_dword(a1 + 10);
          source;
          source = (float *)rf_face_next_room_link((int)source) )
    {
      if ( rf_aabb_overlap_strict_ordered(source + 4, source + 7, a2, a3) )
      {
        if ( rf_polygon_segment_intersect_front_plane(lhs, lhs + 3, source, &scalar) )
        {
          if ( scalar < 1.0 )
          {
            v5 = rf_vector_multiply_scalar(lhs + 3, scaled_result, scalar);
            v6 = rf_vector_add(lhs, sum_result, v5);
            rf_vector_copy((float *)(a5 + 8), copy_result, v6);
            if ( rf_geomod_face_contains_projected_point(source, a5 + 8) )
            {
              rf_vector_copy((float *)(a5 + 20), v8, source);
              *(float *)(a5 + 4) = scalar;
              *(_DWORD *)(a5 + 36) = source;
              return 1;
            }
          }
        }
      }
    }
  }
  return 0;
}

