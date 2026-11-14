// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00535780 rf_face_replace_bitmap_handle_if_equal
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): If face DWORD48 equals oldHandle, stores newHandle and returns its bits in EAX; otherwise returns face pointer bits. No UV regeneration or bitmap validation; mixed raw return is incidental.
_DWORD *__thiscall rf_face_replace_bitmap_handle_if_equal(_DWORD *this, int a2, int a3)
{
  _DWORD *result; // eax

  result = this;
  if ( *(this + 12) == a2 )
  {
    *(this + 12) = a3;
    return (_DWORD *)a3;
  }
  return result;
}

