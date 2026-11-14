// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CFF00 rf_audio_stream_fill_pcm_from_wave_chunk
// UNREALRED VERIFIED [audio-streaming-20261028]: Arguments stream slot,requested bytes,actual-read output. Uses source sample index+0 to592-byte sample record0x1951808; HMMIO+544,data MMCKINFO+548. Sets output0; locks DS buffer vtable+44 at logical write cursor+12 for requested bytes, obtaining up to2 spans. Reads each span through0x5EDD20, accumulates actual bytes. Success advances logical cursor by actual bytes modulo ring bytes+8; actual<requested sets flags+24 mask4. Read/lock error returns-1 and does not advance cursor; partial data/output count may already change. ALWAYS calls Unlock+76 even if Lock failed. Success0; unlock result ignored. No ring size, slot, requested-length or short-read padding validation; service routine handles silence separately.
int __cdecl rf_audio_stream_fill_pcm_from_wave_chunk(int a1, unsigned int a2, unsigned int *a3)
{
  int v4; // [esp+0h] [ebp-28h] BYREF
  int v5; // [esp+4h] [ebp-24h] BYREF
  int v6; // [esp+8h] [ebp-20h]
  HMMIO *v7; // [esp+Ch] [ebp-1Ch]
  int v8; // [esp+10h] [ebp-18h] BYREF
  int v9; // [esp+14h] [ebp-14h] BYREF
  int v10; // [esp+18h] [ebp-10h]
  int *v11; // [esp+1Ch] [ebp-Ch]
  int v12; // [esp+20h] [ebp-8h]
  int v13; // [esp+24h] [ebp-4h] BYREF

  v12 = 0;
  v11 = &unk_1E012F0[7 * a1];
  v7 = (HMMIO *)((char *)&unk_1951808 + 592 * *v11);
  v10 = unk_1BA1820[11 * v11[1]];
  *a3 = 0;
  v13 = 0;
  v8 = 0;
  v4 = 0;
  v9 = 0;
  v5 = 0;
  v6 = (*(int (__thiscall **)(int, int, int, unsigned int, int *, int *, int *, int *, _DWORD))(*(_DWORD *)v10 + 44))(
         v10,
         v10,
         v11[3],
         a2,
         &v8,
         &v9,
         &v4,
         &v5,
         0);
  if ( v6 < 0
    || v8 && rf_wave_mmio_read_data_chunk_bytes(v7[136], v9, v8, (int)(v7 + 137), (unsigned int *)&v13)
    || (*a3 += v13, v13 = 0, v4)
    && rf_wave_mmio_read_data_chunk_bytes(v7[136], v5, v4, (int)(v7 + 137), (unsigned int *)&v13) )
  {
    v12 = -1;
  }
  else
  {
    *a3 += v13;
    v11[3] = (*a3 + v11[3]) % v11[2];
    if ( *a3 < a2 )
      v11[6] |= 4u;
  }
  (*(void (__stdcall **)(int, int, int, int, int))(*(_DWORD *)v10 + 76))(v10, v8, v9, v4, v5);
  return v12;
}

