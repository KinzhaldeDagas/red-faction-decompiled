// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E52D0 rf_vani_player_read_frame_pixels
// UNREALRED VERIFIED [texture-conversion-20261028]: Argumentsframeindex,outputpixels,optionaloutputpalette. Opens/reusesembeddedvfile+120byplayername. Seeks frameindexentry at28+8*index,readsabsolutedataoffsetandstoredsize,seeksdata. Forbits8,read768-bytepaletteifoutputprovidedelseskipit,and subtract768fromstoredsize. Version<=1readsremainingstoredsizeDIRECTLYintooutput; version>1allocatestemporarycompressedblock,readssize,decodes0x5E02C0 forwidth*height pixels ofceil(bits/8)bytes,thenfreesblock. Return-1ifopen/readstatuserror,elsesizeminuspalette. No frameindexbounds,storedsize>=768,allocation/outputcapacity/decompressedsizeorreadlengthvalidation. Leavesembeddedfileopen.
int __thiscall rf_vani_player_read_frame_pixels(int this, int a2, char *a3, char *a4)
{
  char *v6; // [esp+Ch] [ebp-10h]
  int Size; // [esp+10h] [ebp-Ch]
  int int32_versioned; // [esp+14h] [ebp-8h]

  if ( !rf_vfile_has_nonnegative_stream_slot((_DWORD *)(this + 120))
    && rf_vfile_open_with_extension_cache_control_paths((int *)(this + 120), (char *)this, 1, byte_98967F) < 0 )
  {
    return -1;
  }
  rf_vfile_seek((int *)(this + 120), 8 * a2 + 28, 0);
  int32_versioned = rf_binary_stream_read_int32_versioned((int *)(this + 120), 0, 0);
  Size = rf_binary_stream_read_int32_versioned((int *)(this + 120), 0, 0);
  rf_vfile_seek((int *)(this + 120), int32_versioned, 0);
  if ( *(_DWORD *)(this + 76) == 8 )
  {
    if ( a4 )
      rf_vfile_read_buffered_bytes_versioned((int *)(this + 120), a4, 0x300u, 0, 0);
    else
      rf_vfile_seek((int *)(this + 120), int32_versioned + 768, 0);
  }
  if ( *(_DWORD *)(this + 76) == 8 )
    Size -= 768;
  if ( *(int *)(this + 64) <= 1 )
  {
    rf_vfile_read_buffered_bytes_versioned((int *)(this + 120), a3, Size, 0, 0);
  }
  else
  {
    v6 = (char *)operator new(Size);
    rf_vfile_read_buffered_bytes_versioned((int *)(this + 120), v6, Size, 0, 0);
    rf_vani_decode_pixel_packets_rle(
      a3,
      (unsigned __int8 *)v6,
      *(_DWORD *)(this + 72) * *(_DWORD *)(this + 68),
      (*(_DWORD *)(this + 76) + 7) / 8);
    operator delete(v6);
  }
  if ( rf_vfile_get_open_slot_status((_DWORD *)(this + 120)) )
    return -1;
  else
    return Size;
}

