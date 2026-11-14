// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E6210 rf_pcx_read_header_dimensions_palette
// UNREALRED VERIFIED [image-headers-20261028]: Six arguments name,optional width/height/bitdepth outputs,optional768-byte palette,source context. Opens original name or .pcx fallback. Returns1 open failure,2 header read error,3 unsupported header,0 accepted. Reads128-byte header; requires manufacturer10,version5,encoding1,planes1,bits8. Optional dimensions use signed16 xmax-xmin+1/ymax-ymin+1; no positive extent check. Optional palette reads final768 bytes without checking marker or resulting read/seek status, then returns0. Does not validate bytes-per-line, file minimum size or image payload; closes/destroys vfile on all paths.
int __cdecl rf_pcx_read_header_dimensions_palette(char *Str, _DWORD *a2, _DWORD *a3, _DWORD *a4, char *a5, char *a6)
{
  int size; // eax
  char v8[256]; // [esp+14h] [ebp-2ACh] BYREF
  char v9[3]; // [esp+114h] [ebp-1ACh] BYREF
  unsigned __int8 v10; // [esp+117h] [ebp-1A9h]
  __int16 v11; // [esp+118h] [ebp-1A8h]
  __int16 v12; // [esp+11Ah] [ebp-1A6h]
  __int16 v13; // [esp+11Ch] [ebp-1A4h]
  __int16 v14; // [esp+11Eh] [ebp-1A2h]
  char v15; // [esp+155h] [ebp-16Bh]
  int self[71]; // [esp+194h] [ebp-12Ch] BYREF
  int v17; // [esp+2BCh] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v17 = 0;
  if ( rf_vfile_open_with_extension_cache_control_paths(self, Str, 1, a6) >= 0
    || (rf_path_replace_last_dot_suffix_unbounded(v8, Str, ".pcx"),
        rf_vfile_open_with_extension_cache_control_paths(self, v8, 1, a6) >= 0) )
  {
    rf_vfile_read_buffered_bytes_versioned(self, v9, 0x80u, 0, 0);
    if ( rf_vfile_get_open_slot_status(self) )
    {
      rf_vfile_close_stdio_or_vpp(self);
      v17 = -1;
      rf_vfile_destruct_close_if_open(self);
      return 2;
    }
    else if ( v9[0] == 10 && v9[2] == 1 && v15 == 1 && v10 == 8 && v9[1] == 5 )
    {
      if ( a2 )
        *a2 = v13 - v11 + 1;
      if ( a3 )
        *a3 = v14 - v12 + 1;
      if ( a4 )
        *a4 = v10;
      if ( a5 )
      {
        size = rf_vfile_get_size((int)self, nullptr, (int)byte_98967F);
        rf_vfile_seek(self, size - 768, 0);
        rf_vfile_read_buffered_bytes_versioned(self, a5, 0x300u, 0, 0);
      }
      rf_vfile_close_stdio_or_vpp(self);
      v17 = -1;
      rf_vfile_destruct_close_if_open(self);
      return 0;
    }
    else
    {
      rf_vfile_close_stdio_or_vpp(self);
      v17 = -1;
      rf_vfile_destruct_close_if_open(self);
      return 3;
    }
  }
  else
  {
    v17 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 1;
  }
}

