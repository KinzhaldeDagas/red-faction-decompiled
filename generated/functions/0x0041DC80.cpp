// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041DC80 rf_corpse_cleanup_resources_and_unlink
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Cdecl corpse. Assigns empty RFString at+676. Resolves associated item UID+716; success marks item for deferred deletion and sets716=-1, resolution failure leaves stale UID unchanged. Nonzero secondary pointer720 calls burn-effect release0x43EFD0(pointer,0): delegate checks entity owners first, then clears the FIRST matching corpse720 only if no entity matched; this caller has no independent720 reset. Unlinks next652/prev656, zeros links, decrements global corpse count and returns new count. No containing free, common-member destruction, main/special model release, voice724 stop or duplicate-unlink guard here; deletion dispatcher owns remaining lifetime stages.
int __cdecl rf_corpse_cleanup_resources_and_unlink(_DWORD *a1)
{
  int v2; // [esp+0h] [ebp-4h]

  rf_string_assign_from_cstr(a1 + 169, (char *)byte_63192A);
  v2 = rf_item_resolve_handle(a1[179]);
  if ( v2 )
  {
    rf_object_mark_for_deferred_delete(v2);
    a1[179] = -1;
  }
  if ( a1[180] )
    rf_burn_effect_release_record((float *)a1[180], 0);
  *(_DWORD *)(a1[164] + 652) = a1[163];
  *(_DWORD *)(a1[163] + 656) = a1[164];
  a1[163] = 0;
  a1[164] = 0;
  return --unk_681AF0;
}

