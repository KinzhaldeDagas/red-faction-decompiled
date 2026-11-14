// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005741B0 rf_bitmap_release_cpu_pixels_force_or_reference
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: Arguments handle, force byte. Animated handles select source bitmap slot through 36-byte entry DWORD0. For bitmap subtype DWORD+56 equal1/2, child subtype2 first backs up by 108*byte+67 to parent. Nonzero force frees regardless reference count; otherwise decrements byte+92 and frees only when new value is zero. Deletes parent pixel+72 and palette+80, nulls them and the corresponding pointers in byte+67 following frame records. Reference underflow wraps and suppresses freeing. Other subtypes delete pixel/palette immediately unless type DWORD+52==3, which retains user bitmap storage. Does not recycle records or release GPU textures. No bounds, ownership or stale-handle checks.
void __cdecl rf_bitmap_release_cpu_pixels_force_or_reference(unsigned int a1, char a2)
{
  int i; // [esp+10h] [ebp-14h]
  int v3; // [esp+14h] [ebp-10h]
  bool v4; // [esp+1Bh] [ebp-9h]
  unsigned int v5; // [esp+1Ch] [ebp-8h]
  int v6; // [esp+20h] [ebp-4h]

  v5 = rf_bitmap_handle_to_slot_index(a1);
  if ( (a1 & 0x40000000) != 0 )
    v5 = unk_187CD40[9 * v5];
  v6 = dword_1897344 + 108 * v5;
  if ( *(_DWORD *)(v6 + 56) == 1 || *(_DWORD *)(v6 + 56) == 2 )
  {
    if ( *(_DWORD *)(v6 + 56) == 2 )
      v6 -= 108 * *(unsigned __int8 *)(v6 + 67);
    if ( a2 )
      v4 = 1;
    else
      v4 = --*(_BYTE *)(v6 + 92) == 0;
    if ( v4 )
    {
      if ( *(_DWORD *)(v6 + 72) )
      {
        operator delete(*(void **)(v6 + 72));
        *(_DWORD *)(v6 + 72) = 0;
      }
      if ( *(_DWORD *)(v6 + 80) )
      {
        operator delete(*(void **)(v6 + 80));
        *(_DWORD *)(v6 + 80) = 0;
      }
      v3 = v6;
      for ( i = 0; i < *(unsigned __int8 *)(v6 + 67); ++i )
      {
        v3 += 108;
        *(_DWORD *)(v3 + 72) = 0;
        *(_DWORD *)(v3 + 80) = 0;
      }
    }
  }
  else if ( *(_DWORD *)(v6 + 52) != 3 )
  {
    if ( *(_DWORD *)(v6 + 72) )
    {
      operator delete(*(void **)(v6 + 72));
      *(_DWORD *)(v6 + 72) = 0;
    }
    if ( *(_DWORD *)(v6 + 80) )
    {
      operator delete(*(void **)(v6 + 80));
      *(_DWORD *)(v6 + 80) = 0;
    }
  }
}

