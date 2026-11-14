// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00590960 rf_dsound_create_prime_streaming_buffer_slot
// UNREALRED VERIFIED [dsound-creation-20261028]: Arguments sample index,backend slot. Creates DS buffer through device0x1951804 with flags232,size2*output format avgBytesPerSec,format pointer+536. Requires nonnegative result andnonnull pointer. Rewinds source data chunk but ignores result. Source tag2 opens ACM handle into sample+540 andfills via0x590B20; all other tags raw fill0x58FC70. Returns0 only if setup/fill succeeds; failures-1 without consistent buffer/ACM cleanup or pointer nulling. Codec handle can overwrite previous sample handle without close. No slot/sample bounds or ring-length validation; buffer not played here.
int __cdecl rf_dsound_create_prime_streaming_buffer_slot(int a1, int a2)
{
  int *v3; // [esp+0h] [ebp-38h]
  _DWORD v4[2]; // [esp+8h] [ebp-30h] BYREF
  int v5; // [esp+10h] [ebp-28h]
  int v6; // [esp+14h] [ebp-24h]
  int v7; // [esp+18h] [ebp-20h]
  int v8; // [esp+1Ch] [ebp-1Ch]
  int v9; // [esp+20h] [ebp-18h]
  int v10; // [esp+24h] [ebp-14h]
  int v11; // [esp+28h] [ebp-10h]
  char *v12; // [esp+30h] [ebp-8h]
  int v13; // [esp+34h] [ebp-4h]

  v13 = 0;
  v12 = (char *)&unk_1951808 + 592 * a1;
  v3 = &unk_1BA1820[11 * a2];
  v5 = 0;
  v6 = 0;
  v7 = 0;
  v8 = 0;
  v9 = 0;
  v10 = 0;
  v11 = 0;
  v4[0] = 36;
  v4[1] = 232;
  v5 = 2 * *(_DWORD *)(*((_DWORD *)v12 + 134) + 8);
  v7 = *((_DWORD *)v12 + 134);
  if ( (*(int (__stdcall **)(int, _DWORD *, int *, _DWORD))(*(_DWORD *)dword_1951670[101] + 12))(
         dword_1951670[101],
         v4,
         v3,
         0) < 0
    || !*v3 )
  {
    return -1;
  }
  rf_wave_mmio_rewind_find_data_chunk((HMMIO *)v12 + 136, (LPMMCKINFO)(v12 + 548), (MMCKINFO *)(v12 + 568));
  if ( **((_WORD **)v12 + 133) == 2 )
  {
    if ( rf_acm_open_source_to_pcm_stream(
           *((LPWAVEFORMATEX *)v12 + 133),
           *((LPWAVEFORMATEX *)v12 + 134),
           (LPHACMSTREAM)v12 + 135,
           *(_WORD *)(*((_DWORD *)v12 + 134) + 14)) )
    {
      return -1;
    }
    else if ( rf_dsound_fill_buffer_once_from_acm_wave(
                *((HMMIO *)v12 + 136),
                (int)(v12 + 548),
                *((HACMSTREAM *)v12 + 135),
                *v3,
                v5) )
    {
      return -1;
    }
  }
  else if ( rf_dsound_fill_pcm_buffer_from_wave_chunk(*((HMMIO *)v12 + 136), (int)(v12 + 548), *v3, v5) )
  {
    return -1;
  }
  return v13;
}

