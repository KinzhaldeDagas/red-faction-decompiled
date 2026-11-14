// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A7620 rf_text_list_select_previous_or_scroll_up
// UNREALRED VERIFIED [list-selection-20261029]: Empty list no-op. Flag8 invokes0x5A7B00 (scroll previous line/block) instead of changing selection. Otherwise,unless selected==first,moves selected to previous pointer+12,or if no selection finds visible top/bottom entry according to flag0x80. If selected not fully visible,sets scrollY to selected top through clamp/snap helper with snap argument0. Emits virtual+4(event24,-99999) after attempted change,even if visible-entry lookup yieldednull. No reliable boolean return; does not set BYTE+688 here.
char __thiscall rf_text_list_select_previous_or_scroll_up(int *this)
{
  int v1; // eax
  int v2; // eax
  _DWORD *block_at_content_position; // eax

  LOBYTE(v1) = (_BYTE)this - 44;
  if ( (int *)*(this + 183) != this + 181 )
  {
    if ( (*(this + 157) & 8) != 0 )
    {
      LOBYTE(v1) = rf_text_list_scroll_previous_line_or_block(this);
    }
    else
    {
      v1 = *(this + 173);
      if ( v1 != *(this + 183) )
      {
        if ( *(this + 173) )
        {
          *(this + 173) = *(_DWORD *)(*(this + 173) + 12);
        }
        else
        {
          if ( (*(this + 157) & 0x80) != 0 )
          {
            v2 = rf_text_list_inner_height(this);
            block_at_content_position = rf_text_list_find_block_at_content_position(this, 0, *(this + 178) + v2 - 1, 1);
          }
          else
          {
            block_at_content_position = rf_text_list_find_block_at_content_position(this, 0, *(this + 178), 1);
          }
          *(this + 173) = (int)block_at_content_position;
        }
        if ( *(this + 173) && !rf_text_list_block_fully_inside_vertical_view(this, *(this + 173)) )
          rf_text_list_set_scroll_y_with_optional_snap(this, *(_DWORD *)(*(this + 173) + 16), 0);
        LOBYTE(v1) = (*(int (__thiscall **)(int *, int, int))(*this + 4))(this, 24, -99999);
      }
    }
  }
  return v1;
}

