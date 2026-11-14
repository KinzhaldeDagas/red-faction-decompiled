// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559950 rf_vector3_direction_between_return_distance
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Three cdecl pointer arguments (outDirection, pointA, pointB). Subtracts pointB from pointA into outDirection, normalizes it in place through 559280, and leaves the ORIGINAL DISTANCE in x87 ST0 as the return value. No zero-distance guard. The old void return type was incorrect: callers explicitly FSTP the distance, including 5C0BAE and 5C0E3F.
float __cdecl rf_vector3_direction_between_return_distance(
        float *out_direction,
        const float *point_a,
        const float *point_b)
{
  float *v3; // eax
  float copy_result[3]; // [esp+0h] [ebp-18h] BYREF
  float out_vector[3]; // [esp+Ch] [ebp-Ch] BYREF

  v3 = rf_vector_subtract(point_a, out_vector, point_b);
  rf_vector_copy(out_direction, copy_result, v3);
  return rf_vector3_normalize_return_length(out_direction);
}

