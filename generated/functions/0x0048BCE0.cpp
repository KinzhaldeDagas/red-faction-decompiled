// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048BCE0 rf_mover_collect_child_contributor
// UNREALRED VERIFIED [mission-mover-geometry-20261013] Collects one row per child handle with a contributor count and ordered mover pointers; repeated child references append contributors rather than replacing the preceding owner. Dirty marker derives from mover flags 0x80000008. Retail captured link corpus has 770 solid edges for 762 type9 solids, including eight solids with two contributors.
int *__cdecl rf_mover_collect_child_contributor(int *a1, int a2, int a3, int a4)
{
  int *result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < *a1; ++i )
  {
    if ( *(_DWORD *)(a2 + 24 * i) == a4 )
    {
      *(_DWORD *)(a2 + 24 * i + 4 * (unsigned __int8)(*(_BYTE *)(a2 + 24 * i + 4))++ + 8) = a3;
      if ( (*(_DWORD *)(a3 + 792) & 0x80000008) != 0 )
        ++*(_BYTE *)(a2 + 24 * i + 5);
      break;
    }
  }
  result = a1;
  if ( i == *a1 )
  {
    *(_DWORD *)(a2 + 24 * *a1) = a4;
    *(_DWORD *)(a2 + 24 * *a1 + 8) = a3;
    *(_BYTE *)(a2 + 24 * *a1 + 4) = 1;
    *(_BYTE *)(a2 + 24 * *a1 + 5) = 0;
    if ( (*(_DWORD *)(a3 + 792) & 0x80000008) != 0 )
      ++*(_BYTE *)(a2 + 24 * i + 5);
    result = (int *)(*a1 + 1);
    *a1 = (int)result;
  }
  return result;
}

