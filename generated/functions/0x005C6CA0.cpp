// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6CA0 rf_positional_sound_update_software_pan
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Selects segment or point pan from flags bit 4. If abs(previousPan-newPan)>0.1, forwards new pan to the backend voice and caches it at +20. Equality at threshold does nothing. The segment calculation uses raw displacement and can exceed [-1,1]; this wrapper does not clamp it.
void __cdecl rf_positional_sound_update_software_pan(int a1)
{
  float v1; // [esp+4h] [ebp-Ch]
  int *v2; // [esp+8h] [ebp-8h]
  float v3; // [esp+Ch] [ebp-4h]

  v2 = &unk_1DAEE58[27 * a1];
  if ( (v2[20] & 4) != 0 )
    v3 = rf_sound_compute_segment_pan((float *)v2 + 21, (float *)v2 + 24);
  else
    v3 = rf_sound_compute_point_pan((float *)v2 + 9);
  v1 = fabs(*((float *)v2 + 5) - v3);
  if ( v1 > 0.1000000014901161 )
  {
    rf_sound_backend_voice_set_pan(v2[3], v3);
    *((float *)v2 + 5) = v3;
  }
}

