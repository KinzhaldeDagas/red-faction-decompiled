// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A8830 rf_text_list_set_scroll_y_with_optional_snap
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall list,signed requested Y (misinferred pointer),snap byte. Caps to contentHeight-innerHeight then clamps to0. Flags+628 bit0x80 repeats upper cap (can reintroduce negative maximum). If flag0x20 CLEAR,forces snap true;otherwise honors input snap. Snap chooses bottom-alignment0x5A8AB0 for bit0x80,top-alignment0x5A8980 otherwise. With bit0x20 set,reclamps max then min0 after snapping;without it,no final clamp here. Stores scrollY+712,updates vertical scrollbar+784 position if present. Return branch-dependent position/helper pointer,not success boolean.
_DWORD *__thiscall rf_text_list_set_scroll_y_with_optional_snap(int *this, _DWORD *a2, char a3)
{
  _DWORD *result; // eax

  if ( (int)a2 > *(this + 171) - rf_text_list_inner_height(this) )
    a2 = (_DWORD *)(*(this + 171) - rf_text_list_inner_height(this));
  if ( (int)a2 < 0 )
    a2 = nullptr;
  if ( (*(this + 157) & 0x80) != 0 && (int)a2 > *(this + 171) - rf_text_list_inner_height(this) )
    a2 = (_DWORD *)(*(this + 171) - rf_text_list_inner_height(this));
  if ( (*(this + 157) & 0x20) == 0 )
    a3 = 1;
  if ( a3 )
  {
    if ( (*(this + 157) & 0x80) != 0 )
      a2 = (_DWORD *)rf_text_list_snap_scroll_to_line_bottom(this, (int)a2);
    else
      a2 = (_DWORD *)rf_text_list_snap_scroll_to_line_top(this, (int)a2);
  }
  if ( (*(this + 157) & 0x20) != 0 )
  {
    if ( (int)a2 > *(this + 171) - rf_text_list_inner_height(this) )
      a2 = (_DWORD *)(*(this + 171) - rf_text_list_inner_height(this));
    if ( (int)a2 < 0 )
      a2 = nullptr;
  }
  result = a2;
  *(this + 178) = (int)a2;
  if ( *(this + 196) )
    return rf_scrollbar_set_position_unclamped((_DWORD *)*(this + 196), *(this + 178));
  return result;
}

