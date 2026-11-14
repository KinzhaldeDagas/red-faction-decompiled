// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E6850 rf_pcx_write_indexed8_rows_palette
// UNREALRED VERIFIED [image-headers-20261028]: Arguments name,width,height,array of row pointers,768-byte RGB palette. Replaces/appends .pcx filename, builds128-byte header manufacturer10/version5/encoding1/bits8/planes1, xmax=width-1,ymax=height-1,bytes-per-line=width WITHOUT even rounding. Opens write mode2 in default source context. Writes header, encodes each row0x5E6A90, writes palette marker12 and768 palette bytes, closes. Returns1 open failure,6 row helper returned0 or post-close status error,else0. RLE helpers return intended byte counts and ignore I/O errors, so early row checks are weak. No width/height positivity,16-bit truncation,row/palette capacity or path-length checks.
int __cdecl rf_pcx_write_indexed8_rows_palette(char *Str, int a2, int a3, int a4, _BYTE *a5)
{
  int i; // [esp+14h] [ebp-3B0h]
  _WORD Buffer[64]; // [esp+18h] [ebp-3ACh] BYREF
  int self[70]; // [esp+98h] [ebp-32Ch] BYREF
  char v9[516]; // [esp+1B0h] [ebp-214h] BYREF
  int v10; // [esp+3C0h] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v10 = 0;
  rf_path_replace_last_dot_suffix_unbounded(v9, Str, ".pcx");
  memset(Buffer, 0, sizeof(Buffer));
  Buffer[0] = 1290;
  Buffer[1] = 2049;
  HIBYTE(Buffer[32]) = 1;
  Buffer[4] = a2 - 1;
  Buffer[5] = a3 - 1;
  Buffer[3] = 0;
  Buffer[2] = 0;
  Buffer[33] = a2;
  if ( rf_vfile_open_with_extension_cache_control_paths(self, v9, 2, byte_98967F) >= 0 )
  {
    rf_vfile_write_bytes_with_optional_feedback(self, Buffer, 0x80u);
    for ( i = 0; i < a3; ++i )
    {
      if ( !rf_pcx_write_rle_scanline(*(unsigned __int8 **)(a4 + 4 * i), a2, (int)self) )
      {
        rf_vfile_close_stdio_or_vpp(self);
        v10 = -1;
        rf_vfile_destruct_close_if_open(self);
        return 6;
      }
    }
    rf_binary_stream_write_byte_host_order(self, 12);
    rf_vfile_write_bytes_with_optional_feedback(self, a5, 0x300u);
    rf_vfile_close_stdio_or_vpp(self);
    if ( rf_vfile_get_open_slot_status(self) )
    {
      v10 = -1;
      rf_vfile_destruct_close_if_open(self);
      return 6;
    }
    else
    {
      v10 = -1;
      rf_vfile_destruct_close_if_open(self);
      return 0;
    }
  }
  else
  {
    v10 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 1;
  }
}

