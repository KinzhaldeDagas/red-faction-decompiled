// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00435170 sub_435170
// UNREALRED VERIFIED [combat-reaction-20261111]: Walks owner+8CC pointer-array records in source order (8-byte records), returning the first record+4 identifier that is not-1; no later-child scan after a non-(-1) identifier fails entity resolution.40B6D0 calls this whole operation twice on its zero-MaxVel path.
int __cdecl sub_435170(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 2252)); ++i )
  {
    if ( *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(a1 + 2252), i) + 4) != -1 )
      return *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(a1 + 2252), i) + 4);
  }
  return -1;
}

