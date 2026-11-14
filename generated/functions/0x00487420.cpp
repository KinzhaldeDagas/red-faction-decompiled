// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00487420 rf_mover_find_by_saved_identifier
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Walk mover list0x70489C until sentinel0x704610 following owner+0x28C; return first record whose saved id+0x20 equals input or0. Distinct from full runtime-handle resolver and from mover key-array index lookup.
int __cdecl rf_mover_find_by_saved_identifier(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = unk_70489C; (_UNKNOWN *)i != &unk_704610; i = *(_DWORD *)(i + 652) )
  {
    if ( *(_DWORD *)(i + 32) == a1 )
      return i;
  }
  return 0;
}

