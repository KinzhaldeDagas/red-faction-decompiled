// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C0B0 sub_43C0B0
// UNREALRED VERIFIED [combat-panic-movement-20261111]: Carried-body disposal resolves Entity+75C through41E2C0. Only a resolved corpse is marked for deferred deletion, followed by handle=-1,4344D0(1), and Entity+514 deadline500ms. Unresolved retained nonnegative handles remain retained and still force slow mode in4344D0.
void __cdecl sub_43C0B0(int a1)
{
  int v1; // [esp+0h] [ebp-4h]

  if ( a1 )
  {
    v1 = rf_corpse_resolve_handle_type7(*(_DWORD *)(a1 + 1884));
    if ( v1 )
    {
      rf_object_mark_for_deferred_delete(v1);
      *(_DWORD *)(a1 + 1884) = -1;
      sub_4344D0(a1, 1);
      rf_replicator_arm_milliseconds((int *)(a1 + 1300), 500);
    }
  }
}

