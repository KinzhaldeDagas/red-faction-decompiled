// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525B90 rf_inline_pointer_array_append_unique_capacity48
// UNREALRED VERIFIED [decal-face-links-20261028]: Looks up exact dword value/pointer using0x43CC50. Existing index>=0 returned; absent appends through capacity48 helper0x525B40, returning index or-1. No allocation or ownership transfer; inherits equality-only count==48 capacity guard.
int __thiscall rf_inline_pointer_array_append_unique_capacity48(_DWORD *this, int a2)
{
  int first; // [esp+4h] [ebp-4h]

  first = rf_inline_pointer_array_find_first(this, a2);
  if ( first >= 0 )
    return first;
  else
    return rf_inline_pointer_array_append_capacity48(this, a2);
}

