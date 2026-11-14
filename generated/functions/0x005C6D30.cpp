// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6D30 rf_positional_sound_update_doppler
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Computes point or segment Doppler from base frequency +32 and velocity +60. If abs(newFrequency-cachedFrequency)>100, updates cached frequency +28 and calls backend_voice_set_frequency. Otherwise returns the absolute difference. Cache is written before the lower setter applies its unsigned [100,100000] clamp.
int __cdecl rf_positional_sound_update_doppler(int a1)
{
  int result; // eax
  int v2; // [esp+0h] [ebp-8h]
  int *v3; // [esp+4h] [ebp-4h]

  v3 = &unk_1DAEE58[27 * a1];
  if ( (v3[20] & 4) != 0 )
    v2 = rf_sound_compute_segment_doppler_frequency(v3[8], (float *)v3 + 21, (float *)v3 + 24, (float *)v3 + 15);
  else
    v2 = rf_sound_compute_point_doppler_frequency(v3[8], (float *)v3 + 9, (float *)v3 + 15);
  result = abs32(v2 - v3[7]);
  if ( result > 100 )
  {
    v3[7] = v2;
    return rf_sound_backend_voice_set_frequency(v3[3], v2);
  }
  return result;
}

