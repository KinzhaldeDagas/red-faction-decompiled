// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A5D20 rf_text_list_find_block_at_content_position
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall list,X,Y,allow-gap byte. Empty returnsNULL. Requires0<=X<contentWidth+680 and Y<contentHeight+684. Y>=0 scans first node with Y<node.top+height AND(Y>=node.top OR allow-gap). Gap mode therefore picks next block spanning upper bound even if Y below its top. Negative Y returns first block only in gap mode. X checked only against overall content width,not individual block width. No scroll translation or mutation.
_DWORD *__thiscall rf_text_list_find_block_at_content_position(_DWORD *this, int a2, int a3, char a4)
{
  _DWORD *i; // [esp+4h] [ebp-4h]

  if ( (_DWORD *)*(this + 183) == this + 181 )
    return nullptr;
  if ( a2 < 0 || a2 >= *(this + 170) || a3 >= *(this + 171) )
    return nullptr;
  if ( a3 >= 0 )
  {
    for ( i = (_DWORD *)*(this + 183); i != this + 181; i = (_DWORD *)i[2] )
    {
      if ( (a3 >= i[4] || a4) && a3 < i[6] + i[4] )
        return i;
    }
    return nullptr;
  }
  else if ( a4 )
  {
    return (_DWORD *)*(this + 183);
  }
  else
  {
    return nullptr;
  }
}

