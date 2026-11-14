// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525C50 rf_inline_pointer_array_append_capacity128
// UNREALRED VERIFIED [decal-projection-20261028]: Inline array count at+0,elements at+4. Rejects only count==128 with-1; otherwise stores supplied pointer at oldcount, increments count, returns oldindex. No count>=128/negative validation, duplicate check or allocation.
int __thiscall rf_inline_pointer_array_append_capacity128(_DWORD *this, int a2)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *this == 128 )
    return -1;
  v3 = (*this)++;
  *(this + v3 + 1) = a2;
  return v3;
}

