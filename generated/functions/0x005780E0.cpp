// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005780E0 rf_bitmap_estimate_frame_set_storage_from_multiplier
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): cdecl(handle,callerMultiplier). First resolves and returns-1 for negative index. Gets frame count from574AA0(handle,NULL),then5764B0 resolves AGAIN and obtains current record mip-pixel count+48 as its third output. Returns callerMultiplier * storedMipPixelCount * frameCount with unchecked32bit multiplication;does not derive multiplier from format or sum each frame independently. With bytes-per-pixel multiplier this estimates whole frame-set bytes. Tagged-instance count inherits574AA0 decoded-index tag bug. If record file type0,5764B0 leaves third output unchanged,so this function can multiply uninitialized local value. No clock snapshot,overflow/type/count validation.
int __cdecl rf_bitmap_estimate_frame_set_storage_from_multiplier(unsigned int handle, int multiplier)
{
  int v3; // [esp+0h] [ebp-18h]
  int v4; // [esp+4h] [ebp-14h] BYREF
  int v5; // [esp+8h] [ebp-10h]
  int v6; // [esp+Ch] [ebp-Ch] BYREF
  int v7; // [esp+10h] [ebp-8h] BYREF
  int v8; // [esp+14h] [ebp-4h] BYREF

  v5 = rf_bitmap_resolve_current_frame_slot(handle);
  if ( v5 < 0 )
    return -1;
  v3 = rf_bitmap_animation_metadata_query(handle, nullptr);
  rf_bitmap_get_resolved_upload_metadata(handle, &v8, &v6, &v7, &v4);
  return multiplier * v7 * v3;
}

