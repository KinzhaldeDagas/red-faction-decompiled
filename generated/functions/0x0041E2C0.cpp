// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041E2C0 rf_corpse_resolve_handle_type7
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Cdecl handle. Uses common object resolver, returns resolved pointer only when nonnull and common type DWORD36==7, otherwise0. No flags/health/retiring/protection test, mutation or raw-address interpretation of handle.
int __cdecl rf_corpse_resolve_handle_type7(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_object_resolve_handle(a1);
  if ( v2 && *(_DWORD *)(v2 + 36) == 7 )
    return v2;
  else
    return 0;
}

