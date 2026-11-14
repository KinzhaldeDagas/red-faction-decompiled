// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058C9F0 rf_font_read_versioned_file_into_record
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Opens named font through virtual file reader; failed open returns0. Copies filename unbounded into record beginning (nominal name region before+32). Reads header DWORD+32 without validating its value, then signed version; version>1 is fatal, version<1 uses legacy encoding0xF and discards two legacy DWORDs later. Version1 reads encoding tag. Reads glyph count+40, first code+44, default advance+48, height+52 (also copied to spacing+56), kerning count+60, source byte size+64. Allocates/read kerning triples,16-byte glyph records (advance,width,pixelOffset,int16 kernStart,int16 extra), raw source pixels, and1024-byte palette only for tag0xFFFFFFF0. Closes file and returns1. Does not validate magic, nonnegative counts, offsets, file size, short reads or supported encoding;
// format support checked by atlas builder.
char __cdecl rf_font_read_versioned_file_into_record(char *Str, int a2)
{
  char v3; // [esp+7h] [ebp-15Dh]
  _BYTE *v4; // [esp+Ch] [ebp-158h]
  char *v5; // [esp+10h] [ebp-154h]
  int j; // [esp+2Ch] [ebp-138h]
  int i; // [esp+30h] [ebp-134h]
  int int32_versioned; // [esp+34h] [ebp-130h]
  int self[71]; // [esp+38h] [ebp-12Ch] BYREF
  int v10; // [esp+160h] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v10 = 0;
  if ( rf_vfile_open_with_extension_cache_control_paths(self, Str, 1, byte_98967F) >= 0 )
  {
    v5 = Str;
    v4 = (_BYTE *)a2;
    do
    {
      v3 = *v5;
      *v4++ = *v5++;
    }
    while ( v3 );
    *(_DWORD *)(a2 + 32) = rf_binary_stream_read_int32_versioned(self, 0, 0);
    int32_versioned = rf_binary_stream_read_int32_versioned(self, 0, 0);
    if ( int32_versioned > 1 )
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\vsdk\\gr\\gr_font.cpp",
        546,
        "Trying to read a newer font version than supported!!\n");
    if ( int32_versioned >= 1 )
      *(_DWORD *)(a2 + 36) = rf_binary_stream_read_uint32_versioned(self, 0, 0);
    else
      *(_DWORD *)(a2 + 36) = 15;
    *(_DWORD *)(a2 + 40) = rf_binary_stream_read_int32_versioned(self, 0, 0);
    *(_DWORD *)(a2 + 44) = rf_binary_stream_read_int32_versioned(self, 0, 0);
    *(_DWORD *)(a2 + 48) = rf_binary_stream_read_int32_versioned(self, 0, 0);
    *(_DWORD *)(a2 + 52) = rf_binary_stream_read_int32_versioned(self, 0, 0);
    *(_DWORD *)(a2 + 56) = *(_DWORD *)(a2 + 52);
    *(_DWORD *)(a2 + 60) = rf_binary_stream_read_int32_versioned(self, 0, 0);
    if ( int32_versioned < 1 )
    {
      rf_binary_stream_read_int32_versioned(self, 0, 0);
      rf_binary_stream_read_int32_versioned(self, 0, 0);
    }
    *(_DWORD *)(a2 + 64) = rf_binary_stream_read_int32_versioned(self, 0, 0);
    if ( *(_DWORD *)(a2 + 60) )
    {
      *(_DWORD *)(a2 + 68) = operator new(3 * *(_DWORD *)(a2 + 60));
      for ( i = 0; i < *(_DWORD *)(a2 + 60); ++i )
      {
        *(_BYTE *)(3 * i + *(_DWORD *)(a2 + 68)) = rf_binary_stream_read_char8_versioned(self, 0, 0);
        *(_BYTE *)(*(_DWORD *)(a2 + 68) + 3 * i + 1) = rf_binary_stream_read_char8_versioned(self, 0, 0);
        rf_vfile_read_buffered_bytes_versioned(self, (char *)(*(_DWORD *)(a2 + 68) + 3 * i + 2), 1u, 0, 0);
      }
    }
    else
    {
      *(_DWORD *)(a2 + 68) = 0;
    }
    if ( *(_DWORD *)(a2 + 40) )
    {
      *(_DWORD *)(a2 + 72) = operator new(16 * *(_DWORD *)(a2 + 40));
      for ( j = 0; j < *(_DWORD *)(a2 + 40); ++j )
      {
        *(_DWORD *)(16 * j + *(_DWORD *)(a2 + 72)) = rf_binary_stream_read_int32_versioned(self, 0, 0);
        *(_DWORD *)(*(_DWORD *)(a2 + 72) + 16 * j + 4) = rf_binary_stream_read_int32_versioned(self, 0, 0);
        *(_DWORD *)(*(_DWORD *)(a2 + 72) + 16 * j + 8) = rf_binary_stream_read_int32_versioned(self, 0, 0);
        *(_WORD *)(*(_DWORD *)(a2 + 72) + 16 * j + 12) = rf_binary_stream_read_int16_versioned(self, 0, 0);
        *(_WORD *)(*(_DWORD *)(a2 + 72) + 16 * j + 14) = rf_binary_stream_read_int16_versioned(self, 0, 0);
      }
    }
    else
    {
      *(_DWORD *)(a2 + 72) = 0;
    }
    if ( *(_DWORD *)(a2 + 64) )
    {
      *(_DWORD *)(a2 + 76) = operator new(*(_DWORD *)(a2 + 64));
      rf_vfile_read_buffered_bytes_versioned(self, *(char **)(a2 + 76), *(_DWORD *)(a2 + 64), 0, 0);
    }
    else
    {
      *(_DWORD *)(a2 + 76) = 0;
    }
    if ( *(_DWORD *)(a2 + 36) == -16 )
    {
      *(_DWORD *)(a2 + 80) = operator new(0x400u);
      rf_vfile_read_buffered_bytes_versioned(self, *(char **)(a2 + 80), 0x400u, 0, 0);
    }
    rf_vfile_close_stdio_or_vpp(self);
    v10 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 1;
  }
  else
  {
    v10 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 0;
  }
}

