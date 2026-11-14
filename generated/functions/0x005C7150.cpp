// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C7150 rf_positional_sound_update_point
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Requires initialized flag and unsigned instance index<128; does not test allocated bit. Processes only when deadline has elapsed, then resets deadline by interval +72, copies input position to +36 and velocity to +60 (or zero if NULL). Suspended bit 2 skips playback work. Hardware-selection helper is constant 0: effective path updates software gain, then pan and optional Doppler if loop flag or backend says playing, handle>=0 and cached gain>0. Doppler requires a non-NULL, nonzero input velocity. Copies current position into previous position +48 only when this processing path reaches its tail. Encoded hardware branch performs DirectSound emitter updates but is bypassed by the constant selector.
void __cdecl rf_positional_sound_update_point(unsigned int a1, float *source, float *a3, float a4)
{
  float v4; // [esp+10h] [ebp-3Ch]
  float v5[3]; // [esp+14h] [ebp-38h] BYREF
  float v6[3]; // [esp+20h] [ebp-2Ch] BYREF
  float copy_result[3]; // [esp+2Ch] [ebp-20h] BYREF
  float *v8; // [esp+38h] [ebp-14h] BYREF
  int buffer_slot_by_play_handle; // [esp+3Ch] [ebp-10h]
  float v10; // [esp+40h] [ebp-Ch]
  char v11; // [esp+47h] [ebp-5h]
  int *v12; // [esp+48h] [ebp-4h]

  if ( byte_1DAEE54 )
  {
    if ( a1 < 0x80 )
    {
      v12 = &unk_1DAEE58[27 * a1];
      if ( rf_clock_deadline_has_elapsed_half_period(v12 + 19) )
      {
        rf_clock_deadline_set_wrapped_offset(v12 + 19, v12[18]);
        rf_vector_copy((float *)v12 + 9, copy_result, source);
        if ( a3 )
          rf_vector_copy((float *)v12 + 15, v6, a3);
        else
          rf_vector3_zero_return_destination((float *)v12 + 15);
        if ( (v12[20] & 2) == 0 )
        {
          if ( rf_positional_sound_use_hardware_3d_disabled() == 1 )
          {
            if ( (v12[20] & 4) != 0 )
              v10 = rf_sound_compute_segment_attenuated_gain(v12[2], (float *)v12 + 21, (float *)v12 + 24, a4);
            else
              v10 = rf_sound_compute_point_attenuated_gain(v12[2], (float *)v12 + 9, a4);
            v11 = 1;
            if ( v10 <= 0.1000000014901161 )
            {
              if ( (v12[20] & 8) != 0 )
              {
                rf_positional_sound_stop_voice(a1, 0);
                v11 = 0;
              }
              else
              {
                v10 = 0.0;
              }
            }
            *((float *)v12 + 4) = v10;
            if ( v11 == 1 )
            {
              buffer_slot_by_play_handle = rf_dsound_find_buffer_slot_by_play_handle(v12[3]);
              if ( buffer_slot_by_play_handle < 0 )
              {
                rf_positional_sound_start_voice_with_budget(a1);
                *((float *)v12 + 6) = -1.0;
              }
              buffer_slot_by_play_handle = rf_dsound_find_buffer_slot_by_play_handle(v12[3]);
              if ( buffer_slot_by_play_handle >= 0 && !rf_sound_resource_get_record_out(v12[2], &v8) )
              {
                if ( a4 != *((float *)v12 + 6) )
                {
                  v4 = v8[8] * v10;
                  rf_sound_backend_voice_set_gain(v12[3], v4);
                  *((float *)v12 + 6) = a4;
                }
                if ( rf_vector3_components_not_equal((float *)v12 + 9, (float *)v12 + 12) )
                  rf_dsound3d_set_emitter_position_velocity_distances(
                    buffer_slot_by_play_handle,
                    v8[9],
                    v8[10],
                    (float *)v12 + 9,
                    (float *)v12 + 15);
              }
            }
LABEL_34:
            rf_vector_copy((float *)v12 + 12, v5, (const float *)v12 + 9);
            return;
          }
          rf_positional_sound_update_software_gain(a1, a4);
          if ( ((v12[20] & 8) != 0 || rf_sound_backend_voice_is_playing(v12[3]))
            && v12[3] >= 0
            && *((float *)v12 + 4) > 0.0 )
          {
            rf_positional_sound_update_software_pan(a1);
            if ( a3 && !rf_vector3_is_exact_zero(a3) )
              rf_positional_sound_update_doppler(a1);
            goto LABEL_34;
          }
        }
      }
    }
  }
}

