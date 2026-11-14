// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C0E70 rf_sound_compute_segment_pan
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Finds the segment point nearest the listener. Returns 0 when unavailable, at equality, or distance<=0.5. Otherwise returns dot(listener orientation first row, nearestPoint-listener). This path does NOT normalize the displacement, unlike point pan, so the result is distance-scaled and is not inherently bounded to [-1,1].
double __cdecl rf_sound_compute_segment_pan(float *segment_start, float *segment_end)
{
  float *v3; // eax
  float copy_result[3]; // [esp+0h] [ebp-38h] BYREF
  float out_vector[3]; // [esp+Ch] [ebp-2Ch] BYREF
  float lhs[3]; // [esp+18h] [ebp-20h] BYREF
  float v7; // [esp+24h] [ebp-14h]
  float destination[3]; // [esp+28h] [ebp-10h] BYREF
  float v9; // [esp+34h] [ebp-4h]

  if ( !rf_sound_backend_ready )
    return 0.0;
  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(lhs);
  v7 = 0.0;
  rf_vector3_closest_point_on_segment(flt_1DAE7F8, segment_start, segment_end, lhs);
  if ( rf_vector3_components_equal(lhs, flt_1DAE7F8) )
    return 0.0;
  v3 = rf_vector_subtract(lhs, out_vector, flt_1DAE7F8);
  rf_vector_copy(destination, copy_result, v3);
  v9 = rf_vector3_length(destination);
  if ( v9 > 0.5 )
    return (float)rf_vector_dot(unk_1DAE7D4, destination);
  return v7;
}

