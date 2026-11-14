// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DFF80 rf_tga_read_header_dimensions
// UNREALRED VERIFIED [image-headers-20261028]: Seven arguments name,width/height/bitdepth outputs,two unused values,source context. Opens supplied name; only if no dot anywhere in name, appends .tga and retries. Initial success accepts nonnegative open result, fallback success tests exactly0. Reads18-byte TGA header, records open slot global0x664A54. On header status error returns1; otherwise writes signed16 width/height and unsigned byte bitdepth, returns0. Does NOT validate image type, dimensions, bitdepth, descriptor, palette or ID length. Output pointers mandatory. No palette/pixel read; closes/destroys vfile.
int __cdecl rf_tga_read_header_dimensions(char *Str, _DWORD *a2, _DWORD *a3, _DWORD *a4, int a5, int a6, char *a7)
{
  char v7; // al
  char *v10; // [esp+Ch] [ebp-36Ch]
  char *v11; // [esp+18h] [ebp-360h]
  char *v12; // [esp+1Ch] [ebp-35Ch]
  int v13; // [esp+28h] [ebp-350h] BYREF
  char v14[519]; // [esp+2Ch] [ebp-34Ch] BYREF
  char v15; // [esp+233h] [ebp-145h]
  char char8_versioned; // [esp+238h] [ebp-140h]
  char v18; // [esp+239h] [ebp-13Fh]
  char v19; // [esp+23Ah] [ebp-13Eh]
  __int16 int16_versioned; // [esp+23Ch] [ebp-13Ch]
  __int16 v21; // [esp+23Eh] [ebp-13Ah]
  char v22; // [esp+240h] [ebp-138h]
  __int16 v23; // [esp+242h] [ebp-136h]
  __int16 v24; // [esp+244h] [ebp-134h]
  __int16 v25; // [esp+246h] [ebp-132h]
  __int16 v26; // [esp+248h] [ebp-130h]
  unsigned __int8 v27; // [esp+24Ah] [ebp-12Eh]
  char v28; // [esp+24Bh] [ebp-12Dh]
  int self[71]; // [esp+24Ch] [ebp-12Ch] BYREF
  int v30; // [esp+374h] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v30 = 0;
  if ( rf_vfile_open_with_extension_cache_control_paths(self, Str, 1, a7) >= 0 )
    goto LABEL_11;
  v15 = 0;
  if ( !strchr(Str, 46) )
  {
    v12 = Str;
    v11 = v14;
    do
    {
      v7 = *v12;
      *v11++ = *v12++;
    }
    while ( v7 );
    v10 = (char *)&v13 + 3;
    while ( *++v10 )
      ;
    strcpy(v10, ".tga");
    if ( !rf_vfile_open_with_extension_cache_control_paths(self, v14, 1, a7) )
      v15 = 1;
  }
  if ( v15 )
  {
LABEL_11:
    dword_664A54 = self[0];
    char8_versioned = rf_binary_stream_read_char8_versioned(self, 0, 0);
    v18 = rf_binary_stream_read_char8_versioned(self, 0, 0);
    v19 = rf_binary_stream_read_char8_versioned(self, 0, 0);
    int16_versioned = rf_binary_stream_read_int16_versioned(self, 0, 0);
    v21 = rf_binary_stream_read_int16_versioned(self, 0, 0);
    v22 = rf_binary_stream_read_char8_versioned(self, 0, 0);
    v23 = rf_binary_stream_read_int16_versioned(self, 0, 0);
    v24 = rf_binary_stream_read_int16_versioned(self, 0, 0);
    v25 = rf_binary_stream_read_int16_versioned(self, 0, 0);
    v26 = rf_binary_stream_read_int16_versioned(self, 0, 0);
    v27 = rf_binary_stream_read_char8_versioned(self, 0, 0);
    v28 = rf_binary_stream_read_char8_versioned(self, 0, 0);
    if ( rf_vfile_get_open_slot_status(self) )
    {
      rf_vfile_close_stdio_or_vpp(self);
      v30 = -1;
      rf_vfile_destruct_close_if_open(self);
      return 1;
    }
    else
    {
      *a2 = v25;
      *a3 = v26;
      *a4 = v27;
      rf_vfile_close_stdio_or_vpp(self);
      v30 = -1;
      rf_vfile_destruct_close_if_open(self);
      return 0;
    }
  }
  else
  {
    v13 = 1;
    v30 = -1;
    rf_vfile_destruct_close_if_open(self);
    return v13;
  }
}

