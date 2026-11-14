// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048A500 rf_moving_solid_resolve_handle
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mover UID and handle queries, detachment and member ownership, original console packet serialization, native team-byte sentinel and authority comparisons): 
// Cdecl full object handle. Delegates full identifier-table lookup, then requires resolved common typeDWORD36 EXACT9; returns pointer orNULL. No UID lookup, subtype flag check,
// geometry-pointer validation or allocation. Called by mover activation path.
int __cdecl rf_moving_solid_resolve_handle(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_object_resolve_handle(a1);
  if ( v2 && *(_DWORD *)(v2 + 36) == 9 )
    return v2;
  else
    return 0;
}

