// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EDCC0 rf_wave_mmio_rewind_find_data_chunk
// UNREALRED VERIFIED [audio-streaming-20261028]: Arguments HMMIO pointer,data MMCKINFO,parent RIFF MMCKINFO. Seeks absolute parent.dwDataOffset+4,returns-1 on seek==-1. Sets data.ckid to FOURCC data (0x61746164),calls mmioDescend flags0x10 within parent; failure-1,success0. Descend refreshes chunk metadata used as remaining bytes. Does not preserve current file position or reset codec state.
int __cdecl rf_wave_mmio_rewind_find_data_chunk(HMMIO *a1, LPMMCKINFO pmmcki, MMCKINFO *pmmckiParent)
{
  if ( mmioSeek(*a1, pmmckiParent->dwDataOffset + 4, 0) == -1 )
    return -1;
  pmmcki->ckid = 1635017060;
  if ( mmioDescend(*a1, pmmcki, pmmckiParent, 0x10u) )
    return -1;
  else
    return 0;
}

