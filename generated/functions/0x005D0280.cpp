// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D0280 rf_audio_stream_rewind_wave_data_chunk
// UNREALRED VERIFIED [audio-streaming-20261028]: Slot selects sample record; calls0x5EDCC0(address HMMIO+544,data chunk+548,parent chunk+568). Returns-1 for callee nonzero,else0. Repositions file/data chunk only; does not reset ACM codec,DS cursor,EOF flags or drain counter.
int __cdecl rf_audio_stream_rewind_wave_data_chunk(int a1)
{
  char *v2; // [esp+0h] [ebp-8h]

  v2 = (char *)&unk_1951808 + 592 * unk_1E012F0[7 * a1];
  if ( rf_wave_mmio_rewind_find_data_chunk((HMMIO *)v2 + 136, (LPMMCKINFO)(v2 + 548), (MMCKINFO *)(v2 + 568)) )
    return -1;
  else
    return 0;
}

