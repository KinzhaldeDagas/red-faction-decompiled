// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E03F0 rf_tga_read_pixels_palette
// UNREALRED VERIFIED [bitmap-decoders-20261028]: Arguments filename,output pixels,output palette,unused mode,source context. Opens supplied name/context, then .tga fallback with same context and finally default source; fatal if all fail. Reads TGA header, stores open slot in global0x664A54. Accepts bitdepth8/16/24/32, attribute nibble0/1/8 and image types1/2/3/9/10/11. Nonzero image ID length is passed to ABSOLUTE seek(length,0), not relative skip from header end. If color-map flag nonzero, reads map entries as3-byte BGR into RGB palette and zero-fills through256; ignores palette origin and declared entry bitdepth, no palette pointer/count<=256 check. Reads entire remaining file into allocated block. Types1/2 copy raw rows;9/10 decode packet RLE per row via0x5E02C0, whose packets may exceed row width. Types3/11 pass validation but have NO pixel-write branch and still return0 success.
// Vertical descriptor bit0x20 selects row order; horizontal bit0x10 is read/stored locally but never applied. Does not convert16-bit alpha convention or use requested extra mode argument. Frees temporary and closes vfile, returns0 after accepted path,1 for validation/header-status rejection. No destination capacity, payload length, signed-positive dimensions, allocation or post-payload-read status checks.
int __cdecl rf_tga_read_pixels_palette(char *Str, int a2, int a3, int a4, char *a5)
{
  int v6; // esi
  unsigned __int8 *v7; // eax
  int k; // [esp+30h] [ebp-374h]
  void *v9; // [esp+34h] [ebp-370h] BYREF
  int j; // [esp+38h] [ebp-36Ch]
  int i; // [esp+3Ch] [ebp-368h]
  char Buffer[256]; // [esp+40h] [ebp-364h] BYREF
  char v13[260]; // [esp+140h] [ebp-264h] BYREF
  unsigned __int8 char8_versioned; // [esp+244h] [ebp-160h]
  char v15; // [esp+245h] [ebp-15Fh]
  char v16; // [esp+246h] [ebp-15Eh]
  __int16 int16_versioned; // [esp+248h] [ebp-15Ch]
  __int16 v18; // [esp+24Ah] [ebp-15Ah]
  char v19; // [esp+24Ch] [ebp-158h]
  __int16 v20; // [esp+24Eh] [ebp-156h]
  __int16 v21; // [esp+250h] [ebp-154h]
  __int16 v22; // [esp+252h] [ebp-152h]
  __int16 v23; // [esp+254h] [ebp-150h]
  unsigned __int8 v24; // [esp+256h] [ebp-14Eh]
  char v25; // [esp+257h] [ebp-14Dh]
  BOOL v26; // [esp+258h] [ebp-14Ch]
  int v27; // [esp+25Ch] [ebp-148h] BYREF
  char v28; // [esp+263h] [ebp-141h]
  size_t Size; // [esp+264h] [ebp-140h]
  int self[73]; // [esp+268h] [ebp-13Ch] BYREF
  void *v31; // [esp+38Ch] [ebp-18h]
  size_t v32; // [esp+390h] [ebp-14h]
  size_t v33; // [esp+394h] [ebp-10h]
  int v34; // [esp+3A0h] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v34 = 0;
  if ( rf_vfile_open_with_extension_cache_control_paths(self, Str, 1, a5) < 0 )
  {
    rf_path_replace_last_dot_suffix_unbounded(v13, Str, ".tga");
    if ( rf_vfile_open_with_extension_cache_control_paths(self, v13, 1, a5) < 0
      && rf_vfile_open_with_extension_cache_control_paths(self, v13, 1, byte_98967F) < 0 )
    {
      sprintf(Buffer, "Could not open file: %s", v13);
      rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\bmpman\\targautils.cpp", 620, Buffer);
    }
  }
  dword_664A54 = self[0];
  char8_versioned = rf_binary_stream_read_char8_versioned(self, 0, 0);
  v15 = rf_binary_stream_read_char8_versioned(self, 0, 0);
  v16 = rf_binary_stream_read_char8_versioned(self, 0, 0);
  int16_versioned = rf_binary_stream_read_int16_versioned(self, 0, 0);
  v18 = rf_binary_stream_read_int16_versioned(self, 0, 0);
  v19 = rf_binary_stream_read_char8_versioned(self, 0, 0);
  v20 = rf_binary_stream_read_int16_versioned(self, 0, 0);
  v21 = rf_binary_stream_read_int16_versioned(self, 0, 0);
  v22 = rf_binary_stream_read_int16_versioned(self, 0, 0);
  v23 = rf_binary_stream_read_int16_versioned(self, 0, 0);
  v24 = rf_binary_stream_read_char8_versioned(self, 0, 0);
  v25 = rf_binary_stream_read_char8_versioned(self, 0, 0);
  self[72] = (v25 & 0x10) != 0;
  v26 = (v25 & 0x20) != 0;
  if ( !rf_vfile_get_open_slot_status(self)
    && (v24 == 8 || v24 == 24 || v24 == 32 || v24 == 16)
    && ((v28 = v25 & 0xF, (v25 & 0xF) == 8) || !v28 || v28 == 1)
    && (v16 == 1 || v16 == 2 || v16 == 3 || v16 == 9 || v16 == 10 || v16 == 11)
    && (!char8_versioned || rf_vfile_seek(self, char8_versioned, 0) >= 0) )
  {
    if ( v15 )
    {
      for ( i = 0; i < v18; ++i )
      {
        *(_BYTE *)(a3 + 3 * i + 2) = rf_binary_stream_read_byte_versioned(self, 0, 0);
        *(_BYTE *)(a3 + 3 * i + 1) = rf_binary_stream_read_byte_versioned(self, 0, 0);
        *(_BYTE *)(a3 + 3 * i) = rf_binary_stream_read_byte_versioned(self, 0, 0);
      }
      while ( i < 256 )
      {
        *(_BYTE *)(a3 + 3 * i + 2) = 0;
        *(_BYTE *)(a3 + 3 * i + 1) = 0;
        *(_BYTE *)(a3 + 3 * i++) = 0;
      }
    }
    v6 = rf_vfile_get_size((int)self, nullptr, (int)byte_98967F);
    Size = v6 - rf_vfile_get_open_slot_offset(self);
    v31 = operator new(Size);
    v27 = (int)v31;
    rf_vfile_read_buffered_bytes_versioned(self, (char *)v31, Size, 0, 0);
    v33 = (int)v24 >> 3;
    v32 = v33 * v22;
    if ( v16 == 1 || v16 == 2 )
    {
      for ( j = 0; j < v23; ++j )
      {
        if ( (v25 & 0x20) != 0 )
          v9 = (void *)(a2 + v32 * j);
        else
          v9 = (void *)(a2 + v32 * (v23 - j - 1));
        rf_pixel_copy_run_advance_source_destination(v22, &v9, (const void **)&v27, v33);
      }
    }
    else if ( v16 == 9 || v16 == 10 )
    {
      for ( k = 0; k < v23; ++k )
      {
        if ( (v25 & 0x20) != 0 )
          v7 = rf_vani_decode_pixel_packets_rle((void *)(a2 + v32 * k), (unsigned __int8 *)v27, v22, v33);
        else
          v7 = rf_vani_decode_pixel_packets_rle((void *)(a2 + v32 * (v23 - k - 1)), (unsigned __int8 *)v27, v22, v33);
        v27 += (int)v7;
      }
    }
    operator delete(v31);
    rf_vfile_close_stdio_or_vpp(self);
    v34 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 0;
  }
  else
  {
    rf_vfile_close_stdio_or_vpp(self);
    v34 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 1;
  }
}

