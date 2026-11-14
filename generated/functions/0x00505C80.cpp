// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00505C80 rf_trigger_find_by_uid
// UNREALRED VERIFIED [hud-world-targets] Scans the runtime trigger list and returns the trigger whose common-object UID matches the requested identifier.
int __cdecl rf_trigger_find_by_uid(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_object_resolve_handle(a1);
  if ( v2 && *(_DWORD *)(v2 + 36) == 5 )
    return v2;
  else
    return 0;
}

