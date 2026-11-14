// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E5040 rf_vani_player_read_header_metadata
// UNREALRED VERIFIED [texture-conversion-20261028]: Openslocalvfilebyplayername,reads4-bytesignatureVANI,then sixversionedint32 fields: version+64,width+68,height+72,bitsperpixel+76,framerate+88,framecount+84. Bits8->internalformat1,16->3,24->6,32->7,other->0. Doesnotrejectunknownbits,nonpositiveextent/framerate/framecountorversion. Vfilestatusafterreadssetsreturn-1; else0. Signature/openfailure-1. Closessuccessfullyopenedvfileanddestroyslocalwrapperonallpaths. DoesnotcachepixelsorGPUtextures.
int __thiscall rf_vani_player_read_header_metadata(int this)
{
  int v3; // [esp+Ch] [ebp-140h]
  int self[71]; // [esp+18h] [ebp-134h] BYREF
  int v5; // [esp+138h] [ebp-14h]
  char Str1[4]; // [esp+13Ch] [ebp-10h] BYREF
  int v7; // [esp+148h] [ebp-4h]

  v5 = 0;
  rf_vfile_construct_unopened(self);
  v7 = 0;
  if ( rf_vfile_open_with_extension_cache_control_paths(self, (char *)this, 1, byte_98967F) >= 0 )
  {
    rf_vfile_read_buffered_bytes_versioned(self, Str1, 4u, 0, 0);
    if ( !strncmp(Str1, "VANI", 4u) )
    {
      *(_DWORD *)(this + 64) = rf_binary_stream_read_int32_versioned(self, 0, 0);
      *(_DWORD *)(this + 68) = rf_binary_stream_read_int32_versioned(self, 0, 0);
      *(_DWORD *)(this + 72) = rf_binary_stream_read_int32_versioned(self, 0, 0);
      *(_DWORD *)(this + 76) = rf_binary_stream_read_int32_versioned(self, 0, 0);
      *(_DWORD *)(this + 88) = rf_binary_stream_read_int32_versioned(self, 0, 0);
      *(_DWORD *)(this + 84) = rf_binary_stream_read_int32_versioned(self, 0, 0);
      switch ( *(_DWORD *)(this + 76) )
      {
        case 8:
          *(_DWORD *)(this + 80) = 1;
          break;
        case 0x10:
          *(_DWORD *)(this + 80) = 3;
          break;
        case 0x18:
          *(_DWORD *)(this + 80) = 6;
          break;
        case 0x20:
          *(_DWORD *)(this + 80) = 7;
          break;
        default:
          *(_DWORD *)(this + 80) = 0;
          break;
      }
      if ( rf_vfile_get_open_slot_status(self) )
        v5 = -1;
      rf_vfile_close_stdio_or_vpp(self);
      v3 = v5;
      v7 = -1;
      rf_vfile_destruct_close_if_open(self);
      return v3;
    }
    else
    {
      rf_vfile_close_stdio_or_vpp(self);
      v7 = -1;
      rf_vfile_destruct_close_if_open(self);
      return -1;
    }
  }
  else
  {
    v7 = -1;
    rf_vfile_destruct_close_if_open(self);
    return -1;
  }
}

