// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E3B90 rf_apc_cockpit_load_gauge_and_digit_bitmaps
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Lazy-load only handles==-1: apc_digits.vbm ->662E4C with local framecount discarded; apc_armor.vbm ->662E60 and framecount87C6B8; apc_primary.vbm ->662E74/count87C6BC; apc_secondary.vbm ->662E88/count87C6C0. All animation metadata loads use final -1 and shared local duration initialized0. Failed handles remain -1 and are retried; no validation of metadata counts or cross-asset success rollback.
void rf_apc_cockpit_load_gauge_and_digit_bitmaps()
{
  int v0; // [esp+0h] [ebp-8h] BYREF
  int v1; // [esp+4h] [ebp-4h] BYREF

  v0 = 0;
  if ( dword_662E4C == -1 )
    dword_662E4C = rf_bitmap_load_and_query_animation_metadata(aApcDigitsVbm, &v1, &v0, (void *)0xFFFFFFFF);
  if ( dword_662E60 == -1 )
    dword_662E60 = rf_bitmap_load_and_query_animation_metadata(aApcArmorVbm, &dword_87C6B8, &v0, (void *)0xFFFFFFFF);
  if ( dword_662E74 == -1 )
    dword_662E74 = rf_bitmap_load_and_query_animation_metadata(aApcPrimaryVbm, &dword_87C6BC, &v0, (void *)0xFFFFFFFF);
  if ( dword_662E88 == -1 )
    dword_662E88 = rf_bitmap_load_and_query_animation_metadata(aApcSecondaryVb, &dword_87C6C0, &v0, (void *)0xFFFFFFFF);
}

