// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E6470 rf_pcx_read_indexed8_pixels_palette
// UNREALRED VERIFIED [bitmap-decoders-20261028]: Arguments filename,output index pixels,output768-byte palette,source context. Opens original or .pcx fallback. Return codes:1 open failure,2 header read error,3 unsupported header,4 initial compressed-buffer read error,0 success. Requires manufacturer10, encoding1, planes1, bits/pixel8, version5. Width=xmax-xmin+1,height=ymax-ymin+1; no positive extent validation. Reads palette from final768 bytes WITHOUT checking preceding palette marker, seeks128, reads initial1024-byte compressed buffer and tests stream status only there. Per row decodes header bytes-per-line (signed16) worth of PCX RLE: control top bits0xC0 encode low6 repeat count, next byte value; other bytes literal. Copies only first logical width pixels, discarding row padding, carries repeat count across rows. Refills1024-byte buffer without checking subsequent read status.
// Zero-length repeat packet becomes negative after decrement and can suppress subsequent packet reads. No output bounds, palette null check, source remaining-length or bytes-per-line>=width check. Returns success after loops even if later reads failed; closes/destroys vfile on all paths.
int __cdecl rf_pcx_read_indexed8_pixels_palette(char *Str, char *a2, char *a3, char *a4)
{
  int v5; // eax
  char v6[256]; // [esp+18h] [ebp-6CCh] BYREF
  char v7[4]; // [esp+118h] [ebp-5CCh] BYREF
  __int16 v8; // [esp+11Ch] [ebp-5C8h]
  __int16 v9; // [esp+11Eh] [ebp-5C6h]
  __int16 v10; // [esp+120h] [ebp-5C4h]
  __int16 v11; // [esp+122h] [ebp-5C2h]
  char v12; // [esp+159h] [ebp-58Bh]
  __int16 v13; // [esp+15Ah] [ebp-58Ah]
  char v14[1024]; // [esp+198h] [ebp-54Ch] BYREF
  int self[70]; // [esp+598h] [ebp-14Ch] BYREF
  int v16; // [esp+6B4h] [ebp-30h]
  char v17; // [esp+6BBh] [ebp-29h]
  size_t Size; // [esp+6BCh] [ebp-28h]
  int v19; // [esp+6C0h] [ebp-24h]
  char *v20; // [esp+6C4h] [ebp-20h]
  int i; // [esp+6C8h] [ebp-1Ch]
  int v22; // [esp+6CCh] [ebp-18h]
  int j; // [esp+6D0h] [ebp-14h]
  int v24; // [esp+6D4h] [ebp-10h]
  int v25; // [esp+6E0h] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v25 = 0;
  v17 = 0;
  if ( rf_vfile_open_with_extension_cache_control_paths(self, Str, 1, a4) >= 0
    || (rf_path_replace_last_dot_suffix_unbounded(v6, Str, ".pcx"),
        rf_vfile_open_with_extension_cache_control_paths(self, v6, 1, a4) >= 0) )
  {
    rf_vfile_read_buffered_bytes_versioned(self, v7, 0x80u, 0, 0);
    if ( rf_vfile_get_open_slot_status(self) )
    {
      rf_vfile_close_stdio_or_vpp(self);
      v25 = -1;
      rf_vfile_destruct_close_if_open(self);
      return 2;
    }
    else if ( v7[0] == 10 && v7[2] == 1 && v12 == 1 && v7[3] == 8 && v7[1] == 5 )
    {
      v16 = v10 - v8 + 1;
      v24 = v11 - v9 + 1;
      v5 = rf_vfile_get_size((int)self, nullptr, (int)byte_98967F);
      rf_vfile_seek(self, v5 - 768, 0);
      rf_vfile_read_buffered_bytes_versioned(self, a3, 0x300u, 0, 0);
      rf_vfile_seek(self, 128, 0);
      Size = 1024;
      v19 = 0;
      rf_vfile_read_buffered_bytes_versioned(self, v14, 0x400u, 0, 0);
      if ( rf_vfile_get_open_slot_status(self) )
      {
        rf_vfile_close_stdio_or_vpp(self);
        v25 = -1;
        rf_vfile_destruct_close_if_open(self);
        return 4;
      }
      else
      {
        v22 = 0;
        for ( i = 0; i < v24; ++i )
        {
          v20 = a2;
          for ( j = 0; j < v13; ++j )
          {
            if ( !v22 )
            {
              v17 = v14[v19++];
              if ( v19 == Size )
              {
                rf_vfile_read_buffered_bytes_versioned(self, v14, Size, 0, 0);
                v19 = 0;
              }
              if ( (v17 & 0xC0) == 0xC0 )
              {
                v22 = v17 & 0x3F;
                v17 = v14[v19++];
                if ( v19 == Size )
                {
                  rf_vfile_read_buffered_bytes_versioned(self, v14, Size, 0, 0);
                  v19 = 0;
                }
              }
              else
              {
                v22 = 1;
              }
            }
            if ( j < v16 )
              *v20++ = v17;
            --v22;
          }
          a2 += v16;
        }
        rf_vfile_close_stdio_or_vpp(self);
        v25 = -1;
        rf_vfile_destruct_close_if_open(self);
        return 0;
      }
    }
    else
    {
      rf_vfile_close_stdio_or_vpp(self);
      v25 = -1;
      rf_vfile_destruct_close_if_open(self);
      return 3;
    }
  }
  else
  {
    v25 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 1;
  }
}

