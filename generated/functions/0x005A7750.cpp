// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A7750 rf_text_list_select_next_or_scroll_down
// UNREALRED VERIFIED [list-selection-20261029]: Empty list no-op. Flag8 delegates0x5A7D20. Otherwise,unless selected==last,moves selected to next+8,or initializes from visible edge(flag0x80 chooses bottom). Nonvisible selection is revealed using selected bottom-innerHeight through Y setter,snap0. Emits virtual+4(event24,-99999). No explicit list membership guard or common success return; no BYTE+688 update here.
char __thiscall rf_text_list_select_next_or_scroll_down(int *this)
{
  int v1; // eax
  int v2; // eax
  _DWORD *block_at_content_position; // eax
  int v4; // esi
  int v5; // eax

  LOBYTE(v1) = (_BYTE)this - 44;
  if ( (int *)*(this + 183) != this + 181 )
  {
    if ( (*(this + 157) & 8) != 0 )
    {
      LOBYTE(v1) = rf_text_list_scroll_next_line_or_block(this);
    }
    else
    {
      v1 = *(this + 173);
      if ( v1 != *(this + 184) )
      {
        if ( *(this + 173) )
        {
          *(this + 173) = *(_DWORD *)(*(this + 173) + 8);
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
        {
          v4 = *(_DWORD *)(*(this + 173) + 24) + *(_DWORD *)(*(this + 173) + 16);
          v5 = rf_text_list_inner_height(this);
          rf_text_list_set_scroll_y_with_optional_snap(this, v4 - v5, 0);
        }
        LOBYTE(v1) = (*(int (__thiscall **)(int *, int, int))(*this + 4))(this, 24, -99999);
      }
    }
  }
  return v1;
}

