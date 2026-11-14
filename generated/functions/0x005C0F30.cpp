// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C0F30 rf_sound_compute_point_doppler_frequency
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Returns 11025 when backend unavailable, or the original frequency when source equals listener. Forms normalized source-listener and listener-source directions. Returns integer truncation of float(baseFrequency * (600 + dot(source-listener unit, listenerVelocity)) / (600 - dot(listener-source unit, sourceVelocity))). No denominator guard or output clamp here; set-frequency wrapper clamps separately.
int __cdecl rf_sound_compute_point_doppler_frequency(int a1, float *point_a, float *a3)
{
  float out_direction[3]; // [esp+0h] [ebp-24h] BYREF
  float v5[3]; // [esp+Ch] [ebp-18h] BYREF
  float v6; // [esp+18h] [ebp-Ch]
  float v7; // [esp+1Ch] [ebp-8h]

  if ( !rf_sound_backend_ready )
    return 11025;
  rf_vector3_default_construct_noop(out_direction);
  rf_vector3_default_construct_noop(v5);
  if ( rf_vector3_components_equal(point_a, flt_1DAE7F8) )
    return a1;
  rf_vector3_direction_between_return_distance(out_direction, point_a, flt_1DAE7F8);
  rf_vector3_direction_between_return_distance(v5, flt_1DAE7F8, point_a);
  v6 = rf_vector_dot(out_direction, unk_1DAE804);
  v7 = rf_vector_dot(v5, a3);
  return (int)(float)((double)a1 * ((v6 + 600.0) / (600.0 - v7)));
}

