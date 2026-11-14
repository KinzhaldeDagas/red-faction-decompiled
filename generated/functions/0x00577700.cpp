// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00577700 rf_bitmap_load_vbm_cpu_payload_by_slot
// UNREALRED VERIFIED [bitmap-decoders-20261028]: Argument bitmap slot INDEX. Gets format bytes/pixel. Any nonzero subtype+56 is treated as sequence child and backs up by108*byte+67; callers normally pass a resolved child. If parent pixels null, opens parent filename/context, seeks absolute32, allocates parent framecount byte67 * bytes/pixel * parent pixelcount+48, reads all frame payload. For format5 toggles bit0x8000 across all frames. Assigns each following frame record pixel pointer to slice offset(backoffset-1)*bytes/pixel*child pixelcount, sets parent reference byte92=framecount. If subtype0, opens/seeks32, allocates current pixel count; reduction mode1 seeks past original base image, mode2 past base plus quarter-area level, then reads desired remaining payload. Format5 toggles high bit only when record byte68<2. Closes/destroys vfile, but checks NONE of open/seek/read/allocation
// results and does not free old pointers. Return vfile destructor result, not load success. File type5 dispatch in0x576610 assumes success unconditionally.
int __cdecl rf_bitmap_load_vbm_cpu_payload_by_slot(int a1)
{
  int i; // [esp+Ch] [ebp-144h]
  int Size; // [esp+14h] [ebp-13Ch]
  char *v4; // [esp+18h] [ebp-138h]
  char *v5; // [esp+1Ch] [ebp-134h]
  char *Str; // [esp+20h] [ebp-130h]
  int self[70]; // [esp+24h] [ebp-12Ch] BYREF
  int v8; // [esp+140h] [ebp-10h]
  int v9; // [esp+14Ch] [ebp-4h]

  Str = (char *)(dword_1897344 + 108 * a1);
  rf_vfile_construct_unopened(self);
  v9 = 0;
  v8 = rf_bitmap_format_bytes_per_pixel(*((_DWORD *)Str + 15));
  if ( *((_DWORD *)Str + 14) )
  {
    v5 = &Str[-108 * (unsigned __int8)Str[67]];
    if ( !*((_DWORD *)v5 + 18) )
    {
      rf_vfile_open_with_extension_cache_control_paths(self, v5, 1, *((void **)Str + 25));
      rf_vfile_seek(self, 32, 0);
      Size = (unsigned __int8)v5[67] * v8 * *((_DWORD *)v5 + 12);
      *((_DWORD *)v5 + 18) = operator new(Size);
      rf_vfile_read_buffered_bytes_versioned(self, *((char **)v5 + 18), Size, 0, 0);
      rf_vfile_close_stdio_or_vpp(self);
      if ( *((_DWORD *)Str + 15) == 5 )
        rf_bitmap_pixel16_toggle_high_bit_run(*((_WORD **)v5 + 18), *((_DWORD *)Str + 12) * (unsigned __int8)v5[67]);
      v4 = v5;
      for ( i = 0; i < (unsigned __int8)v5[67]; ++i )
      {
        v4 += 108;
        *((_DWORD *)v4 + 18) = *((_DWORD *)v5 + 18) + ((unsigned __int8)v4[67] - 1) * v8 * *((_DWORD *)v4 + 12);
      }
      v5[92] = v5[67];
    }
  }
  else
  {
    rf_vfile_open_with_extension_cache_control_paths(self, Str, 1, *((void **)Str + 25));
    rf_vfile_seek(self, 32, 0);
    *((_DWORD *)Str + 18) = operator new(v8 * *((_DWORD *)Str + 12));
    if ( *((_DWORD *)Str + 26) == 1 )
    {
      rf_vfile_seek(self, *((unsigned __int16 *)Str + 21) * v8 * *((unsigned __int16 *)Str + 20), 1);
    }
    else if ( *((_DWORD *)Str + 26) == 2 )
    {
      rf_vfile_seek(
        self,
        v8
      * (((int)*((unsigned __int16 *)Str + 21) >> 1) * ((int)*((unsigned __int16 *)Str + 20) >> 1)
       + *((unsigned __int16 *)Str + 21) * *((unsigned __int16 *)Str + 20)),
        1);
    }
    rf_vfile_read_buffered_bytes_versioned(self, *((char **)Str + 18), v8 * *((_DWORD *)Str + 12), 0, 0);
    rf_vfile_close_stdio_or_vpp(self);
    if ( *((_DWORD *)Str + 15) == 5 && (unsigned __int8)Str[68] < 2u )
      rf_bitmap_pixel16_toggle_high_bit_run(*((_WORD **)Str + 18), *((_DWORD *)Str + 12));
  }
  v9 = -1;
  return rf_vfile_destruct_close_if_open(self);
}

