// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D6A0 rf_integer_clamp_in_place
// UNREALRED VERIFIED [item-pickups-20261028]: Signed in-place clamp. If *value<lower, writes lower and exits; otherwise if *value>upper writes upper. Does not normalize reversed bounds. Return register is inconsistent pointer/lower value across branches, not a reliable pointer/status contract.
_DWORD *__cdecl rf_integer_clamp_in_place(_DWORD *a1, int a2, int a3)
{
  _DWORD *result; // eax

  result = a1;
  if ( *a1 >= a2 )
  {
    if ( *a1 > a3 )
    {
      *a1 = a3;
      return a1;
    }
  }
  else
  {
    *a1 = a2;
    return (_DWORD *)a2;
  }
  return result;
}

