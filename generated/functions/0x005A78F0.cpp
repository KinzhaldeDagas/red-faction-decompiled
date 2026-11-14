// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A78F0 rf_text_list_page_select_previous
// UNREALRED VERIFIED [list-selection-20261029]: Empty no-op. With selected entry:if it intersects current view,first calls page-scroll-up0x5A7E60. Looks up block at max(selected.top-innerHeight,0),X0,gap mode;changes selected and emits24 only if pointer differs;sets BYTE+688=1 regardless difference. Without selection delegates page-scroll-up. Does not use select/reveal helper or explicitly sync scrollbar position; return incidental.
_DWORD *__thiscall rf_text_list_page_select_previous(int this)
{
  _DWORD *result; // eax
  int v2; // esi
  _DWORD *block_at_content_position; // [esp+8h] [ebp-8h]
  int v5; // [esp+Ch] [ebp-4h]

  result = (_DWORD *)(this + 724);
  if ( *(_DWORD *)(this + 732) != this + 724 )
  {
    if ( *(_DWORD *)(this + 692) )
    {
      if ( rf_text_list_block_intersects_vertical_view((_DWORD *)this, *(_DWORD *)(this + 692)) )
        rf_text_list_scroll_page_up(this);
      v2 = *(_DWORD *)(this + 692);
      v5 = *(_DWORD *)(v2 + 16) - rf_text_list_inner_height((_DWORD *)this);
      if ( v5 < 0 )
        v5 = 0;
      block_at_content_position = rf_text_list_find_block_at_content_position((_DWORD *)this, 0, v5, 1);
      result = (_DWORD *)this;
      if ( *(_DWORD **)(this + 692) != block_at_content_position )
      {
        *(_DWORD *)(this + 692) = block_at_content_position;
        result = (_DWORD *)(*(int (__thiscall **)(int, int, int))(*(_DWORD *)this + 4))(this, 24, -99999);
      }
      *(_BYTE *)(this + 688) = 1;
    }
    else
    {
      return rf_text_list_scroll_page_up(this);
    }
  }
  return result;
}

