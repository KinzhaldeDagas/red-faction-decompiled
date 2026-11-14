// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A7B00 rf_text_list_scroll_previous_line_or_block
// UNREALRED VERIFIED [list-selection-20261029]: Empty or first entry fully visible returns without movement. Flag0x80 bottom-oriented mode locates block at viewport bottom-1;flag0x10 moves to previous block bottom,otherwise previous line bottom using biased index and line-bottom helper. Fallback last block bottom if lookup fails. Non-bottom mode finds block starting at/before scrollY-1;flag0x10 selects its top,otherwise corresponding line top;no block falls back first.top. Calls Y setter with snap0,which may force snapping based on flags. Does not change selected or notify; return low byte incidental.
char __thiscall rf_text_list_scroll_previous_line_or_block(int *this)
{
  int v1; // eax
  int v2; // eax
  int v3; // esi
  int v4; // eax
  int v5; // esi
  int v6; // eax
  int v7; // eax
  int v8; // esi
  int v9; // eax
  int v10; // esi
  int v11; // eax
  int v12; // eax
  int v15; // [esp+8h] [ebp-Ch]
  int *block_ending_after_y; // [esp+10h] [ebp-4h]
  int *block_starting_at_or_before_y; // [esp+10h] [ebp-4h]

  LOBYTE(v1) = (_BYTE)this - 44;
  if ( (int *)*(this + 183) != this + 181 )
  {
    LOBYTE(v1) = rf_text_list_block_fully_inside_vertical_view(this, *(this + 183));
    if ( !(_BYTE)v1 )
    {
      if ( (*(this + 157) & 0x80) != 0 )
      {
        v2 = rf_text_list_inner_height(this);
        block_ending_after_y = rf_text_list_first_block_ending_after_y(this, *(this + 178) + v2 - 1);
        if ( block_ending_after_y )
        {
          v1 = *(this + 157) & 0x10;
          if ( v1 )
          {
            if ( block_ending_after_y != (int *)*(this + 183) )
            {
              v5 = *(_DWORD *)(block_ending_after_y[3] + 24) + *(_DWORD *)(block_ending_after_y[3] + 16);
              v6 = rf_text_list_inner_height(this);
              LOBYTE(v1) = rf_text_list_set_scroll_y_with_optional_snap(this, v5 - v6, 0);
            }
          }
          else
          {
            v7 = rf_text_list_inner_height(this);
            v1 = rf_text_block_line_index_from_y_with_gap_bias(block_ending_after_y, *(this + 178) + v7 - 1);
            if ( v1 )
            {
              v10 = rf_text_block_line_bottom_y(block_ending_after_y, v1 - 1);
              v11 = rf_text_list_inner_height(this);
              LOBYTE(v1) = rf_text_list_set_scroll_y_with_optional_snap(this, v10 - v11, 0);
            }
            else if ( block_ending_after_y != (int *)*(this + 183) )
            {
              v8 = *(_DWORD *)(block_ending_after_y[3] + 24) + *(_DWORD *)(block_ending_after_y[3] + 16);
              v9 = rf_text_list_inner_height(this);
              LOBYTE(v1) = rf_text_list_set_scroll_y_with_optional_snap(this, v8 - v9, 0);
            }
          }
        }
        else
        {
          v3 = *(_DWORD *)(*(this + 184) + 24) + *(_DWORD *)(*(this + 184) + 16);
          v4 = rf_text_list_inner_height(this);
          LOBYTE(v1) = rf_text_list_set_scroll_y_with_optional_snap(this, v3 - v4, 0);
        }
      }
      else
      {
        block_starting_at_or_before_y = (int *)rf_text_list_last_block_starting_at_or_before_y(this, *(this + 178) - 1);
        if ( block_starting_at_or_before_y )
        {
          if ( (*(this + 157) & 0x10) != 0 )
          {
            LOBYTE(v1) = rf_text_list_set_scroll_y_with_optional_snap(this, block_starting_at_or_before_y[4], 0);
          }
          else
          {
            v15 = rf_text_block_line_index_from_y(block_starting_at_or_before_y, *(this + 178) - 1);
            v12 = rf_text_block_line_top_y(block_starting_at_or_before_y, v15);
            LOBYTE(v1) = rf_text_list_set_scroll_y_with_optional_snap(this, v12, 0);
          }
        }
        else
        {
          LOBYTE(v1) = rf_text_list_set_scroll_y_with_optional_snap(this, *(_DWORD *)(*(this + 183) + 16), 0);
        }
      }
    }
  }
  return v1;
}

