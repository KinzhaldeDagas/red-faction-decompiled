// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00487EB0 rf_mover_clear_linked_object_physics_flag
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL volume/decal layouts, cumulative corner room queries, mover list and auxiliary-node ownership, linked physics flags and native debug draw arguments): 
// Cdecl mover pointer. Scans handle arrays716 FIRST,then704, resolving every handle through full identifier-table resolver. For each valid object clears bit0x10000000 in DWORD424,
// preserving all other bits. Missing/stale handles skipped; duplicate handles may be visited repeatedly. No array clear, handle deletion, child unlink, movement or flag set on mover
// itself. Normal EAX is second array count from final loop test, not Boolean.
int __cdecl rf_mover_clear_linked_object_physics_flag(int a1)
{
  int *v1; // eax
  int result; // eax
  int *v3; // eax
  int v4; // [esp+0h] [ebp-8h]
  int v5; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]
  int j; // [esp+4h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 716)); ++i )
  {
    v1 = (int *)sub_552200((_DWORD *)(a1 + 716), i);
    v4 = rf_object_resolve_handle(*v1);
    if ( v4 )
      *(_DWORD *)(v4 + 424) &= ~0x10000000u;
  }
  for ( j = 0; ; ++j )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 704));
    if ( j >= result )
      break;
    v3 = (int *)sub_552200((_DWORD *)(a1 + 704), j);
    v5 = rf_object_resolve_handle(*v3);
    if ( v5 )
      *(_DWORD *)(v5 + 424) &= ~0x10000000u;
  }
  return result;
}

