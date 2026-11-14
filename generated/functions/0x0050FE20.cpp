// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050FE20 rf_projectile_resolve_uid_type2
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Resolves generic object UID via40CE70, returns pointer only when non-NULL and runtime DWORD+36 equals2; otherwise NULL. No weapon-index lookup or mutation.
int __cdecl rf_projectile_resolve_uid_type2(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_object_resolve_handle(a1);
  if ( v2 && *(_DWORD *)(v2 + 36) == 2 )
    return v2;
  else
    return 0;
}

