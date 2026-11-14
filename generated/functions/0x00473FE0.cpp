// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00473FE0 rf_item_resolve_handle
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Resolve full common identifier with rf_object_resolve_handle; return only non-null record whose runtime type+0x24==1, otherwise0. No identifier-list scan, definition lookup, or allocation.
int __cdecl rf_item_resolve_handle(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_object_resolve_handle(a1);
  if ( v2 && *(_DWORD *)(v2 + 36) == 1 )
    return v2;
  else
    return 0;
}

