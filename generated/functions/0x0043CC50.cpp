// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043CC50 rf_inline_pointer_array_find_first
// UNREALRED VERIFIED [decal-face-links-20261028]: Inline container count at+0,elements at+4+4*i. Returns first exact dword/pointer match or-1; no pointee comparison, mutation, validity or capacity checks.
int __thiscall rf_inline_pointer_array_find_first(_DWORD *this, int a2)
{
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < *this; ++i )
  {
    if ( *(this + i + 1) == a2 )
      return i;
  }
  return -1;
}

