// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525E40 rf_inline_pointer_array_erase_unchecked
// UNREALRED VERIFIED [decal-updates-20261028]: Decrements count unconditionally then shifts inline dword elements left starting caller index (element i at this+4+4*i). No count/index validation, capacity mutation, last-slot clearing or pointee destruction. Invalid/negative index can underwrite; empty container count underflows. Returns this.
_DWORD *__thiscall rf_inline_pointer_array_erase_unchecked(_DWORD *this, int a2)
{
  _DWORD *result; // eax

  --*this;
  while ( 1 )
  {
    result = this;
    if ( a2 >= *this )
      break;
    *(this + a2 + 1) = *(this + a2 + 2);
    ++a2;
  }
  return result;
}

