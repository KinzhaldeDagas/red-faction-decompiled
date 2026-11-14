// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573F20 rf_vbm_read_header_metadata
// UNREALRED VERIFIED [bitmap-loading-20261028]: Arguments filename,width,height,format,framecount,mipcount,rate,extra/header field,source context. Opens vfile; failure0. Reads four signature bytes but NEVER checks them. Reads int32 outputs in order: extra field,width,height,format selector,rate,framecount,mipcount-minus-one. Format selector0->internal5,1->4,other->3. Adds1 to stored mip count; if global0x663F10clear forces mipcount1. Closes/destroys vfile and returns1 without checking post-read status or field ranges. Does not load pixel data. Local .vbm string is unused.
int __cdecl rf_vbm_read_header_metadata(
        char *Str,
        int *a2,
        int *a3,
        _DWORD *a4,
        int *a5,
        _DWORD *a6,
        int *a7,
        int *a8,
        void *a9)
{
  int int32_versioned; // [esp+Ch] [ebp-138h]
  int self[70]; // [esp+10h] [ebp-134h] BYREF
  char v12[8]; // [esp+128h] [ebp-1Ch] BYREF
  char v13[4]; // [esp+134h] [ebp-10h] BYREF
  int v14; // [esp+140h] [ebp-4h]

  strcpy(v12, ".vbm");
  rf_vfile_construct_unopened(self);
  v14 = 0;
  if ( rf_vfile_open_with_extension_cache_control_paths(self, Str, 1, a9) >= 0 )
  {
    rf_vfile_read_buffered_bytes_versioned(self, v13, 4u, 0, 0);
    *a8 = rf_binary_stream_read_int32_versioned(self, 0, 0);
    *a2 = rf_binary_stream_read_int32_versioned(self, 0, 0);
    *a3 = rf_binary_stream_read_int32_versioned(self, 0, 0);
    int32_versioned = rf_binary_stream_read_int32_versioned(self, 0, 0);
    if ( int32_versioned )
    {
      if ( int32_versioned == 1 )
        *a4 = 4;
      else
        *a4 = 3;
    }
    else
    {
      *a4 = 5;
    }
    *a7 = rf_binary_stream_read_int32_versioned(self, 0, 0);
    *a5 = rf_binary_stream_read_int32_versioned(self, 0, 0);
    *a6 = rf_binary_stream_read_int32_versioned(self, 0, 0) + 1;
    if ( !byte_663F10 )
      *a6 = 1;
    rf_vfile_close_stdio_or_vpp(self);
    v14 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 1;
  }
  else
  {
    v14 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 0;
  }
}

