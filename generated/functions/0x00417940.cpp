// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417940 rf_monitor_fill_noise_bitmap
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Lock bitmap handle record+0x14 through0x573640; fill width*height contiguous16-bit pixels. Per pixel multiply global RNG dword0x6612DC by65539, writing0 when RNG bit0x40000 is set and0xFFFF otherwise. Unlock through0x573680 then OR record flags+0x38 with4. No rendered-bit guard inside this function.
int __cdecl rf_monitor_fill_noise_bitmap(int a1)
{
  unsigned int v2[8]; // [esp+0h] [ebp-30h] BYREF
  __int16 *v3; // [esp+20h] [ebp-10h]
  int j; // [esp+24h] [ebp-Ch]
  int i; // [esp+28h] [ebp-8h]
  __int16 v6; // [esp+2Ch] [ebp-4h]

  rf_bitmap_lock_pixels_backend_dispatch(*(_DWORD *)(a1 + 20), 0, (int)v2, 1);
  v3 = (__int16 *)v2[3];
  for ( i = 0; i < (int)v2[5]; ++i )
  {
    for ( j = 0; j < (int)v2[4]; ++j )
    {
      dword_6612DC *= 65539;
      if ( (dword_6612DC & 0x40000) != 0 )
        v6 = 0;
      else
        v6 = -1;
      *v3++ = v6;
    }
  }
  rf_bitmap_unlock_pixels_backend_dispatch(v2);
  *(_DWORD *)(a1 + 56) |= 4u;
  return a1;
}

