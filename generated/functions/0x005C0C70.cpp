// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C0C70 rf_sound_compute_segment_attenuated_gain
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Computes the point on a segment nearest the listener via 56CBA0, then applies the same inverse-distance gain law as point attenuation. At exact listener equality returns base_gain*scale*group_gain without upper clamp. Else normalizes listener-to-nearest-point displacement, measures distance, returns 0 beyond max_distance, attenuates above min_distance, multiplies group gain, and caps at 1. Scale above 1 is ignored outside the equality path. No index or denominator-range validation.
double __cdecl rf_sound_compute_segment_attenuated_gain(int a1, float *segment_start, float *segment_end, float a4)
{
  float *v5; // eax
  float copy_result[3]; // [esp+Ch] [ebp-44h] BYREF
  float out_vector[3]; // [esp+18h] [ebp-38h] BYREF
  float v9; // [esp+24h] [ebp-2Ch]
  float lhs[3]; // [esp+28h] [ebp-28h] BYREF
  char *v11; // [esp+34h] [ebp-1Ch]
  float v12; // [esp+38h] [ebp-18h]
  float v13; // [esp+3Ch] [ebp-14h]
  float v14; // [esp+40h] [ebp-10h]
  float destination[3]; // [esp+44h] [ebp-Ch] BYREF

  if ( !rf_sound_backend_ready )
    return 0.0;
  v11 = &rf_sound_resource_registry[64 * a1];
  v12 = 0.0;
  rf_vector3_default_construct_noop(lhs);
  rf_vector3_default_construct_noop(destination);
  rf_vector3_closest_point_on_segment(flt_1DAE7F8, segment_start, segment_end, lhs);
  if ( rf_vector3_components_equal(lhs, flt_1DAE7F8) )
  {
    return (float)(*((float *)v11 + 8) * a4 * unk_1DAE7B8[*((_DWORD *)v11 + 13)]);
  }
  else
  {
    v5 = rf_vector_subtract(lhs, out_vector, flt_1DAE7F8);
    rf_vector_copy(destination, copy_result, v5);
    v14 = rf_vector3_length(destination);
    rf_vector_normalize_reciprocal_sqrt(destination);
    v13 = *((float *)v11 + 8);
    if ( a4 < 1.0 )
      v13 = v13 * a4;
    if ( *((float *)v11 + 10) >= (double)v14 )
    {
      if ( *((float *)v11 + 9) < (double)v14 )
      {
        v9 = (v14 / *((float *)v11 + 9) - 1.0) * *((float *)v11 + 11) + 1.0;
        if ( v9 != 0.0 )
          v12 = v13 / v9;
      }
      else
      {
        v12 = v13;
      }
      v12 = v12 * unk_1DAE7B8[*((_DWORD *)v11 + 13)];
      return (float)rf_float_minimum_two_values(v12, 1.0);
    }
    else
    {
      return 0.0;
    }
  }
}

