// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A5BD0 rf_text_list_sync_vertical_scrollbar_extent
// UNREALRED VERIFIED [text-layout-20261029]: If vertical scrollbar pointer list+784 nonnull,gets content height+684 through0x5A90D0 and calls0x5EEF10. Null returns this; otherwise helper result. Updates range/thumb extent,not scrollY or scrollbar position.
_DWORD *__thiscall rf_text_list_sync_vertical_scrollbar_extent(_DWORD *this)
{
  _DWORD *result; // eax
  int content_height; // eax

  result = this;
  if ( *(this + 196) )
  {
    content_height = rf_text_list_get_content_height(this);
    return (_DWORD *)rf_scrollbar_set_total_extent((_DWORD *)*(this + 196), content_height);
  }
  return result;
}

