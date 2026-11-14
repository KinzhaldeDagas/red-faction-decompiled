// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C10D0 rf_sound_voice_start_at_point
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Rejects unavailable backend, index==-1, failed lazy load, or computed point gain<0.05 with -1. Mode 1 with 3D-mode byte exactly 1 starts a static 3D sample with zero velocity, record distances/base gain, loop byte, and final argument. Otherwise computes point pan and starts looping (frequency scale 1, final 0) or nonlooping (caller final argument, final flag 1). Other backend modes return -1. No upper index check.
int __cdecl rf_sound_voice_start_at_point(int a1, float *a2, char a3, float a4)
{
  float v5; // [esp+18h] [ebp-1Ch]
  int v6[3]; // [esp+1Ch] [ebp-18h] BYREF
  int v7; // [esp+28h] [ebp-Ch]
  char *v8; // [esp+2Ch] [ebp-8h]
  float v9; // [esp+30h] [ebp-4h]

  if ( !rf_sound_backend_ready )
    return -1;
  if ( a1 == -1 )
    return -1;
  v8 = &rf_sound_resource_registry[64 * a1];
  if ( rf_sound_load_entry(a1, 0, 0) == -1 )
    return -1;
  v9 = rf_sound_compute_point_attenuated_gain(a1, a2, 1.0);
  if ( v9 < 0.05000000074505806 )
    return -1;
  v7 = -1;
  if ( rf_sound_backend_mode == 1 )
  {
    if ( rf_sound_backend_get_3d_mode() == 1 )
    {
      rf_vector3_set_components_return_destination((float *)v6, 0.0, 0.0, 0.0);
      return rf_dsound_play_static_3d_sample(
               *((_DWORD *)v8 + 12),
               a2,
               (float *)v6,
               *((float *)v8 + 9),
               *((float *)v8 + 10),
               *((float *)v8 + 8),
               a3);
    }
    else
    {
      v5 = rf_sound_compute_point_pan(a2);
      if ( a3 == 1 )
        return rf_sound_voice_start_looping(a1, v9, v5, 1.0, 0);
      else
        return rf_sound_voice_start_nonlooping(a1, v9, v5, a4, 1);
    }
  }
  return v7;
}

