// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A5C00 rf_text_list_sync_horizontal_scrollbar_extent
// UNREALRED VERIFIED [text-layout-20261029]: If horizontal scrollbar pointer list+788 nonnull,gets content width+680 through0x5A90B0 and calls0x5EEF10. Does not update scrollX or clamp existing scrollbar position. Return path this/helper pointer.
_DWORD *__thiscall rf_text_list_sync_horizontal_scrollbar_extent(_DWORD *this)
{
  _DWORD *result; // eax
  int content_width; // eax

  result = this;
  if ( *(this + 197) )
  {
    content_width = rf_text_list_get_content_width(this);
    return (_DWORD *)rf_scrollbar_set_total_extent((_DWORD *)*(this + 197), content_width);
  }
  return result;
}

