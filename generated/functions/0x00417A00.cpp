// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417A00 rf_monitor_fill_black_bitmap
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Only when record flags+0x38 bit4 is clear: lock bitmap+0x14, memset contiguous2*width*height bytes to0, unlock. Does not set rendered bit4 afterward. Already-bit4 case returns without clearing bitmap.
int __cdecl rf_monitor_fill_black_bitmap(int a1)
{
  int result; // eax
  unsigned int v2[3]; // [esp+0h] [ebp-24h] BYREF
  void *v3; // [esp+Ch] [ebp-18h]
  int v4; // [esp+10h] [ebp-14h]
  int v5; // [esp+14h] [ebp-10h]
  void *v6; // [esp+20h] [ebp-4h]

  result = a1;
  if ( (*(_DWORD *)(a1 + 56) & 4) == 0 )
  {
    rf_bitmap_lock_pixels_backend_dispatch(*(_DWORD *)(a1 + 20), 0, (int)v2, 1);
    v6 = v3;
    memset(v3, 0, 2 * v4 * v5);
    return rf_bitmap_unlock_pixels_backend_dispatch(v2);
  }
  return result;
}

