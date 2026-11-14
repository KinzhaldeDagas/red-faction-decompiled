// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A87B0 rf_text_list_set_scroll_x
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall list,signed requested X. Caps to contentWidth-innerWidth then clamps negative to0,stores scrollX+708. If horizontal scrollbar+788 exists,sets its position via0x5EEA50;otherwise returns this. Does not relayout text,notify selection or read bar range.
_DWORD *__thiscall rf_text_list_set_scroll_x(_DWORD *this, int a2)
{
  _DWORD *result; // eax

  if ( a2 > *(this + 170) - rf_text_list_inner_width(this) )
    a2 = *(this + 170) - rf_text_list_inner_width(this);
  if ( a2 < 0 )
    a2 = 0;
  result = this;
  *(this + 177) = a2;
  if ( *(this + 197) )
    return rf_scrollbar_set_position_unclamped((_DWORD *)*(this + 197), *(this + 177));
  return result;
}

