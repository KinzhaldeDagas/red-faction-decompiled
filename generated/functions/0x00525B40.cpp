// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525B40 rf_inline_pointer_array_append_capacity48
// UNREALRED VERIFIED [decal-projection-20261028]: Inline array count at+0,elements at+4. Rejects only count==48 with-1; otherwise stores supplied pointer at oldcount, increments count, returns oldindex. No count>=48/negative validation, duplicate check or allocation.
int __thiscall rf_inline_pointer_array_append_capacity48(_DWORD *this, int a2)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *this == 48 )
    return -1;
  v3 = (*this)++;
  *(this + v3 + 1) = a2;
  return v3;
}

