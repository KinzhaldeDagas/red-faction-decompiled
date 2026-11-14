// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A7D20 rf_text_list_scroll_next_line_or_block
// UNREALRED VERIFIED [list-selection-20261029]: Empty or last entry fully visible no-op. Flag0x80 bottom mode locates first block ending after viewport bottom;flag0x10 targets its bottom,otherwise computed line bottom,then subtracts viewport height and calls Y setter snap0. Lookup failure uses last block bottom. Non-bottom mode simply requests scrollY+1 with snap1. No selection or notification; setter controls bounds/snap behavior.
char __thiscall rf_text_list_scroll_next_line_or_block(int *this)
{
  char result; // al
  int v2; // eax
  int v3; // esi
  int v4; // eax
  int v5; // esi
  int v6; // eax
  int v7; // eax
  int v9; // [esp+8h] [ebp-8h]
  int *block_ending_after_y; // [esp+Ch] [ebp-4h]

  result = (_BYTE)this - 44;
  if ( (int *)*(this + 183) != this + 181 )
  {
    result = rf_text_list_block_fully_inside_vertical_view(this, *(this + 184));
    if ( !result )
    {
      if ( (*(this + 157) & 0x80) != 0 )
      {
        v2 = rf_text_list_inner_height(this);
        block_ending_after_y = rf_text_list_first_block_ending_after_y(this, *(this + 178) + v2);
        if ( block_ending_after_y )
        {
          if ( (*(this + 157) & 0x10) != 0 )
          {
            v5 = block_ending_after_y[6] + block_ending_after_y[4];
          }
          else
          {
            v7 = rf_text_list_inner_height(this);
            v9 = rf_text_block_line_index_from_y_with_gap_bias(block_ending_after_y, *(this + 178) + v7);
            v5 = rf_text_block_line_bottom_y(block_ending_after_y, v9);
          }
          v6 = rf_text_list_inner_height(this);
          return rf_text_list_set_scroll_y_with_optional_snap(this, v5 - v6, 0);
        }
        else
        {
          v3 = *(_DWORD *)(*(this + 184) + 24) + *(_DWORD *)(*(this + 184) + 16);
          v4 = rf_text_list_inner_height(this);
          return rf_text_list_set_scroll_y_with_optional_snap(this, v3 - v4, 0);
        }
      }
      else
      {
        return rf_text_list_set_scroll_y_with_optional_snap(this, *(this + 178) + 1, 1);
      }
    }
  }
  return result;
}

