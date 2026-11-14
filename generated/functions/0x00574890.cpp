// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00574890 rf_bitmap_slot_recycle_without_freeing_pixels
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: Argument is an ordinary slot INDEX, not handle. Locates 108-byte record at 0x1897344, unlinks through next/previous +84/+88 and inserts into free-list head 0x18973A8 with sentinel 0x1897350. Clears name byte0, hash+32=-1, handle+36=-1, type+52=0, current width/height+44/+46, mip count byte+64, pixel count+48, format+60, pixel pointer+72, palette pointer+80, reference byte+92, fields+96/+104. Does NOT delete pointed pixel/palette allocations or invalidate renderer textures; callers must release first. Several other fields remain stale. Returns record pointer; no index or membership guard.
int __cdecl rf_bitmap_slot_recycle_without_freeing_pixels(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = dword_1897344 + 108 * a1;
  *(_DWORD *)(*(_DWORD *)(v2 + 88) + 84) = *(_DWORD *)(v2 + 84);
  *(_DWORD *)(*(_DWORD *)(v2 + 84) + 88) = *(_DWORD *)(v2 + 88);
  *(_DWORD *)(v2 + 84) = 0;
  *(_DWORD *)(v2 + 88) = 0;
  *(_DWORD *)(v2 + 88) = unk_18973A8;
  *(_DWORD *)(v2 + 84) = &unk_1897350;
  *(_DWORD *)(unk_18973A8 + 84) = v2;
  unk_18973A8 = v2;
  *(_BYTE *)v2 = 0;
  *(_DWORD *)(v2 + 32) = -1;
  *(_DWORD *)(v2 + 52) = 0;
  *(_DWORD *)(v2 + 36) = -1;
  *(_WORD *)(v2 + 44) = 0;
  *(_WORD *)(v2 + 46) = 0;
  *(_BYTE *)(v2 + 64) = 0;
  *(_DWORD *)(v2 + 48) = 0;
  *(_DWORD *)(v2 + 60) = 0;
  *(_DWORD *)(v2 + 72) = 0;
  *(_DWORD *)(v2 + 80) = 0;
  *(_BYTE *)(v2 + 92) = 0;
  *(_DWORD *)(v2 + 96) = 0;
  *(_DWORD *)(v2 + 104) = 0;
  return v2;
}

