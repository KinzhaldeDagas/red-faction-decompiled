// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00545590 rf_rfl_lightmaps_section_load
// UNREALRED VERIFIED [rfl-section-dispatch]: Loads section 0x1200 lightmaps.
int __cdecl rf_rfl_lightmaps_section_load(_DWORD *a1)
{
  int result; // eax
  int v2; // [esp+4h] [ebp-B0h]
  void *v3; // [esp+8h] [ebp-ACh]
  __int16 v4; // [esp+10h] [ebp-A4h]
  unsigned int v5; // [esp+14h] [ebp-A0h]
  unsigned int v6; // [esp+18h] [ebp-9Ch]
  int jj; // [esp+1Ch] [ebp-98h]
  int v8; // [esp+20h] [ebp-94h]
  int ii; // [esp+24h] [ebp-90h]
  unsigned int v10; // [esp+28h] [ebp-8Ch]
  int v11; // [esp+2Ch] [ebp-88h]
  unsigned int v12; // [esp+30h] [ebp-84h]
  unsigned int v13; // [esp+34h] [ebp-80h]
  unsigned int v14; // [esp+38h] [ebp-7Ch]
  int n; // [esp+3Ch] [ebp-78h]
  int v16; // [esp+40h] [ebp-74h]
  int m; // [esp+44h] [ebp-70h]
  int v18; // [esp+48h] [ebp-6Ch]
  unsigned __int16 v19; // [esp+58h] [ebp-5Ch]
  int k; // [esp+5Ch] [ebp-58h]
  int v21; // [esp+60h] [ebp-54h]
  int j; // [esp+64h] [ebp-50h]
  int v23; // [esp+68h] [ebp-4Ch]
  int v24; // [esp+6Ch] [ebp-48h]
  char *Block; // [esp+70h] [ebp-44h]
  int int32_versioned; // [esp+74h] [ebp-40h]
  unsigned int v27[8]; // [esp+78h] [ebp-3Ch] BYREF
  int v28; // [esp+98h] [ebp-1Ch]
  int v29; // [esp+9Ch] [ebp-18h]
  int i; // [esp+A0h] [ebp-14h]
  int v31; // [esp+A4h] [ebp-10h]
  int v32; // [esp+B0h] [ebp-4h]

  result = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  v31 = result;
  for ( i = 0; i < v31; ++i )
  {
    int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    v29 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    v3 = operator new(0x18u);
    v32 = 0;
    if ( v3 )
      v2 = rf_lightmap_atlas_page24_construct_register((int)v3, int32_versioned, v29, 0, 0);
    else
      v2 = 0;
    v32 = -1;
    v28 = v2;
    if ( rf_vfile_get_slot_version(a1) >= 128 )
    {
      rf_vfile_read_buffered_bytes_versioned(a1, *(char **)(v28 + 12), 3 * v29 * int32_versioned, 0, 0);
    }
    else
    {
      Block = (char *)malloc(2 * v29 * int32_versioned);
      rf_vfile_read_buffered_bytes_versioned(a1, Block, 2 * v29 * int32_versioned, 0, 0);
      v23 = 0;
      v24 = 0;
      for ( j = 0; j < v29; ++j )
      {
        v21 = 0;
        for ( k = 0; k < int32_versioned; ++k )
        {
          v19 = *(_WORD *)&Block[2 * k + 2 * v24];
          *(_BYTE *)(v21 + v23 + *(_DWORD *)(v28 + 12)) = (8 * (((int)v19 >> 10) & 0x1F)) | 7;
          *(_BYTE *)(v21 + v23 + *(_DWORD *)(v28 + 12) + 1) = (8 * (((int)v19 >> 5) & 0x1F)) | 7;
          *(_BYTE *)(v21 + v23 + *(_DWORD *)(v28 + 12) + 2) = (8 * (v19 & 0x1F)) | 7;
          v21 += 3;
        }
        v23 += 3 * int32_versioned;
        v24 += int32_versioned;
      }
      free(Block);
    }
    if ( !rf_renderer_texture_mode_supported_dispatch((int)&unk_187CD28) )
    {
      v18 = 0;
      for ( m = 0; m < v29; ++m )
      {
        v16 = 0;
        for ( n = 0; n < int32_versioned; ++n )
        {
          v12 = (2 * *(unsigned __int8 *)(*(_DWORD *)(v28 + 12) + v16 + v18)) | 1;
          v13 = (2 * *(unsigned __int8 *)(*(_DWORD *)(v28 + 12) + v16 + v18 + 1)) | 1;
          v14 = (2 * *(unsigned __int8 *)(*(_DWORD *)(v28 + 12) + v16 + v18 + 2)) | 1;
          if ( v12 > 0xFF )
            LOBYTE(v12) = -1;
          if ( v13 > 0xFF )
            LOBYTE(v13) = -1;
          if ( v14 > 0xFF )
            LOBYTE(v14) = -1;
          *(_BYTE *)(v16 + v18 + *(_DWORD *)(v28 + 12)) = v12;
          *(_BYTE *)(v16 + v18 + *(_DWORD *)(v28 + 12) + 1) = v13;
          *(_BYTE *)(v16 + v18 + *(_DWORD *)(v28 + 12) + 2) = v14;
          v16 += 3;
        }
        v18 += 3 * int32_versioned;
      }
    }
    if ( rf_bitmap_lock_pixels_backend_dispatch(*(_DWORD *)(v28 + 16), 0, (int)v27, 2) )
    {
      v11 = 0;
      v10 = v27[3];
      for ( ii = 0; ii < v29; ++ii )
      {
        v8 = 0;
        for ( jj = 0; jj < int32_versioned; ++jj )
        {
          v5 = *(unsigned __int8 *)(*(_DWORD *)(v28 + 12) + v8 + v11 + 1) >> 3;
          v6 = *(unsigned __int8 *)(*(_DWORD *)(v28 + 12) + v8 + v11 + 2) >> 3;
          v4 = rf_uint32_maximum_two_values(*(unsigned __int8 *)(*(_DWORD *)(v28 + 12) + v8 + v11) >> 3, 4u);
          LOWORD(v5) = rf_uint32_maximum_two_values(v5, 4u);
          *(_WORD *)(v10 + 2 * jj) = rf_uint32_maximum_two_values(v6, 4u) | (32 * v5) | (v4 << 10) | 0x8000;
          v8 += 3;
        }
        v11 += 3 * int32_versioned;
        v10 += 2 * ((signed int)v27[6] / 2);
      }
      rf_bitmap_unlock_pixels_backend_dispatch(v27);
    }
    result = i + 1;
  }
  return result;
}

