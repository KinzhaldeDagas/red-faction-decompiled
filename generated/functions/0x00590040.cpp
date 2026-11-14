// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00590040 rf_sound_sample_open_wave_formats_and_data
// UNREALRED VERIFIED [dsound-creation-20261028]: Requires initialized0x1BA1810 and sample index>=0,else-1. Opens record filepath+256,offset+512 through0x5ED990 into HMMIO+544,source format+532,output PCM format+536,parent RIFF chunk+568; then rewinds/finds data chunk+548 via0x5EDCC0. Both success0; failure closes HMMIO andreturns-1. If data-chunk lookup fails after format allocation,format buffers remain allocated for later cleanup. No index upper bound,old format release or source pointer initialization here.
int __cdecl rf_sound_sample_open_wave_formats_and_data(int a1)
{
  char *v2; // [esp+0h] [ebp-4h]

  if ( !unk_1BA1810 )
    return -1;
  if ( a1 < 0 )
    return -1;
  v2 = (char *)&unk_1951808 + 592 * a1;
  if ( !rf_wave_mmio_open_read_source_and_pcm_formats(
          v2 + 256,
          *((_DWORD *)v2 + 128),
          (HMMIO *)v2 + 136,
          (void **)v2 + 133,
          (void **)v2 + 134,
          (LPMMCKINFO)(v2 + 568))
    && !rf_wave_mmio_rewind_find_data_chunk((HMMIO *)v2 + 136, (LPMMCKINFO)(v2 + 548), (MMCKINFO *)(v2 + 568)) )
  {
    return 0;
  }
  rf_wave_mmio_close_handle_pointer((HMMIO *)v2 + 136);
  return -1;
}

