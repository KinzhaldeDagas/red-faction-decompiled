// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D0540 rf_audio_stream_service_slot
// UNREALRED VERIFIED [audio-streaming-20261028]: If flags+24 active mask1clear,does nothing. Calculates bytes available since write cursor0x5CFE70; ifnonzero selects ACM filler0x5D02E0 only when source format tag==2,else raw PCM filler0x5CFF00. Ignores filler return status. If EOF mask4set,remaining=available-actual,clearsEOF; loop mask2 triggers wave-data rewind whose result is ignored. Adds remaining to silence-drain counter+20 and fills silence. After successful silence fill,if cumulative counter>=ring bytes,zeroes counter and stops slot0x5D0200. Counter is NOT reset on loop rewind,successful data reads or manual stop; repeated loop gaps can accumulate toward stop. Returns path-dependent pointer/mask/helper result,not service success. Callback acquires critical section; this body does not.
int *__cdecl rf_audio_stream_service_slot(int a1)
{
  int *result; // eax
  int v2; // [esp+0h] [ebp-10h]
  unsigned int v3; // [esp+4h] [ebp-Ch] BYREF
  int *v4; // [esp+8h] [ebp-8h]
  int *v5; // [esp+Ch] [ebp-4h]

  result = &unk_1E012F0[7 * a1];
  v5 = result;
  if ( (result[6] & 1) != 0 )
  {
    result = (int *)rf_audio_stream_bytes_played_since_write_cursor(a1);
    v4 = result;
    if ( result )
    {
      if ( *(_WORD *)unk_1951A1C[148 * *v5] == 2 )
        rf_audio_stream_fill_acm_converted_wave(a1, (int)v4, &v3);
      else
        rf_audio_stream_fill_pcm_from_wave_chunk(a1, (unsigned int)v4, &v3);
      result = (int *)(v5[6] & 4);
      if ( result )
      {
        v2 = (int)v4 - v3;
        v5[6] &= ~4u;
        if ( (v5[6] & 2) != 0 )
          rf_audio_stream_rewind_wave_data_chunk(a1);
        v5[5] += v2;
        result = (int *)rf_audio_stream_fill_silence_advance_cursor(a1, v2);
        if ( !result )
        {
          result = (int *)v5[5];
          if ( (unsigned int)result >= v5[2] )
          {
            v5[5] = 0;
            return rf_audio_stream_stop_slot(a1);
          }
        }
      }
    }
  }
  return result;
}

