// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568D20 rf_sound_update_listener_and_instances
// Copies the supplied camera position and orientation right-vector into the listener globals, updates active positional voices, and admits/stops ambient voices by recomputed gain. The listener must converge to a newly possessed local body before event 58 is played.
// UNREALRED VERIFIED [ambient-audio]: Updates listener transforms, 30 common positioned voices, and all 25 reserved ambient frontend slots. Ambient backend playback starts when recomputed gain is at least 0.1 and stops below 0.1 while the frontend slot remains reserved.
void __cdecl rf_sound_update_listener_and_instances(float *source, float *a2, float *a3)
{
  int started; // eax
  int v4; // eax
  float v5; // [esp+Ch] [ebp-6Ch]
  float v6[3]; // [esp+10h] [ebp-68h] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-5Ch] BYREF
  int v8; // [esp+28h] [ebp-50h] BYREF
  int v9; // [esp+2Ch] [ebp-4Ch] BYREF
  int *v10; // [esp+30h] [ebp-48h]
  int *v11; // [esp+34h] [ebp-44h]
  float v12[3]; // [esp+38h] [ebp-40h] BYREF
  float v13[3]; // [esp+44h] [ebp-34h] BYREF
  int i; // [esp+50h] [ebp-28h]
  _BYTE v15[36]; // [esp+54h] [ebp-24h] BYREF

  if ( rf_sound_system_ready[0] )
  {
    rf_vector3_copy_return_destination(v13, source);
    rf_vector3_copy_return_destination(v12, a2);
    rf_matrix3_copy_construct((int)v15, a3);
    rf_sound_backend_set_listener_transform((int)v13, (int)v12, (int)v15);
    rf_vector_copy(unk_1808BC0, copy_result, source);
    rf_vector_copy(unk_18090F8, v6, a3);
    for ( i = 0; i < 30; ++i )
    {
      v11 = &rf_gamesound_voice_pool[11 * i];
      if ( v11[1] >= 0 )
      {
        if ( *((_BYTE *)v11 + 40) )
          rf_positioned_voice_update(i | (v11[3] << 8), (float *)v11 + 6, (int)flt_17F10B0, *((float *)v11 + 9));
      }
    }
    for ( i = 0; i < 25; ++i )
    {
      v10 = &rf_ambient_voice_pool[6 * i];
      if ( *v10 >= 0 )
      {
        rf_gamesound_spatialize_event(*v10, (float *)v10 + 2, (float *)&v9, (float *)&v8, *((float *)v10 + 5));
        *(float *)&v8 = *(float *)&v8 * rf_sound_channel_group_gains[rf_ambient_voice_channel_group];
        if ( v10[1] < 0 )
        {
          if ( *(float *)&v8 >= 0.1000000014901161 )
          {
            if ( unk_1D85DF6[64 * *v10] )
            {
              started = rf_sound_voice_start_looping(*v10, *(float *)&v8, *(float *)&v9, 0.0, 0);
              v10[1] = started;
            }
            else
            {
              v4 = rf_sound_voice_start_nonlooping(*v10, *(float *)&v8, *(float *)&v9, 0.0, 0);
              v10[1] = v4;
            }
          }
        }
        else if ( *(float *)&v8 >= 0.1000000014901161 )
        {
          if ( unk_1D85DF6[64 * *v10] )
          {
            v5 = rf_sound_compute_point_attenuated_gain(*v10, (float *)v10 + 2, 1.0);
            rf_sound_backend_voice_set_gain(v10[1], v5);
          }
        }
        else
        {
          rf_sound_backend_voice_stop(v10[1]);
          v10[1] = -1;
        }
      }
    }
  }
}

