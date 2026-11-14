// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F7DD0 rf_model_geometry_load_lod_raw_block
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl(vfile,76-byte LOD,16-byte descriptor). ORs descriptor.flags intoLOD.flags64;copies descriptor+4 to68,batch countWORD8 toLOD12,rawByteSize12 toLOD0. Sets raw4/batches8=NULL,allocates raw size unchecked for validity,returns0 only if allocator returnsNULL. Reads entire raw block then sets batches8=raw4. Offset begins align16(56*batchCount). Reads extraDWORD toLOD72. Per56-byte batch reads sevenu16 to offsets40,42,44,46,52,50,48 thenu32 flags to0 (helper0x5CEC80);leaves raw32 unchanged. Fixes pointers sequentially to raw+offset:pos4 advances byteCount44,normal8 advances same44,UV12 advances48,triangles20 advances46;align16 after each. IfLODflag0x20,face planes16 advance16*triangleCount42. Duplicate indices24 advance52;optional field28 only set if byteCount50!=0,advances50. Clears batch36
// then ifflag1 assigns pointer36 and advances2*descriptor auxiliary count4. Every region aligned16;NO check against raw allocation size,overflow or existing stream error. Reads aux record count20,sets pointer16 to raw+offset if nonzero,accounts100bytes each. Reads texture count60;per texture reads BYTE tag intoLOD24+i,NULstring into512-byte stack(max511 stored chars),loads bitmap and writes handle32+4*i. No bounds on count:tags/handles can overwrite header fields,including count60 during iteration. Returns1 even prior read/load failures;raw-backed pointers are not separately allocated.
int __cdecl rf_model_geometry_load_lod_raw_block(int *a1, int a2, int a3)
{
  char byte_versioned; // al
  int v5; // eax
  int v6; // [esp+4h] [ebp-260h]
  int v7; // [esp+8h] [ebp-25Ch]
  int v8; // [esp+Ch] [ebp-258h]
  int v9; // [esp+10h] [ebp-254h]
  int v10; // [esp+14h] [ebp-250h]
  int v11; // [esp+18h] [ebp-24Ch]
  int v12; // [esp+1Ch] [ebp-248h]
  int v13; // [esp+20h] [ebp-244h]
  int v14; // [esp+24h] [ebp-240h]
  char v15[512]; // [esp+2Ch] [ebp-238h] BYREF
  int v16; // [esp+230h] [ebp-34h]
  __int16 v17; // [esp+234h] [ebp-30h]
  __int16 v18; // [esp+238h] [ebp-2Ch]
  int uint32_versioned; // [esp+23Ch] [ebp-28h]
  __int16 v20; // [esp+240h] [ebp-24h]
  int int32_versioned; // [esp+244h] [ebp-20h]
  int i; // [esp+248h] [ebp-1Ch]
  int v23; // [esp+24Ch] [ebp-18h]
  __int16 v24; // [esp+250h] [ebp-14h]
  __int16 uint16_versioned; // [esp+254h] [ebp-10h]
  __int16 v26; // [esp+258h] [ebp-Ch]
  int v27; // [esp+25Ch] [ebp-8h]
  __int16 v28; // [esp+260h] [ebp-4h]

  v27 = 0;
  *(_DWORD *)(a2 + 64) |= *(_DWORD *)a3;
  *(_DWORD *)(a2 + 68) = *(_DWORD *)(a3 + 4);
  *(_DWORD *)(a2 + 4) = 0;
  *(_DWORD *)(a2 + 8) = 0;
  *(_WORD *)(a2 + 12) = *(_WORD *)(a3 + 8);
  *(_DWORD *)a2 = *(_DWORD *)(a3 + 12);
  *(_DWORD *)(a2 + 4) = operator new(*(_DWORD *)a2);
  if ( !*(_DWORD *)(a2 + 4) )
    return 0;
  rf_vfile_read_buffered_bytes_versioned(a1, *(char **)(a2 + 4), *(_DWORD *)a2, 0, 0);
  v27 = 0;
  *(_DWORD *)(a2 + 8) = *(_DWORD *)(a2 + 4);
  v27 += 56 * *(unsigned __int16 *)(a2 + 12);
  if ( v27 % 16 )
    v14 = 16 - v27 % 16;
  else
    v14 = 0;
  v27 += v14;
  int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  *(_DWORD *)(a2 + 72) = int32_versioned;
  for ( i = 0; i < *(unsigned __int16 *)(a2 + 12); ++i )
  {
    uint16_versioned = rf_binary_stream_read_uint16_versioned(a1, 0, 0);
    v17 = rf_binary_stream_read_uint16_versioned(a1, 0, 0);
    v28 = rf_binary_stream_read_uint16_versioned(a1, 0, 0);
    v20 = rf_binary_stream_read_uint16_versioned(a1, 0, 0);
    v24 = rf_binary_stream_read_uint16_versioned(a1, 0, 0);
    v26 = rf_binary_stream_read_uint16_versioned(a1, 0, 0);
    v18 = rf_binary_stream_read_uint16_versioned(a1, 0, 0);
    uint32_versioned = rf_binary_stream_read_uint32_versioned(a1, 0, 0);
    *(_WORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 40) = uint16_versioned;
    *(_WORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 42) = v17;
    *(_WORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 44) = v28;
    *(_WORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 46) = v20;
    *(_WORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 52) = v24;
    *(_WORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 50) = v26;
    *(_WORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 48) = v18;
    rf_scene_key_set_first_dword((_DWORD *)(*(_DWORD *)(a2 + 8) + 56 * i), uint32_versioned);
    *(_DWORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 32) = *(_DWORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 32);
    *(_DWORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 4) = v27 + *(_DWORD *)(a2 + 4);
    v27 += *(unsigned __int16 *)(*(_DWORD *)(a2 + 8) + 56 * i + 44);
    if ( v27 % 16 )
      v13 = 16 - v27 % 16;
    else
      v13 = 0;
    v27 += v13;
    *(_DWORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 8) = v27 + *(_DWORD *)(a2 + 4);
    v27 += *(unsigned __int16 *)(*(_DWORD *)(a2 + 8) + 56 * i + 44);
    if ( v27 % 16 )
      v12 = 16 - v27 % 16;
    else
      v12 = 0;
    v27 += v12;
    *(_DWORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 12) = v27 + *(_DWORD *)(a2 + 4);
    v27 += *(unsigned __int16 *)(*(_DWORD *)(a2 + 8) + 56 * i + 48);
    if ( v27 % 16 )
      v11 = 16 - v27 % 16;
    else
      v11 = 0;
    v27 += v11;
    *(_DWORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 20) = v27 + *(_DWORD *)(a2 + 4);
    v27 += *(unsigned __int16 *)(*(_DWORD *)(a2 + 8) + 56 * i + 46);
    if ( v27 % 16 )
      v10 = 16 - v27 % 16;
    else
      v10 = 0;
    v27 += v10;
    if ( (*(_DWORD *)(a2 + 64) & 0x20) != 0 )
    {
      *(_DWORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 16) = v27 + *(_DWORD *)(a2 + 4);
      v16 = *(unsigned __int16 *)(*(_DWORD *)(a2 + 8) + 56 * i + 42);
      v27 += 16 * v16;
      if ( v27 % 16 )
        v9 = 16 - v27 % 16;
      else
        v9 = 0;
      v27 += v9;
    }
    *(_DWORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 24) = v27 + *(_DWORD *)(a2 + 4);
    v27 += *(unsigned __int16 *)(*(_DWORD *)(a2 + 8) + 56 * i + 52);
    if ( v27 % 16 )
      v8 = 16 - v27 % 16;
    else
      v8 = 0;
    v27 += v8;
    if ( *(_WORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 50) )
    {
      *(_DWORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 28) = v27 + *(_DWORD *)(a2 + 4);
      v27 += *(unsigned __int16 *)(*(_DWORD *)(a2 + 8) + 56 * i + 50);
      if ( v27 % 16 )
        v7 = 16 - v27 % 16;
      else
        v7 = 0;
      v27 += v7;
    }
    *(_DWORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 36) = 0;
    if ( (*(_DWORD *)(a2 + 64) & 1) != 0 )
    {
      *(_DWORD *)(*(_DWORD *)(a2 + 8) + 56 * i + 36) = v27 + *(_DWORD *)(a2 + 4);
      v27 += 2 * *(_DWORD *)(a3 + 4);
      if ( v27 % 16 )
        v6 = 16 - v27 % 16;
      else
        v6 = 0;
      v27 += v6;
    }
  }
  v23 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  *(_DWORD *)(a2 + 20) = v23;
  *(_DWORD *)(a2 + 16) = 0;
  if ( *(_DWORD *)(a2 + 20) )
  {
    *(_DWORD *)(a2 + 16) = v27 + *(_DWORD *)(a2 + 4);
    v27 += 100 * *(_DWORD *)(a2 + 20);
  }
  *(_DWORD *)(a2 + 60) = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  for ( i = 0; i < *(_DWORD *)(a2 + 60); ++i )
  {
    memset(v15, 0, sizeof(v15));
    byte_versioned = rf_binary_stream_read_byte_versioned(a1, 0, 0);
    *(_BYTE *)(i + a2 + 24) = byte_versioned;
    rf_binary_stream_read_nul_string_to_buffer(a1, v15, 511, 0, nullptr);
    v5 = rf_bitmap_load_with_optional_mipmap_generation(v15, (void *)0xFFFFFFFF, 1);
    *(_DWORD *)(a2 + 4 * i + 32) = v5;
  }
  return 1;
}

