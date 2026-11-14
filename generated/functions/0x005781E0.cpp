// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005781E0 rf_bitmap_handle_recycle_slot_or_animation_entry
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: Decodes handle with 0x574350. Ordinary handle delegates slot index to 0x574890, which clears pointers without freeing allocations. Animated handle locates 36-byte entry at 0x187CD40 + 36*index, writes entry+12=-1, unlinks next/previous +4/+8, inserts at free-list head 0x18973C0 with sentinel 0x18973BC. Returns 0 on animation path. Does not free source bitmap frames, CPU pixels, palette or GPU textures itself; no double-release, occupancy or stale-generation checks.
int __cdecl rf_bitmap_handle_recycle_slot_or_animation_entry(unsigned int a1)
{
  int *v2; // [esp+4h] [ebp-8h]
  unsigned int v3; // [esp+8h] [ebp-4h]

  v3 = rf_bitmap_handle_to_slot_index(a1);
  if ( (a1 & 0x40000000) == 0 )
    return rf_bitmap_slot_recycle_without_freeing_pixels(v3);
  v2 = &unk_187CD40[9 * v3];
  v2[3] = -1;
  *(_DWORD *)(v2[2] + 4) = v2[1];
  *(_DWORD *)(v2[1] + 8) = v2[2];
  v2[1] = 0;
  v2[2] = 0;
  v2[1] = dword_18973C0;
  *(_DWORD *)(dword_18973C0 + 8) = v2;
  dword_18973C0 = (int)v2;
  v2[2] = (int)&unk_18973BC;
  return 0;
}

