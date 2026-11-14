// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00518510 rf_nav_segment_avoids_point_except_start
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Cdecl avoidPoint3f,segmentStart3f,segmentEnd3f,squaredThreshold float. Exact threshold0 returns1. Otherwise computes closest point on segment via56CBA0(discarding its x87 return);vector-equality helper matching closest to segmentStart returns1 WITHOUT distance test. Else returns1 iff threshold<=squaredDistance(avoid,closest),including unordered via TEST AH,41h/JNZ. Thus start-endpoint shortcut can accept a segment starting within exclusion radius;threshold is compared directly to SQUARED distance,not squared internally. No pointer/finite/negative-threshold validation. Corrected integer segmentEnd to pointer;caller-pop16 unchanged.
bool __cdecl rf_nav_segment_avoids_point_except_start(
        const float *avoid_point,
        const float *segment_start,
        const float *segment_end,
        float squared_threshold)
{
  float closest_point[3]; // [esp+0h] [ebp-Ch] BYREF

  if ( squared_threshold == 0.0 )
    return 1;
  rf_vector3_default_construct_noop(closest_point);
  rf_vector3_closest_point_on_segment(avoid_point, segment_start, segment_end, closest_point);
  return rf_vector3_components_equal(closest_point, (float *)segment_start)
      || squared_threshold <= rf_vector_distance_squared(avoid_point, closest_point);
}

