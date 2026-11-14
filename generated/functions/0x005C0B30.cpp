// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C0B30 rf_sound_compute_point_attenuated_gain
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): CORRECTION to the older streaming-position annotation: computes a gain and does NOT set any backend voice position. If not ready returns 0. At listener/source equality returns base_gain*scale*group_gain without upper clamp. Otherwise gets distance and normalized direction from 559950. Multiplies base_gain by scale only when scale<1. Outside max_distance(+40) returns 0; within min_distance(+36) retains gain; otherwise divides by ((distance/min_distance-1)*rolloff(+44)+1), leaving zero if divisor is zero. Multiplies group_gain and returns min(gain,1). No lower clamp or index validation.
double __cdecl rf_sound_compute_point_attenuated_gain(int a1, float *point_a, float a3)
{
  float v5; // [esp+Ch] [ebp-20h]
  char *v6; // [esp+10h] [ebp-1Ch]
  float v7; // [esp+14h] [ebp-18h]
  float v8; // [esp+14h] [ebp-18h]
  float v10; // [esp+18h] [ebp-14h]
  float v11; // [esp+1Ch] [ebp-10h]
  float out_direction[3]; // [esp+20h] [ebp-Ch] BYREF

  if ( !rf_sound_backend_ready )
    return 0.0;
  v6 = &rf_sound_resource_registry[64 * a1];
  v7 = 0.0;
  if ( rf_vector3_components_equal(point_a, flt_1DAE7F8) )
  {
    return (float)(*((float *)v6 + 8) * a3 * unk_1DAE7B8[*((_DWORD *)v6 + 13)]);
  }
  else
  {
    rf_vector3_default_construct_noop(out_direction);
    v11 = rf_vector3_direction_between_return_distance(out_direction, point_a, flt_1DAE7F8);
    v10 = *((float *)v6 + 8);
    if ( a3 < 1.0 )
      v10 = v10 * a3;
    if ( *((float *)v6 + 10) >= (double)v11 )
    {
      if ( *((float *)v6 + 9) < (double)v11 )
      {
        v5 = (v11 / *((float *)v6 + 9) - 1.0) * *((float *)v6 + 11) + 1.0;
        if ( v5 != 0.0 )
          v7 = v10 / v5;
      }
      else
      {
        v7 = v10;
      }
      v8 = v7 * unk_1DAE7B8[*((_DWORD *)v6 + 13)];
      return (float)rf_float_minimum_two_values(v8, 1.0);
    }
    else
    {
      return 0.0;
    }
  }
}

