// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A5E50 rf_text_list_first_block_ending_after_y
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall list,Y. Empty or Y>=content height returnsNULL. Scans first block with topY+height>Y,ignores lower bound and gaps; negative Y is allowed. No X test,scroll translation or state mutation.
_DWORD *__thiscall rf_text_list_first_block_ending_after_y(_DWORD *this, int a2)
{
  _DWORD *i; // [esp+4h] [ebp-4h]

  if ( (_DWORD *)*(this + 183) == this + 181 )
    return nullptr;
  if ( a2 >= *(this + 171) )
    return nullptr;
  for ( i = (_DWORD *)*(this + 183); i != this + 181; i = (_DWORD *)i[2] )
  {
    if ( i[6] + i[4] > a2 )
      return i;
  }
  return nullptr;
}

