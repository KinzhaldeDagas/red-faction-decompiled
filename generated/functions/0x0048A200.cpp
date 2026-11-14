// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048A200 rf_mover_resolve_handle
// UNREALRED VERIFIED [mission-mover-layout-20261013] Typed common-handle resolver accepts only common type 8. Authored moving-group UID corresponds to the first key UID assigned at 0x487630; later key UIDs do not independently identify additional common movers.
int __cdecl rf_mover_resolve_handle(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_object_resolve_handle(a1);
  if ( v2 && *(_DWORD *)(v2 + 36) == 8 )
    return v2;
  else
    return 0;
}

