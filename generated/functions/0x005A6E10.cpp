// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A6E10 rf_text_list_select_entry_optional_reveal
// UNREALRED VERIFIED [list-selection-20261029]: Thiscall list,entry pointer,reveal byte. Stores selected+692 immediately. Reveal nonzero and entry not fully in vertical view sets scrollY RAW: flag0x80 aligns entry bottom to inner viewport bottom,else aligns entry top. Updates vertical scrollbar position if present. No null/membership guard,clamping,snapping,selection notification or dirty BYTE+688 update. Return can be this,visibility byte or scrollbar helper result.
_DWORD *__thiscall rf_text_list_select_entry_optional_reveal(_DWORD *this, int a2, char a3)
{
  _DWORD *result; // eax
  int v4; // esi
  int v5; // esi

  result = this;
  *(this + 173) = a2;
  if ( a3 )
  {
    LOBYTE(result) = rf_text_list_block_fully_inside_vertical_view(this, *(this + 173));
    if ( !(_BYTE)result )
    {
      if ( (*(this + 157) & 0x80) != 0 )
      {
        v4 = *(_DWORD *)(*(this + 173) + 24) + *(_DWORD *)(*(this + 173) + 16);
        v5 = v4 - rf_text_list_inner_height(this);
        result = this;
        *(this + 178) = v5;
      }
      else
      {
        result = this;
        *(this + 178) = *(_DWORD *)(*(this + 173) + 16);
      }
      if ( *(this + 196) )
        return rf_scrollbar_set_position_unclamped((_DWORD *)*(this + 196), *(this + 178));
    }
  }
  return result;
}

