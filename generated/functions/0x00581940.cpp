// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581940 rf_renderer_normal_dot_direction_to_camera
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Recovered cdecl(normal3f,worldPoint3f),returns floating ST0. Forms local camera18CD5E8-worldPoint,unchecked-normalizes,returns dot(normal,normalizedDirection). Source vectors unchanged;normal not normalized,so only cosine when caller normal unit length. No own coincident-camera/finite guard. Not a boolean facing predicate;original instructions leave vector-dot ST0 result.
double __cdecl rf_renderer_normal_dot_direction_to_camera(const float *a1, const float *a2)
{
  float out_vector[3]; // [esp+0h] [ebp-Ch] BYREF

  rf_vector_subtract(&flt_18CD5E8, out_vector, a2);
  rf_vector_normalize_reciprocal_sqrt(out_vector);
  return rf_vector_dot(out_vector, (float *)a1);
}

