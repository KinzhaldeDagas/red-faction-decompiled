// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00434C10 rf_entity_any_attached_child_has_player_flag
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(required owner), canonicalAL0/1. Signed i=0..<count firstDWORD(owner+2252), re-read count each test. Unchecked pointer-array element->relation
// DWORD4 full handle is resolved as COMMON. Skip missing objects; first nonNULL object whose common flags DWORD124 has mask0x2000 returnsAL1, regardless of runtime type, relation
// key, alive state or reciprocal parent equality. Exhaustion returnsAL0. No own NULL/entry guard or writes; not a test of owner player flag or only direct ENTITY children.
char __cdecl rf_entity_any_attached_child_has_player_flag(int a1)
{
  int v1; // eax
  int v3; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 2252)); ++i )
  {
    v1 = sub_552200((_DWORD *)(a1 + 2252), i);
    v3 = rf_object_resolve_handle(*(_DWORD *)(*(_DWORD *)v1 + 4));
    if ( v3 && (*(_DWORD *)(v3 + 124) & 0x2000) != 0 )
      return 1;
  }
  return 0;
}

