// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A79C0 rf_text_list_page_select_next
// UNREALRED VERIFIED [list-selection-20261029]: Empty no-op. Existing selection intersecting view first triggers page-scroll-down0x5A8160. If selected height<=viewport,looks up at min(selected.top+innerHeight,contentHeight-1),X0,gap mode,notifies24 if pointer differs. Oversized entry instead takes selected.next when nonnull and notifies24;NO sentinel comparison,so final oversized entry can select sentinel. Sets BYTE+688=1. No selection delegates page-scroll-down; no common status return.
_DWORD *__thiscall rf_text_list_page_select_next(int this)
{
  _DWORD *result; // eax
  int v2; // esi
  int v3; // esi
  _DWORD *block_at_content_position; // [esp+8h] [ebp-8h]
  int v6; // [esp+Ch] [ebp-4h]

  result = (_DWORD *)(this + 724);
  if ( *(_DWORD *)(this + 732) != this + 724 )
  {
    if ( *(_DWORD *)(this + 692) )
    {
      if ( rf_text_list_block_intersects_vertical_view((_DWORD *)this, *(_DWORD *)(this + 692)) )
        rf_text_list_scroll_page_down(this);
      v2 = *(_DWORD *)(this + 692);
      if ( *(_DWORD *)(v2 + 24) <= rf_text_list_inner_height((_DWORD *)this) )
      {
        v3 = *(_DWORD *)(this + 692);
        v6 = *(_DWORD *)(v3 + 16) + rf_text_list_inner_height((_DWORD *)this);
        if ( v6 > *(_DWORD *)(this + 684) - 1 )
          v6 = *(_DWORD *)(this + 684) - 1;
        block_at_content_position = rf_text_list_find_block_at_content_position((_DWORD *)this, 0, v6, 1);
        if ( *(_DWORD **)(this + 692) != block_at_content_position )
        {
          *(_DWORD *)(this + 692) = block_at_content_position;
          (*(void (__thiscall **)(int, int, int))(*(_DWORD *)this + 4))(this, 24, -99999);
        }
      }
      else if ( *(_DWORD *)(*(_DWORD *)(this + 692) + 8) )
      {
        *(_DWORD *)(this + 692) = *(_DWORD *)(*(_DWORD *)(this + 692) + 8);
        (*(void (__thiscall **)(int, int, int))(*(_DWORD *)this + 4))(this, 24, -99999);
      }
      *(_BYTE *)(this + 688) = 1;
      return (_DWORD *)this;
    }
    else
    {
      return rf_text_list_scroll_page_down(this);
    }
  }
  return result;
}

