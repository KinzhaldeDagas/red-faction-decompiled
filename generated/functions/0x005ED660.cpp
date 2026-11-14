// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ED660 rf_acm_open_source_to_pcm_stream
// UNREALRED VERIFIED [wave-codec-20261028]: Arguments source WAVEFORMATEX,destination WAVEFORMATEX,output ACM handle,requested bits-per-sample WORD. Initializes driver0x5ED880 only if global ready0. Writes destination PCM tag1,source channels/sample rate,requested bits,cbSize0,blockAlign=bits*channels/8,avgBytesPerSec=sampleRate*blockAlign. Calls acmStreamOpen with selected driver0x1F67100,callback0,instance0,flags4. API error-1,success0. No bitdepth/channel/rate/product validation or output-handle clearing on failure; caller owns source/destination storage and stream lifetime.
int __cdecl rf_acm_open_source_to_pcm_stream(
        LPWAVEFORMATEX pwfxSrc,
        LPWAVEFORMATEX pwfxDst,
        LPHACMSTREAM phas,
        WORD a4)
{
  if ( !unk_1F6710C && rf_acm_initialize_ms_adpcm_driver() )
    return -1;
  pwfxDst->wFormatTag = 1;
  pwfxDst->nChannels = pwfxSrc->nChannels;
  pwfxDst->nSamplesPerSec = pwfxSrc->nSamplesPerSec;
  pwfxDst->wBitsPerSample = a4;
  pwfxDst->cbSize = 0;
  pwfxDst->nBlockAlign = pwfxDst->wBitsPerSample * pwfxDst->nChannels / 8;
  pwfxDst->nAvgBytesPerSec = pwfxDst->nSamplesPerSec * pwfxDst->nBlockAlign;
  if ( acmStreamOpen(phas, *(HACMDRIVER *)&byte_1F670FC[4], pwfxSrc, pwfxDst, nullptr, 0, 0, 4u) )
    return -1;
  else
    return 0;
}

