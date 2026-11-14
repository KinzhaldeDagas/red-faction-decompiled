// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C0180 rf_intrusive_slist_remove_search_unchecked_count
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Thiscall header,target,RET4. Decrements count UNCONDITIONALLY before search, even absent target or empty list. Head match advances header.head but DOES NOT clear removed head.next; nonhead search finds predecessor, relinks and clears target.next. Missing target leaves links unchanged while count remains decremented and returns original head bits (or0). No ownership/null-target/underflow protection, allocation or free. This distinction matters for pair free/active list accounting.
_DWORD *__thiscall rf_intrusive_slist_remove_search_unchecked_count(_DWORD *this, _DWORD *a2)
{
  _DWORD *result; // eax
  _DWORD *i; // [esp+4h] [ebp-4h]

  --*(this + 1);
  if ( (_DWORD *)*this == a2 )
  {
    *this = *a2;
    return a2;
  }
  else
  {
    result = (_DWORD *)*this;
    for ( i = (_DWORD *)*this; i; i = (_DWORD *)*i )
    {
      if ( (_DWORD *)*i == a2 )
      {
        *i = *a2;
        *a2 = 0;
        return a2;
      }
    }
  }
  return result;
}

