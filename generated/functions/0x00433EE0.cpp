// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00433EE0 rf_entity_resolve_handle
// Resolves an object identifier through the shared object table and returns the record only when it is non-null and runtime type dword +0x24 is zero.
// UNREALRED VERIFIED [ai-set-mode-event-20260826]: Set_AI_Mode uses this entity-only identifier resolver for both direct and attached targets. A resolved event or any non-type-0 object returns null, so target events are ignored rather than recursively activated.
int __cdecl rf_entity_resolve_handle(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_object_resolve_handle(a1);
  if ( !v2 || *(_DWORD *)(v2 + 36) )
    return 0;
  else
    return v2;
}

