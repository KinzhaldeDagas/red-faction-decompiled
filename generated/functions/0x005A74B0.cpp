// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A74B0 rf_text_list_remove_entry
// UNREALRED VERIFIED [list-selection-20261029]: Thiscall list,entry pointer. Dereferences and unlinks previous+12/next+8 BEFORE any null check,zeros links. Current list flag0x400 chooses base deleting destructor0x5A9670,otherwise buffered0x5A96C0;does not inspect entry RTTI. Clears selected+692 if same pointer,recomputes extents and both scrollbar ranges. Chooses entry at scrollY with gap mode or last entry,then writes raw scrollY aligned to top or bottom(flag0x80);none writes0. No final scrollbar-position synchronization or general membership/sentinel validation. Return branch-dependent entry/viewport/helper value,not deletion status.
_DWORD *__thiscall rf_text_list_remove_entry(int *this, _DWORD *a2)
{
  _DWORD *result; // eax
  int v3; // esi

  *(_DWORD *)(a2[3] + 8) = a2[2];
  *(_DWORD *)(a2[2] + 12) = a2[3];
  a2[2] = 0;
  a2[3] = 0;
  if ( (*(this + 157) & 0x400) != 0 )
  {
    if ( a2 )
      rf_text_entry_scalar_deleting_destructor(a2, 1);
  }
  else if ( a2 )
  {
    rf_text_entry_buffered_scalar_deleting_destructor(a2, 1);
  }
  if ( (_DWORD *)*(this + 173) == a2 )
    *(this + 173) = 0;
  rf_text_list_recompute_block_positions_and_extent(this);
  rf_text_list_sync_vertical_scrollbar_extent(this);
  rf_text_list_sync_horizontal_scrollbar_extent(this);
  if ( *(this + 178) <= *(this + 171) )
    result = rf_text_list_find_block_at_content_position(this, 0, *(this + 178), 1);
  else
    result = (_DWORD *)*(this + 184);
  if ( result )
  {
    if ( (*(this + 157) & 0x80) != 0 )
    {
      v3 = result[6] + result[4];
      result = (_DWORD *)rf_text_list_inner_height(this);
      *(this + 178) = v3 - (_DWORD)result;
    }
    else
    {
      *(this + 178) = result[4];
    }
  }
  else
  {
    *(this + 178) = 0;
  }
  return result;
}

