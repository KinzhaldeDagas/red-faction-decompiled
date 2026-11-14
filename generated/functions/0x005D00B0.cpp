// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D00B0 rf_audio_stream_fill_silence_advance_cursor
// UNREALRED VERIFIED [audio-streaming-20261028]: Arguments stream slot,byte count. Silence byte0 when sample output WAVEFORMAT bits-per-sample at+14==16,else0x80 (including other unvalidated formats). Locks DS buffer at current logical write cursor into up to2 spans. Lock failure-1 without unlock. Success memset spans, advances cursor by locked span sizes modulo ring bytes, unlocks ignoring result, returns0. Does not update EOF/drain flags or validate count/capacity.
int __cdecl rf_audio_stream_fill_silence_advance_cursor(int a1, int a2)
{
  void *v3; // [esp+0h] [ebp-24h] BYREF
  size_t v4; // [esp+4h] [ebp-20h]
  size_t v5; // [esp+8h] [ebp-1Ch] BYREF
  int v6; // [esp+Ch] [ebp-18h]
  void *v7; // [esp+10h] [ebp-14h] BYREF
  size_t Size; // [esp+14h] [ebp-10h] BYREF
  size_t v9; // [esp+18h] [ebp-Ch]
  int *v10; // [esp+1Ch] [ebp-8h]
  unsigned __int8 v11; // [esp+23h] [ebp-1h]

  v7 = nullptr;
  v3 = nullptr;
  Size = 0;
  v5 = 0;
  v10 = &unk_1E012F0[7 * a1];
  v11 = 0x80;
  if ( *(_WORD *)(unk_1951A20[148 * *v10] + 14) == 16 )
    v11 = 0;
  v6 = (*(int (__stdcall **)(int, int, int, void **, size_t *, void **, size_t *, _DWORD))(*(_DWORD *)unk_1BA1820[11 * v10[1]]
                                                                                         + 44))(
         unk_1BA1820[11 * v10[1]],
         v10[3],
         a2,
         &v7,
         &Size,
         &v3,
         &v5,
         0);
  if ( v6 < 0 )
    return -1;
  v9 = 0;
  memset(v7, v11, Size);
  v4 = Size;
  if ( v3 )
  {
    memset(v3, v11, v5);
    v9 = v5;
  }
  v10[3] = (v9 + v4 + v10[3]) % v10[2];
  (*(void (__stdcall **)(int, void *, size_t, void *, size_t))(*(_DWORD *)unk_1BA1820[11 * v10[1]] + 76))(
    unk_1BA1820[11 * v10[1]],
    v7,
    Size,
    v3,
    v5);
  return 0;
}

