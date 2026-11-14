// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A7E60 rf_text_list_scroll_page_up
// UNREALRED VERIFIED [list-selection-20261029]: Clears BYTE+688 even when empty. Nonempty subtracts innerHeight from scrollY;normal mode clamps0,bottom mode lower bound is first.height-innerHeight. Flag0x10 aligns whole block top or bottom after gap lookup. Otherwise aligns using fontHeight times line index;these formulas OMIT entry lineGap even though index helper includes gap. May advance to next block top if rounding passes final line. Writes scrollY directly,not generic setter/bar sync. Lookup results dereferenced without null checks. Return is branch-dependent pointer/coordinate,this or entry.
int *__thiscall rf_text_list_scroll_page_up(int this)
{
  int *result; // eax
  int v2; // eax
  int v3; // esi
  int v4; // esi
  int v5; // eax
  int v6; // eax
  int v7; // esi
  int v9; // [esp+8h] [ebp-Ch]
  int *v10; // [esp+8h] [ebp-Ch]
  int *v11; // [esp+8h] [ebp-Ch]
  _DWORD *block_at_content_position; // [esp+8h] [ebp-Ch]
  int height_select_current; // [esp+Ch] [ebp-8h]
  int v14; // [esp+Ch] [ebp-8h]
  int v15; // [esp+10h] [ebp-4h]

  result = (int *)this;
  *(_BYTE *)(this + 688) = 0;
  if ( *(_DWORD *)(this + 732) != this + 724 )
  {
    *(_DWORD *)(this + 712) -= rf_text_list_inner_height((_DWORD *)this);
    if ( (*(_DWORD *)(this + 628) & 0x80) != 0 )
    {
      v9 = *(_DWORD *)(this + 732);
      if ( v9 && *(_DWORD *)(this + 712) < *(_DWORD *)(v9 + 24) - rf_text_list_inner_height((_DWORD *)this) )
        *(_DWORD *)(this + 712) = *(_DWORD *)(v9 + 24) - rf_text_list_inner_height((_DWORD *)this);
    }
    else if ( *(int *)(this + 712) < 0 )
    {
      *(_DWORD *)(this + 712) = 0;
    }
    if ( (*(_DWORD *)(this + 628) & 0x10) != 0 )
    {
      if ( (*(_DWORD *)(this + 628) & 0x80) != 0 )
      {
        v6 = rf_text_list_inner_height((_DWORD *)this);
        block_at_content_position = rf_text_list_find_block_at_content_position(
                                      (_DWORD *)this,
                                      0,
                                      *(_DWORD *)(this + 712) + v6 - 1,
                                      1);
        v7 = block_at_content_position[6] + block_at_content_position[4];
        *(_DWORD *)(this + 712) = v7 - rf_text_list_inner_height((_DWORD *)this);
      }
      else
      {
        *(_DWORD *)(this + 712) = rf_text_list_find_block_at_content_position(
                                    (_DWORD *)this,
                                    0,
                                    *(_DWORD *)(this + 712),
                                    1)[4];
      }
      return (int *)this;
    }
    else if ( (*(_DWORD *)(this + 628) & 0x80) != 0 )
    {
      v2 = rf_text_list_inner_height((_DWORD *)this);
      v10 = rf_text_list_find_block_at_content_position((_DWORD *)this, 0, *(_DWORD *)(this + 712) + v2 - 1, 1);
      height_select_current = rf_font_get_height_select_current(v10[10]);
      if ( *(_DWORD *)(this + 712) + rf_text_list_inner_height((_DWORD *)this) - 1 > v10[4] )
      {
        v5 = rf_text_list_inner_height((_DWORD *)this);
        v3 = height_select_current * (rf_text_block_line_index_if_y_inside(v10, *(_DWORD *)(this + 712) + v5 - 1) + 1)
           + v10[4];
      }
      else
      {
        v3 = height_select_current + v10[4];
      }
      v4 = v3 - rf_text_list_inner_height((_DWORD *)this);
      *(_DWORD *)(this + 712) = v4;
      return (int *)this;
    }
    else
    {
      v11 = rf_text_list_find_block_at_content_position((_DWORD *)this, 0, *(_DWORD *)(this + 712), 1);
      v14 = rf_font_get_height_select_current(v11[10]);
      if ( *(_DWORD *)(this + 712) > v11[4] )
      {
        v15 = rf_text_block_line_index_if_y_inside(v11, *(_DWORD *)(this + 712));
        if ( *(_DWORD *)(this + 712) == v11[4] + v14 * v15 )
        {
          *(_DWORD *)(this + 712) = v11[4] + v14 * v15;
          return (int *)this;
        }
        else if ( v15 == v11[11] - 1 )
        {
          result = *(int **)(v11[2] + 16);
          *(_DWORD *)(this + 712) = result;
        }
        else
        {
          *(_DWORD *)(this + 712) = v11[4] + v14 * (v15 + 1);
          return (int *)this;
        }
      }
      else
      {
        *(_DWORD *)(this + 712) = v11[4];
        return v11;
      }
    }
  }
  return result;
}

