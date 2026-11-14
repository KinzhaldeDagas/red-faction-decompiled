// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6B80 rf_positional_sound_update_software_gain
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Uses segment attenuation when flags bit 4 is set, otherwise point attenuation. Gain>0.1 updates the current voice if handle>=0 and either nonlooping or the loop is still playing; otherwise caches gain and attempts budgeted start. Gain<=0.1 stops a looping voice; for nonloops, sends zero gain and caches zero. Stopping a loop leaves its old cached gain. No upper-level instance bounds/state validation here.
void __cdecl rf_positional_sound_update_software_gain(int a1, float a2)
{
  float v2; // [esp+4h] [ebp-8h]
  int *v3; // [esp+8h] [ebp-4h]

  v3 = &unk_1DAEE58[27 * a1];
  if ( (v3[20] & 4) != 0 )
    v2 = rf_sound_compute_segment_attenuated_gain(v3[2], (float *)v3 + 21, (float *)v3 + 24, a2);
  else
    v2 = rf_sound_compute_point_attenuated_gain(v3[2], (float *)v3 + 9, a2);
  if ( v2 > 0.1000000014901161 )
  {
    if ( v3[3] >= 0 && ((v3[20] & 8) == 0 || rf_sound_backend_voice_is_playing(v3[3])) )
    {
      rf_sound_backend_voice_set_gain(v3[3], v2);
      *((float *)v3 + 4) = v2;
    }
    else
    {
      *((float *)v3 + 4) = v2;
      rf_positional_sound_start_voice_with_budget(a1);
    }
  }
  else if ( (v3[20] & 8) != 0 )
  {
    rf_positional_sound_stop_voice(a1, 0);
  }
  else
  {
    rf_sound_backend_voice_set_gain(v3[3], 0.0);
    *((float *)v3 + 4) = 0.0;
  }
}

