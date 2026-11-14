// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D02E0 rf_audio_stream_fill_acm_converted_wave
// UNREALRED VERIFIED [audio-streaming-20261028]: Arguments stream slot,requested decoded bytes,actual decoded output. Initializes output0,locks DS buffer at logical write cursor into2 spans. Uses ACM stream sample+540,queries compressed bytes for locked destination bytes0x5ED820; nonpositive/error fails. Reads compressed source into shared buffer0x193BBE8 with0x5EDD20. Source0 bytes sets EOF mask4; otherwise converts to shared180000-byte buffer0x1DD53D0 through0x5ED760. If consumed source less than read,seeks HMMIO backward by difference,ignores seek result. Copies converted destination bytes into first DS span then second; NO check that converted length<=combined locked spans or that queried source bytes fit shared source buffer. Advances logical cursor by copied bytes modulo ring size. EOF mask4 is set only on zero source read,not any short decode. Failure-1,success0; ALWAYS calls DS
// Unlock even on Lock failure,ignores result. Global scratch makes routine nonreentrant absent external synchronization.
int __cdecl rf_audio_stream_fill_acm_converted_wave(int a1, int a2, _DWORD *a3)
{
  int v4; // [esp+0h] [ebp-3Ch] BYREF
  size_t v5; // [esp+4h] [ebp-38h]
  size_t v6; // [esp+8h] [ebp-34h] BYREF
  size_t v7; // [esp+Ch] [ebp-30h]
  void *v8; // [esp+10h] [ebp-2Ch] BYREF
  int v9; // [esp+14h] [ebp-28h] BYREF
  int v10; // [esp+18h] [ebp-24h]
  char *v11; // [esp+1Ch] [ebp-20h]
  void *v12; // [esp+20h] [ebp-1Ch] BYREF
  size_t Size; // [esp+24h] [ebp-18h] BYREF
  int v14; // [esp+28h] [ebp-14h]
  int v15; // [esp+2Ch] [ebp-10h]
  int *v16; // [esp+30h] [ebp-Ch]
  int v17; // [esp+34h] [ebp-8h]
  int v18; // [esp+38h] [ebp-4h] BYREF

  v17 = 0;
  v16 = &unk_1E012F0[7 * a1];
  v11 = (char *)&unk_1951808 + 592 * *v16;
  v14 = unk_1BA1820[11 * v16[1]];
  *a3 = 0;
  v18 = 0;
  v12 = nullptr;
  v8 = nullptr;
  Size = 0;
  v9 = 0;
  v10 = (*(int (__thiscall **)(int, int, int, int, void **, size_t *, void **, int *, _DWORD))(*(_DWORD *)v14 + 44))(
          v14,
          v14,
          v16[3],
          a2,
          &v12,
          &Size,
          &v8,
          &v9,
          0);
  if ( v10 < 0 )
    goto LABEL_14;
  v15 = rf_acm_stream_source_bytes_for_destination_size(*((HACMSTREAM *)v11 + 135), v9 + Size);
  if ( v15 <= 0
    || rf_wave_mmio_read_data_chunk_bytes(
         *((HMMIO *)v11 + 136),
         v15,
         (int)byte_193BBE8,
         (int)(v11 + 548),
         (unsigned int *)&v18) )
  {
    goto LABEL_14;
  }
  if ( v18 )
  {
    v5 = 0;
    v7 = 0;
    if ( rf_acm_stream_convert_buffer_once(
           *((HACMSTREAM *)v11 + 135),
           byte_193BBE8,
           v18,
           byte_1DD53D0,
           0x2BF20u,
           &v6,
           (DWORD *)&v4) != -1 )
    {
      if ( v4 < (unsigned int)v18 )
        mmioSeek(*((HMMIO *)v11 + 136), v4 - v18, 1);
      if ( v6 <= Size )
      {
        v5 = v6;
        v7 = 0;
        memcpy(v12, byte_1DD53D0, v6);
      }
      else
      {
        v5 = Size;
        v7 = v6 - Size;
        memcpy(v12, byte_1DD53D0, Size);
        memcpy(v8, &byte_1DD53D0[Size], v6 - Size);
      }
      *a3 += v6;
      goto LABEL_13;
    }
LABEL_14:
    v17 = -1;
    goto LABEL_15;
  }
  v16[6] |= 4u;
LABEL_13:
  v16[3] = (*a3 + v16[3]) % (unsigned int)v16[2];
LABEL_15:
  (*(void (__thiscall **)(int, int, void *, size_t, void *, int))(*(_DWORD *)v14 + 76))(v14, v14, v12, Size, v8, v9);
  return v17;
}

