// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058FA70 rf_sound_sample_load_header_or_static_buffer
// UNREALRED VERIFIED [dsound-creation-20261028]: Calls0x590040; failure-1. Header-only byte EXACTLY1 returns0 with wave file/formats open. Otherwise source format tag1 delegates PCM static buffer0x58FB30; tag2 delegates ACM static buffer0x58FDD0; other tagsfail. Closes HMMIO after static branch,returns0 only if selected loader returned0. Does not free format allocations or static buffers on failure.
int __cdecl rf_sound_sample_load_header_or_static_buffer(int a1, char a2)
{
  int v3; // [esp+0h] [ebp-Ch]
  int v4; // [esp+8h] [ebp-4h]

  v4 = 0;
  if ( rf_sound_sample_open_wave_formats_and_data(a1) )
    return -1;
  if ( a2 == 1 )
    return 0;
  v3 = **((unsigned __int16 **)&unk_1951808 + 148 * a1 + 133);
  if ( v3 == 1 )
  {
    if ( !rf_dsound_create_static_pcm_sample_buffer(a1) )
      goto LABEL_12;
  }
  else if ( v3 == 2 && !rf_dsound_create_static_acm_decoded_sample_buffer(a1) )
  {
    goto LABEL_12;
  }
  v4 = -1;
LABEL_12:
  rf_wave_mmio_close_handle_pointer((HMMIO *)&unk_1951808 + 148 * a1 + 136);
  return v4;
}

