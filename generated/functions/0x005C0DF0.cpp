// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C0DF0 rf_sound_compute_point_pan
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Returns 0 if backend unavailable or source equals listener. Otherwise 559950 produces normalized source-listener direction and returns distance in ST0. If distance>0.5, returns dot(listener orientation first row, direction), else 0. The old void return type on 559950 caused false pseudocode showing a constant-zero distance.
double __cdecl rf_sound_compute_point_pan(float *point_a)
{
  float v2; // [esp+0h] [ebp-14h]
  float out_direction[3]; // [esp+4h] [ebp-10h] BYREF
  float v4; // [esp+10h] [ebp-4h]

  if ( !rf_sound_backend_ready )
    return 0.0;
  rf_vector3_default_construct_noop(out_direction);
  v2 = 0.0;
  if ( rf_vector3_components_equal(point_a, flt_1DAE7F8) )
    return 0.0;
  v4 = rf_vector3_direction_between_return_distance(out_direction, point_a, flt_1DAE7F8);
  if ( v4 > 0.5 )
    return (float)rf_vector_dot(unk_1DAE7D4, out_direction);
  return v2;
}

