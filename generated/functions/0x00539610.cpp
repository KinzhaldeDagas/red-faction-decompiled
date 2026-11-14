// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539610 rf_lightmap_tile_copy_rgb24_texel_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Thiscall tile,destinationX,destinationY,sourceX,sourceY. Tile+12 points to image header;image width DWORD+4,pixels pointer+12. Both coordinates offset by tile originX+16/originY+20. Byte offsets=3*(originX+x)+3*imageWidth*(originY+y). Copies three consecutive source bytes to destination in order,returns destination byte offset. No coordinate/image/NULL checks,channel conversion or row-pitch field;assumes tightly packed3-byte pixels. Same exact texel safe,arbitrary partial overlap not buffered.
int __thiscall rf_lightmap_tile_copy_rgb24_texel_unchecked(_DWORD *this, int a2, int a3, int a4, int a5)
{
  int v6; // [esp+8h] [ebp-Ch]
  int v7; // [esp+Ch] [ebp-8h]
  int v8; // [esp+10h] [ebp-4h]

  v7 = 3 * *(_DWORD *)(*(this + 3) + 4);
  v6 = 3 * (*(this + 4) + a4) + v7 * (*(this + 5) + a5);
  v8 = 3 * (*(this + 4) + a2) + v7 * (*(this + 5) + a3);
  *(_BYTE *)(*(_DWORD *)(*(this + 3) + 12) + v8) = *(_BYTE *)(*(_DWORD *)(*(this + 3) + 12) + v6);
  *(_BYTE *)(v8 + *(_DWORD *)(*(this + 3) + 12) + 1) = *(_BYTE *)(v6 + *(_DWORD *)(*(this + 3) + 12) + 1);
  *(_BYTE *)(v8 + *(_DWORD *)(*(this + 3) + 12) + 2) = *(_BYTE *)(v6 + *(_DWORD *)(*(this + 3) + 12) + 2);
  return v8;
}

