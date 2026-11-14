// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005785F0 rf_bitmap_clear_all_locked_texture_tile_bytes
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): cdecl(handle). Queries resolved dimensions W/H,calculates signed tileCount=((W-1)/maxWidth187CCCC+1)*((H-1)/maxHeight187CCD0+1). For each tile,locks via573640(handle,tile,32B descriptor,mode1);if successful zeros descriptor.pixelPointer+12 for descriptor.height+20 * descriptor.pitchBytes+24 bytes,including row padding,then unlocks. Failed tiles skipped but loop still advances;EAX final count/index,NOT successful clears. No max-size-zero/dimension/overflow,pixel-pointer/lock-length or failed-metadata guard;all pixel values become zero rather than an opaque black color.
int __cdecl rf_bitmap_clear_all_locked_texture_tile_bytes(unsigned int a1)
{
  int result; // eax
  signed int i; // [esp+0h] [ebp-30h]
  int v3; // [esp+4h] [ebp-2Ch] BYREF
  unsigned int v4[8]; // [esp+8h] [ebp-28h] BYREF
  int v5; // [esp+28h] [ebp-8h]
  int v6; // [esp+2Ch] [ebp-4h] BYREF

  rf_bitmap_get_resolved_dimensions(a1, &v3, &v6);
  v5 = (v3 - 1) / unk_187CCCC + 1;
  result = v5 * ((v6 - 1) / unk_187CCD0 + 1);
  v5 = result;
  for ( i = 0; i < v5; ++i )
  {
    if ( rf_bitmap_lock_pixels_backend_dispatch(a1, i, v4, 1u) )
    {
      memset((void *)v4[3], 0, v4[5] * v4[6]);
      rf_bitmap_unlock_pixels_backend_dispatch(v4);
    }
    result = i + 1;
  }
  return result;
}

