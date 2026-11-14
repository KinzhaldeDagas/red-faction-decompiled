// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00590B20 rf_dsound_fill_buffer_once_from_acm_wave
// UNREALRED VERIFIED [dsound-buffers-20261028]: Five arguments HMMIO,data chunk pointer,ACM handle,DS buffer,requested decoded bytes. Locks buffer offset0 into single output span; negative Lock HRESULT releases DS buffer andreturns-1 without clearing caller pointer. Queries encoded source bytes for locked size0x5ED820,reads shared scratch0x193BBE8 through0x5EDD20. Read error sets return-1 but may continue depending output count. If source bytes nonzero,converts directly into locked span0x5ED760; conversion failure returns-1 WITHOUT Unlock. If codec consumed fewer source bytes,seeks HMMIO backward by difference,ignores seek result. Normal path Unlock+76 ignored,returns accumulated0/-1. No invalid size-query result,source scratch-capacity,short decoded-tail silence fill or output-null validation. Uses shared scratch,requires external serialization.
int __cdecl rf_dsound_fill_buffer_once_from_acm_wave(HMMIO hmmio, int a2, HACMSTREAM has, int a4, int a5)
{
  DWORD v6; // [esp+0h] [ebp-20h]
  int v7; // [esp+4h] [ebp-1Ch] BYREF
  int v8; // [esp+8h] [ebp-18h] BYREF
  int v9; // [esp+Ch] [ebp-14h] BYREF
  int v10; // [esp+10h] [ebp-10h]
  DWORD cbInput; // [esp+14h] [ebp-Ch] BYREF
  int v12; // [esp+18h] [ebp-8h] BYREF
  int v13; // [esp+1Ch] [ebp-4h]

  v13 = 0;
  v10 = (*(int (__stdcall **)(int, _DWORD, int, int *, DWORD *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)a4 + 44))(
          a4,
          0,
          a5,
          &v12,
          &cbInput,
          0,
          0,
          0);
  if ( v10 < 0 )
  {
    (*(void (__thiscall **)(int, int))(*(_DWORD *)a4 + 8))(a4, a4);
    return -1;
  }
  else
  {
    v6 = rf_acm_stream_source_bytes_for_destination_size(has, cbInput);
    if ( rf_wave_mmio_read_data_chunk_bytes(hmmio, v6, (int)byte_193BBE8, a2, (unsigned int *)&v7) )
      v13 = -1;
    if ( v7 )
    {
      if ( rf_acm_stream_convert_buffer_once(has, byte_193BBE8, v7, (BYTE *)v12, cbInput, (DWORD *)&v9, (DWORD *)&v8) == -1 )
        return -1;
      if ( v8 < (unsigned int)v7 )
        mmioSeek(hmmio, v8 - v7, 1);
    }
    (*(void (__stdcall **)(int, int, DWORD, _DWORD, _DWORD))(*(_DWORD *)a4 + 76))(a4, v12, cbInput, 0, 0);
  }
  return v13;
}

