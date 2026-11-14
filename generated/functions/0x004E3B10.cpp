// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E3B10 rf_fighter_cockpit_load_digit_and_bank_bitmaps
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Lazy-load only handles equal -1. Fighter01_digits.vbm ->662EFC via animation metadata loader(local framecount discarded); fighter01_lb.vbm ->662F50 and fighter01_rb.vbm ->662F68 via bitmap loader(-1,1). Returned failure -1 remains retryable. No APC gauge/count loads, per-model cache, unload or error handling.
void rf_fighter_cockpit_load_digit_and_bank_bitmaps()
{
  int v0; // [esp+0h] [ebp-8h] BYREF
  int v1; // [esp+4h] [ebp-4h] BYREF

  v0 = 0;
  if ( dword_662EFC == -1 )
    dword_662EFC = rf_bitmap_load_and_query_animation_metadata(aFighter01Digit, &v1, &v0, (void *)0xFFFFFFFF);
  if ( dword_662F50 == -1 )
    dword_662F50 = rf_bitmap_load_with_optional_mipmap_generation(aFighter01LbVbm, (void *)0xFFFFFFFF, 1);
  if ( dword_662F68 == -1 )
    dword_662F68 = rf_bitmap_load_with_optional_mipmap_generation(aFighter01RbVbm, (void *)0xFFFFFFFF, 1);
}

