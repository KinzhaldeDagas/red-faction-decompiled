// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058FC70 rf_dsound_fill_pcm_buffer_from_wave_chunk
// UNREALRED VERIFIED [dsound-creation-20261028]: Arguments HMMIO,data chunk,DS buffer,byte count. Locks offset0 for requested bytes with only first region outputs. Lock failure releases DS buffer andreturns-1,leaving caller-owned pointer stale. Else reads through0x5EDD20; failure return-1,success0; ignores actual byte count and always unlocks requested locked region. No short-read silence padding,second wrapped region,output format or buffer-lost retry handling; Unlock result ignored.
int __cdecl rf_dsound_fill_pcm_buffer_from_wave_chunk(HMMIO hmmio, int a2, int a3, int a4)
{
  int v5; // [esp+0h] [ebp-14h] BYREF
  int v6; // [esp+4h] [ebp-10h]
  int v7; // [esp+8h] [ebp-Ch] BYREF
  int v8; // [esp+Ch] [ebp-8h] BYREF
  int v9; // [esp+10h] [ebp-4h]

  v9 = 0;
  v6 = (*(int (__stdcall **)(int, _DWORD, int, int *, int *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)a3 + 44))(
         a3,
         0,
         a4,
         &v8,
         &v7,
         0,
         0,
         0);
  if ( v6 < 0 )
  {
    (*(void (__stdcall **)(int))(*(_DWORD *)a3 + 8))(a3);
    return -1;
  }
  else
  {
    if ( rf_wave_mmio_read_data_chunk_bytes(hmmio, v7, v8, a2, (unsigned int *)&v5) )
      v9 = -1;
    (*(void (__thiscall **)(int, int, int, int, _DWORD, _DWORD))(*(_DWORD *)a3 + 76))(a3, a3, v8, v7, 0, 0);
  }
  return v9;
}

