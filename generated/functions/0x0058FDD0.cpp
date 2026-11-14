// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058FDD0 rf_dsound_create_static_acm_decoded_sample_buffer
// UNREALRED VERIFIED [dsound-creation-20261028]: Argument sample index. Allocates encoded chunk-size bytes,reads wave source into block,opens local ACM stream to16-bit PCM. Uses DECLARED chunk size for destination-size query/conversion,not actual bytes read. Creates static DS buffer with decoded-size query result and flags393456/234,locks entire buffer,and converts. Success unlocks,closes local ACM stream,frees block,returns0. Failure frees block andcloses nonnull ACM stream,returns-1; conversion/Lock failure releases DS buffer WITHOUT nulling sample pointer; conversion failure does not Unlock before release. Create success pointer not independently checked. Ignores used destination bytes and leaves unwritten tail; no failed-size-query,length/allocation overflow or source-format validation. Does not obtain3D interface in this routine.
int __cdecl rf_dsound_create_static_acm_decoded_sample_buffer(int a1)
{
  int v2; // [esp+0h] [ebp-6Ch] BYREF
  int v3; // [esp+4h] [ebp-68h]
  size_t Size; // [esp+8h] [ebp-64h]
  HACMSTREAM has; // [esp+Ch] [ebp-60h] BYREF
  int v6; // [esp+10h] [ebp-5Ch] BYREF
  int v7; // [esp+14h] [ebp-58h]
  int v8; // [esp+18h] [ebp-54h]
  int v9; // [esp+1Ch] [ebp-50h]
  struct tWAVEFORMATEX *p_pwfxDst; // [esp+20h] [ebp-4Ch]
  int v11; // [esp+24h] [ebp-48h]
  int v12; // [esp+28h] [ebp-44h]
  int v13; // [esp+2Ch] [ebp-40h]
  int v14; // [esp+30h] [ebp-3Ch]
  int v15; // [esp+38h] [ebp-34h] BYREF
  int v16; // [esp+3Ch] [ebp-30h] BYREF
  struct tWAVEFORMATEX pwfxDst; // [esp+40h] [ebp-2Ch] BYREF
  void *Block; // [esp+54h] [ebp-18h]
  int v19; // [esp+58h] [ebp-14h]
  int v20; // [esp+5Ch] [ebp-10h] BYREF
  char *v21; // [esp+60h] [ebp-Ch]
  int v22; // [esp+64h] [ebp-8h]
  int v23; // [esp+68h] [ebp-4h] BYREF

  v22 = 0;
  has = nullptr;
  v21 = (char *)&unk_1951808 + 592 * a1;
  Block = nullptr;
  Size = *((_DWORD *)v21 + 138);
  Block = malloc(Size);
  if ( Block
    && !rf_wave_mmio_read_data_chunk_bytes(
          *((HMMIO *)v21 + 136),
          Size,
          (int)Block,
          (int)(v21 + 548),
          (unsigned int *)&v23)
    && !rf_acm_open_source_to_pcm_stream(*((LPWAVEFORMATEX *)v21 + 133), &pwfxDst, &has, 0x10u) )
  {
    v19 = rf_acm_stream_destination_bytes_for_source_size(has, Size);
    v7 = 0;
    v8 = 0;
    v9 = 0;
    p_pwfxDst = nullptr;
    v11 = 0;
    v12 = 0;
    v13 = 0;
    v14 = 0;
    v6 = 36;
    v7 = unk_193BBE0 == 1 ? 393456 : 234;
    v8 = v19;
    p_pwfxDst = &pwfxDst;
    v3 = (*(int (__stdcall **)(int, int *, char *, _DWORD))(*(_DWORD *)dword_1951670[101] + 12))(
           dword_1951670[101],
           &v6,
           v21 + 524,
           0);
    if ( v3 >= 0 )
    {
      v3 = (*(int (__stdcall **)(_DWORD, _DWORD, int, int *, int *, _DWORD, _DWORD, _DWORD))(**((_DWORD **)v21 + 131)
                                                                                           + 44))(
             *((_DWORD *)v21 + 131),
             0,
             v19,
             &v20,
             &v15,
             0,
             0,
             0);
      if ( v3 >= 0 )
      {
        if ( !rf_acm_stream_convert_buffer_once(has, (BYTE *)Block, Size, (BYTE *)v20, v19, (DWORD *)&v2, (DWORD *)&v16) )
        {
          (*(void (__stdcall **)(_DWORD, int, int, _DWORD, _DWORD))(**((_DWORD **)v21 + 131) + 76))(
            *((_DWORD *)v21 + 131),
            v20,
            v15,
            0,
            0);
          rf_acm_close_stream(has);
          has = nullptr;
          goto LABEL_14;
        }
        (*(void (__stdcall **)(_DWORD))(**((_DWORD **)v21 + 131) + 8))(*((_DWORD *)v21 + 131));
      }
      else
      {
        (*(void (__stdcall **)(_DWORD))(**((_DWORD **)v21 + 131) + 8))(*((_DWORD *)v21 + 131));
      }
    }
  }
  v22 = -1;
LABEL_14:
  if ( Block )
    free(Block);
  if ( has )
    rf_acm_close_stream(has);
  return v22;
}

