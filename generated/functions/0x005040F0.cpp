// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005040F0 rf_pointer_array_erase_index_unchecked
// UNREALRED VERIFIED [event-lifecycle-20261028]: Decrements dword count at this+0 unconditionally, then shifts4-byte elements from index+1 to index until index reaches new count. Backing pointer at this+8; capacity at+4 unchanged. Does not validate index/count, free pointees, or clear old last slot. Empty count or invalid index can corrupt container state; caller must enforce validity.
_DWORD *__thiscall rf_pointer_array_erase_index_unchecked(_DWORD *this, int a2)
{
  _DWORD *result; // eax

  --*this;
  while ( 1 )
  {
    result = this;
    if ( a2 >= *this )
      break;
    *(_DWORD *)(*(this + 2) + 4 * a2) = *(_DWORD *)(*(this + 2) + 4 * a2 + 4);
    ++a2;
  }
  return result;
}

