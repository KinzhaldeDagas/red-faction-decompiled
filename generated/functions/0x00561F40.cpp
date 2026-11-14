// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561F40 sub_561F40
// UNREALRED VERIFIED [original-shadow-root-20261027] Model anchor lookup: for render type 2, scans definition bone records in source order (count +72, stride 76, parent at +148) and returns the first signed-negative parent index; other model types or no parentless bone return -1. Object model binding 0x4BC000 stores this result at Object+620. It is not an averaged root or capsule base.
int __thiscall sub_561F40(_DWORD *this)
{
  int i; // [esp+4h] [ebp-8h]
  int v3; // [esp+8h] [ebp-4h]

  if ( *this == 2 )
  {
    v3 = *(this + 2);
    for ( i = 0; i < *(_DWORD *)(v3 + 72); ++i )
    {
      if ( *(int *)(v3 + 76 * i + 148) < 0 )
        return i;
    }
  }
  return -1;
}

