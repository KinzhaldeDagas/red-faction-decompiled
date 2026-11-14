// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568300 rf_gamesound_spatialize_event
// Computes positional event distance attenuation and pan from the current listener globals. A source beyond the authored maximum distance returns zero gain before voice allocation.
// UNREALRED VERIFIED [sound-spatialization]: Uses sound-record min/max/rolloff at +0x24/+0x28/+0x2C. Gain is zero beyond max, unity through min, otherwise source_gain / (((distance/min)-1)*rolloff+1); pan derives from listener-relative direction.
void __cdecl rf_gamesound_spatialize_event(int a1, float *lhs, float *a3, float *a4, float a5)
{
  float v5; // [esp+8h] [ebp-18h]
  float out_vector[3]; // [esp+Ch] [ebp-14h] BYREF
  float v7; // [esp+18h] [ebp-8h]
  float *v8; // [esp+1Ch] [ebp-4h]

  v8 = (float *)&rf_sound_resource_registry[64 * a1];
  rf_vector_subtract(lhs, out_vector, unk_1808BC0);
  v7 = rf_vector3_length(out_vector);
  if ( v8[10] >= (double)v7 )
  {
    if ( v8[9] <= (double)v7 )
    {
      v5 = (v7 / v8[9] - 1.0) * v8[11] + 1.0;
      if ( v5 == 0.0 )
        *a4 = a5;
      else
        *a4 = a5 / v5;
    }
    else
    {
      *a4 = a5;
    }
    rf_float_clamp_in_place(a4, 0.0, a5);
    if ( v7 == 0.0 )
    {
      *a3 = 0.0;
    }
    else
    {
      rf_vector_normalize_reciprocal_sqrt(out_vector);
      *a3 = rf_vector_dot(unk_18090F8, out_vector);
    }
  }
  else
  {
    *a3 = 0.0;
    *a4 = 0.0;
  }
}

