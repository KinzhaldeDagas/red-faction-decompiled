// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C0FF0 rf_sound_compute_segment_doppler_frequency
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): As point Doppler, but uses the point on the supplied segment nearest the listener. Returns 11025 when unavailable and original frequency at equality. Uses opposite normalized directions and constant 600 in the velocity ratio; rounds through a float temporary then truncates to int. No denominator guard.
int __cdecl rf_sound_compute_segment_doppler_frequency(int a1, float *segment_start, float *segment_end, float *a4)
{
  float point_a[3]; // [esp+0h] [ebp-30h] BYREF
  float out_direction[3]; // [esp+Ch] [ebp-24h] BYREF
  float v7[3]; // [esp+18h] [ebp-18h] BYREF
  float v8; // [esp+24h] [ebp-Ch]
  float v9; // [esp+28h] [ebp-8h]

  if ( !rf_sound_backend_ready )
    return 11025;
  rf_vector3_default_construct_noop(out_direction);
  rf_vector3_default_construct_noop(v7);
  rf_vector3_default_construct_noop(point_a);
  rf_vector3_closest_point_on_segment(flt_1DAE7F8, segment_start, segment_end, point_a);
  if ( rf_vector3_components_equal(point_a, flt_1DAE7F8) )
    return a1;
  rf_vector3_direction_between_return_distance(out_direction, point_a, flt_1DAE7F8);
  rf_vector3_direction_between_return_distance(v7, flt_1DAE7F8, point_a);
  v8 = rf_vector_dot(out_direction, unk_1DAE804);
  v9 = rf_vector_dot(v7, a4);
  return (int)(float)((double)a1 * ((v8 + 600.0) / (600.0 - v9)));
}

