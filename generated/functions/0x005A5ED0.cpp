// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A5ED0 rf_text_list_reflow_dirty_blocks
// UNREALRED VERIFIED [text-layout-20261029]: Scans blocks; for each dirty BYTE+4,layouts through0x5A5A90 with callback Y=cumulative block heights-scrollY. Cumulative sum omits inter-block gap,unlike final positioning helper. If any dirty node,recomputes block positions/extents then synchronizes BOTH scrollbar extents. Neither this body nor layout helper clears dirty BYTE. No dirty nodes returns0;otherwise final scrollbar helper result,not dirty count.
_DWORD *__thiscall rf_text_list_reflow_dirty_blocks(_DWORD *this)
{
  _DWORD *result; // eax
  int i; // [esp+4h] [ebp-Ch]
  unsigned __int8 v4; // [esp+Bh] [ebp-5h]
  int v5; // [esp+Ch] [ebp-4h]

  v4 = 0;
  v5 = 0;
  for ( i = *(this + 183); (_DWORD *)i != this + 181; i = *(_DWORD *)(i + 8) )
  {
    if ( *(_BYTE *)(i + 4) )
    {
      rf_text_list_layout_block((int)this, (int *)i, v5 - *(this + 178));
      v4 = 1;
    }
    v5 += *(_DWORD *)(i + 24);
  }
  result = (_DWORD *)v4;
  if ( v4 )
  {
    rf_text_list_recompute_block_positions_and_extent(this);
    rf_text_list_sync_vertical_scrollbar_extent(this);
    return rf_text_list_sync_horizontal_scrollbar_extent(this);
  }
  return result;
}

