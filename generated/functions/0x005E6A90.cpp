// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E6A90 rf_pcx_write_rle_scanline
// UNREALRED VERIFIED [image-headers-20261028]: Actual THREE stack arguments source row,logical width,stream pointer. Reads first source byte before checking width. Accumulates equal-byte runs, flushes at63 through0x5E6BB0, escapes literals whose high bits are0xC0, flushes final run, returns intended encoded byte count. Width<=0 still encodes one byte because initial run starts1; no source length checks. Packet helper ignores I/O errors, so nonzero result does not prove file writes succeeded. Emits no row padding or even-width adjustment.
int __cdecl rf_pcx_write_rle_scanline(unsigned __int8 *a1, int a2)
{
  int i; // [esp+0h] [ebp-10h]
  int v4; // [esp+4h] [ebp-Ch]
  int v5; // [esp+8h] [ebp-8h]
  int v6; // [esp+8h] [ebp-8h]
  int v7; // [esp+8h] [ebp-8h]
  char v8; // [esp+Dh] [ebp-3h]
  unsigned __int8 v9; // [esp+Eh] [ebp-2h]
  unsigned __int8 v10; // [esp+Fh] [ebp-1h]

  v4 = 0;
  v9 = *a1;
  v8 = 1;
  for ( i = 1; i < a2; ++i )
  {
    v10 = *++a1;
    if ( *a1 == v9 )
    {
      if ( ++v8 == 63 )
      {
        v5 = rf_pcx_write_rle_packet(v9, v8);
        if ( !v5 )
          return 0;
        v4 += v5;
        v8 = 0;
      }
    }
    else
    {
      if ( v8 )
      {
        v6 = rf_pcx_write_rle_packet(v9, v8);
        if ( !v6 )
          return 0;
        v4 += v6;
      }
      v9 = v10;
      v8 = 1;
    }
  }
  if ( !v8 )
    return v4;
  v7 = rf_pcx_write_rle_packet(v9, v8);
  if ( v7 )
    return v7 + v4;
  else
    return 0;
}

