// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A8C60 rf_text_list_set_scroll_x_fraction
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Recovered code0x5A8C60..0x5A8CCE. Thiscall list,float fraction,unused DWORD. Ordered fraction clamps0..1. Range=max(contentWidth+680-innerWidth,0);stores scrollX+708=truncate(range*fraction),returns stored integer. Callee pops8 stack bytes although second DWORD is unused. Does NOT invoke general X setter,update scrollbar position,notify or mark BYTE+688. NaN not explicitly rejected by comparisons.
int __thiscall rf_text_list_set_scroll_x_fraction(void *list, float fraction, int unused)
{
  int result; // eax
  int v5; // [esp+4h] [ebp-4h]

  if ( fraction >= 0.0 )
  {
    if ( fraction > 1.0 )
      fraction = 1.0;
  }
  else
  {
    fraction = 0.0;
  }
  v5 = *((_DWORD *)list + 170) - rf_text_list_inner_width(list);
  if ( v5 < 0 )
    v5 = 0;
  result = (int)((double)v5 * fraction);
  *((_DWORD *)list + 177) = result;
  return result;
}

