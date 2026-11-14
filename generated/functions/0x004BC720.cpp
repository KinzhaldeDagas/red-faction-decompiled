// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BC720 rf_object_runtime_identifier_to_saved_identifier
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Resolve full runtime identifier using rf_object_resolve_handle; return common-object dword+0x20 on hit, else-1. Used for event activation-context packing. Does not serialize low16-bit slot alone or preserve unresolved runtime identifier.
int __cdecl rf_object_runtime_identifier_to_saved_identifier(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_object_resolve_handle(a1);
  if ( v2 )
    return *(_DWORD *)(v2 + 32);
  else
    return -1;
}

