// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437A50 rf_entity_mark_owned_flag40_projectiles
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled action packet15/16/20/28/36/46/47 registry, consumed source arguments, ownership, reload ordering and
// projectile traversal): Cdecl entity, bool AL. NULL entity ->AL0. Otherwise scan full projectile list911F74/sentinel911CE8, next652; for each node ownerDWORD48==entity.handle44,
// dereference node class pointer660 unguarded and require classDWORD612 mask40. Set node float668 exactly-1.0 (PE631048), mark result1; continue all nodes. Return AL1 iff any match,
// else0. No exact weapon-registry-ID filter, runtime/authority/alive check, byteflag or list mutation in this helper. Native body sets a float; immediate explosion/deletion is not
// performed here. Called repeatedly by packet36 receiver for its narrower remote-charge-ID matches.
char __cdecl rf_entity_mark_owned_flag40_projectiles(int a1)
{
  char v2; // [esp+3h] [ebp-5h]
  int i; // [esp+4h] [ebp-4h]

  if ( !a1 )
    return 0;
  v2 = 0;
  for ( i = dword_911F74; (_UNKNOWN *)i != &unk_911CE8; i = *(_DWORD *)(i + 652) )
  {
    if ( *(_DWORD *)(i + 48) == *(_DWORD *)(a1 + 44) && (*(_DWORD *)(*(_DWORD *)(i + 660) + 612) & 0x40) != 0 )
    {
      *(float *)(i + 668) = -1.0;
      v2 = 1;
    }
  }
  return v2;
}

