// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00415D20 rf_clutter_find_by_uid
// UNREALRED VERIFIED [switch-clutter-reset] Resolves a common object UID and returns it only when runtime object type +0x24 is clutter type 4.
int __cdecl rf_clutter_find_by_uid(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_object_resolve_handle(a1);
  if ( v2 && *(_DWORD *)(v2 + 36) == 4 )
    return v2;
  else
    return 0;
}

