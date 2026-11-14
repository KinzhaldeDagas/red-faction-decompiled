// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E1550 rf_tga_write_truecolor_raw_image
// UNREALRED VERIFIED [image-headers-20261028]: Seven arguments name,source pixels,unused argument,width,height,bitdepth,source context. Opens .tga output mode2; writes header type2,dimensions16-bit,depth byte,descriptor0x20, then contiguous ceil(depth/8)*width*height source bytes. Returns-1 only open failure,else0 after close. No pixel channel conversion,row reversal,stride handling,attribute nibble adjustment,write-status,size or dimension checks.
int __cdecl rf_tga_write_truecolor_raw_image(char *Str, _BYTE *Buffer, int a3, int a4, int a5, int a6, char *a7)
{
  char v8[256]; // [esp+Ch] [ebp-22Ch] BYREF
  int stream[70]; // [esp+10Ch] [ebp-12Ch] BYREF
  int v10; // [esp+228h] [ebp-10h]
  int v11; // [esp+234h] [ebp-4h]

  rf_vfile_construct_unopened(stream);
  v11 = 0;
  v10 = (a6 + 7) / 8;
  rf_path_replace_last_dot_suffix_unbounded(v8, Str, ".tga");
  if ( rf_vfile_open_with_extension_cache_control_paths(stream, v8, 2, a7) >= 0 )
  {
    rf_binary_stream_write_byte_host_order(stream, 0);
    rf_binary_stream_write_byte_host_order(stream, 0);
    rf_binary_stream_write_byte_host_order(stream, 2);
    rf_binary_stream_write_word_host_order(stream, 0);
    rf_binary_stream_write_word_host_order(stream, 0);
    rf_binary_stream_write_byte_host_order(stream, 0);
    rf_binary_stream_write_word_host_order(stream, 0);
    rf_binary_stream_write_word_host_order(stream, 0);
    rf_binary_stream_write_word_host_order(stream, a4);
    rf_binary_stream_write_word_host_order(stream, a5);
    rf_binary_stream_write_byte_host_order(stream, a6);
    rf_binary_stream_write_byte_host_order(stream, 32);
    rf_vfile_write_bytes_with_optional_feedback(stream, Buffer, v10 * a5 * a4);
    rf_vfile_close_stdio_or_vpp(stream);
    v11 = -1;
    rf_vfile_destruct_close_if_open(stream);
    return 0;
  }
  else
  {
    v11 = -1;
    rf_vfile_destruct_close_if_open(stream);
    return -1;
  }
}

