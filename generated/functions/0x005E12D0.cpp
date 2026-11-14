// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E12D0 rf_tga_write_truecolor_rle_image
// UNREALRED VERIFIED [image-headers-20261028]: Seven arguments name,source pixels,unused argument,width,height,bitdepth,source context. Creates .tga path, opens mode2. Writes18-byte header image type10,RLE truecolor,no palette/origin,dimensions truncated16-bit,pixel depth byte,descriptor0x20 (top origin,attribute nibble0 regardless depth). Bytes/pixel=ceil(depth/8); allocates2*bytes*width*height output, calls0x5DFBB0(compareBytes=sourceStride=bytes,total input bytes=bytes*width*height). Nonnegative encoder count writes block, closes/deletes and returns0; encoder negative or open failure-1. No dimension/bitdepth/allocation/capacity or write-status checks. For16-bit depth payload helper0x5DFE10 does not populate output payload, despite encoded count. Header alone does not establish a valid complete file.
int __cdecl rf_tga_write_truecolor_rle_image(char *Str, char *a2, int a3, int a4, int a5, int a6, char *a7)
{
  char v8[256]; // [esp+1Ch] [ebp-234h] BYREF
  size_t ElementSize; // [esp+11Ch] [ebp-134h]
  void *Buffer; // [esp+120h] [ebp-130h]
  int stream[70]; // [esp+124h] [ebp-12Ch] BYREF
  int v12; // [esp+240h] [ebp-10h]
  int v13; // [esp+24Ch] [ebp-4h]

  rf_vfile_construct_unopened(stream);
  v13 = 0;
  v12 = (a6 + 7) / 8;
  rf_path_replace_last_dot_suffix_unbounded(v8, Str, ".tga");
  if ( rf_vfile_open_with_extension_cache_control_paths(stream, v8, 2, a7) >= 0 )
  {
    rf_binary_stream_write_byte_host_order(stream, 0);
    rf_binary_stream_write_byte_host_order(stream, 0);
    rf_binary_stream_write_byte_host_order(stream, 10);
    rf_binary_stream_write_word_host_order(stream, 0);
    rf_binary_stream_write_word_host_order(stream, 0);
    rf_binary_stream_write_byte_host_order(stream, 0);
    rf_binary_stream_write_word_host_order(stream, 0);
    rf_binary_stream_write_word_host_order(stream, 0);
    rf_binary_stream_write_word_host_order(stream, a4);
    rf_binary_stream_write_word_host_order(stream, a5);
    rf_binary_stream_write_byte_host_order(stream, a6);
    rf_binary_stream_write_byte_host_order(stream, 32);
    Buffer = operator new(v12 * 2 * a5 * a4);
    ElementSize = (size_t)rf_tga_encode_rle_packets(Buffer, a2, v12, v12, v12 * a5 * a4);
    if ( (ElementSize & 0x80000000) == 0 )
    {
      rf_vfile_write_bytes_with_optional_feedback(stream, Buffer, ElementSize);
      rf_vfile_close_stdio_or_vpp(stream);
      operator delete(Buffer);
      v13 = -1;
      rf_vfile_destruct_close_if_open(stream);
      return 0;
    }
    else
    {
      operator delete(Buffer);
      rf_vfile_close_stdio_or_vpp(stream);
      v13 = -1;
      rf_vfile_destruct_close_if_open(stream);
      return -1;
    }
  }
  else
  {
    v13 = -1;
    rf_vfile_destruct_close_if_open(stream);
    return -1;
  }
}

