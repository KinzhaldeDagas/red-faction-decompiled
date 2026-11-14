// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E45F0 rf_submarine_cockpit_load_gauge_digit_and_bank_bitmaps
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Lazy-load only handles==-1: sub_digits.vbm ->662EA0(local framecount discarded), sub_armor.vbm ->662EB4/count87C6C4, sub_primary.vbm ->662EC8/count87C6C8 via animation metadata loader(final -1,shared local duration0). sub_lb.vbm ->662EE8,sub_rb.vbm ->662EF8 through bitmap loader(-1,1). Failed handles remain retryable -1; no secondary assets, metadata validation or full-resource transaction.
void rf_submarine_cockpit_load_gauge_digit_and_bank_bitmaps()
{
  int v0; // [esp+0h] [ebp-8h] BYREF
  int v1; // [esp+4h] [ebp-4h] BYREF

  v0 = 0;
  if ( dword_662EA0 == -1 )
    dword_662EA0 = rf_bitmap_load_and_query_animation_metadata(aSubDigitsVbm, &v1, &v0, (void *)0xFFFFFFFF);
  if ( dword_662EB4 == -1 )
    dword_662EB4 = rf_bitmap_load_and_query_animation_metadata(aSubArmorVbm, &dword_87C6C4, &v0, (void *)0xFFFFFFFF);
  if ( dword_662EC8 == -1 )
    dword_662EC8 = rf_bitmap_load_and_query_animation_metadata(aSubPrimaryVbm, &dword_87C6C8, &v0, (void *)0xFFFFFFFF);
  if ( dword_662EE8 == -1 )
    dword_662EE8 = rf_bitmap_load_with_optional_mipmap_generation(aSubLbVbm, (void *)0xFFFFFFFF, 1);
  if ( dword_662EF8 == -1 )
    dword_662EF8 = rf_bitmap_load_with_optional_mipmap_generation(aSubRbVbm, (void *)0xFFFFFFFF, 1);
}

