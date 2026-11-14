// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A8160 rf_text_list_scroll_page_down
// UNREALRED VERIFIED [list-selection-20261029]: Requires nonempty and current scrollY<=contentHeight-innerHeight;then clears BYTE+688. Flag0x10 whole-block mode:oversized current block can advance directly to next block;otherwise adds viewport height and aligns target block top or bottom(flag0x80). Other mode adds viewport height,clamps against last bottom or contentHeight-1,then aligns using fontHeight*lineIndex,OMITTING entry lineGap in coordinate formula. Writes scrollY directly without scrollbar-position update or generic Y setter. No null lookup guards; oversized-next path can reach sentinel. Return incidental coordinate/pointer/helper result.
_DWORD *__thiscall rf_text_list_scroll_page_down(int this)
{
  _DWORD *result; // eax
  int v2; // esi
  int v3; // esi
  int v4; // eax
  int v5; // esi
  int v6; // eax
  int v7; // eax
  int v8; // esi
  int v9; // esi
  int v10; // esi
  int v11; // eax
  int v12; // esi
  int v14; // [esp+8h] [ebp-Ch]
  int *v15; // [esp+8h] [ebp-Ch]
  int *v16; // [esp+8h] [ebp-Ch]
  _DWORD *block_at_content_position; // [esp+8h] [ebp-Ch]
  int v18; // [esp+8h] [ebp-Ch]
  _DWORD *v19; // [esp+8h] [ebp-Ch]
  _DWORD *v20; // [esp+8h] [ebp-Ch]
  int height_select_current; // [esp+Ch] [ebp-8h]
  int v22; // [esp+Ch] [ebp-8h]

  result = (_DWORD *)(this + 724);
  if ( *(_DWORD *)(this + 732) != this + 724 )
  {
    result = (_DWORD *)rf_text_list_inner_height((_DWORD *)this);
    if ( *(_DWORD *)(this + 712) <= *(_DWORD *)(this + 684) - (int)result )
    {
      *(_BYTE *)(this + 688) = 0;
      if ( (*(_DWORD *)(this + 628) & 0x10) != 0 )
      {
        if ( (*(_DWORD *)(this + 628) & 0x80) != 0 )
        {
          v7 = rf_text_list_inner_height((_DWORD *)this);
          block_at_content_position = rf_text_list_find_block_at_content_position(
                                        (_DWORD *)this,
                                        0,
                                        *(_DWORD *)(this + 712) + v7 - 1,
                                        1);
          if ( block_at_content_position[6] <= rf_text_list_inner_height((_DWORD *)this)
            || block_at_content_position == *(_DWORD **)(this + 736) )
          {
            *(_DWORD *)(this + 712) += rf_text_list_inner_height((_DWORD *)this);
            v18 = *(_DWORD *)(this + 736);
            v9 = *(_DWORD *)(v18 + 24) + *(_DWORD *)(v18 + 16);
            if ( *(_DWORD *)(this + 712) > v9 - rf_text_list_inner_height((_DWORD *)this) )
            {
              v10 = *(_DWORD *)(v18 + 24) + *(_DWORD *)(v18 + 16);
              *(_DWORD *)(this + 712) = v10 - rf_text_list_inner_height((_DWORD *)this);
            }
            v11 = rf_text_list_inner_height((_DWORD *)this);
            v19 = rf_text_list_find_block_at_content_position((_DWORD *)this, 0, *(_DWORD *)(this + 712) + v11 - 1, 1);
            v12 = v19[6] + v19[4];
            result = (_DWORD *)rf_text_list_inner_height((_DWORD *)this);
            *(_DWORD *)(this + 712) = v12 - (_DWORD)result;
          }
          else
          {
            v8 = *(_DWORD *)(block_at_content_position[2] + 24) + *(_DWORD *)(block_at_content_position[2] + 16);
            result = (_DWORD *)rf_text_list_inner_height((_DWORD *)this);
            *(_DWORD *)(this + 712) = v8 - (_DWORD)result;
          }
        }
        else
        {
          v20 = rf_text_list_find_block_at_content_position((_DWORD *)this, 0, *(_DWORD *)(this + 712), 1);
          if ( v20[6] <= rf_text_list_inner_height((_DWORD *)this) || v20 == *(_DWORD **)(this + 736) )
          {
            *(_DWORD *)(this + 712) += rf_text_list_inner_height((_DWORD *)this);
            if ( *(_DWORD *)(this + 712) >= *(_DWORD *)(this + 684) )
              *(_DWORD *)(this + 712) = *(_DWORD *)(this + 684) - 1;
            result = rf_text_list_find_block_at_content_position((_DWORD *)this, 0, *(_DWORD *)(this + 712), 1);
            *(_DWORD *)(this + 712) = result[4];
          }
          else
          {
            result = (_DWORD *)v20[2];
            *(_DWORD *)(this + 712) = result[4];
          }
        }
      }
      else
      {
        *(_DWORD *)(this + 712) += rf_text_list_inner_height((_DWORD *)this);
        if ( (*(_DWORD *)(this + 628) & 0x80) != 0 )
        {
          v14 = *(_DWORD *)(this + 736);
          v2 = *(_DWORD *)(v14 + 24) + *(_DWORD *)(v14 + 16);
          if ( *(_DWORD *)(this + 712) > v2 - rf_text_list_inner_height((_DWORD *)this) )
          {
            v3 = *(_DWORD *)(v14 + 24) + *(_DWORD *)(v14 + 16);
            *(_DWORD *)(this + 712) = v3 - rf_text_list_inner_height((_DWORD *)this);
          }
          v4 = rf_text_list_inner_height((_DWORD *)this);
          v15 = rf_text_list_find_block_at_content_position((_DWORD *)this, 0, *(_DWORD *)(this + 712) + v4 - 1, 1);
          height_select_current = rf_font_get_height_select_current(v15[10]);
          if ( *(_DWORD *)(this + 712) > v15[4] )
          {
            v6 = rf_text_list_inner_height((_DWORD *)this);
            v5 = height_select_current
               * (rf_text_block_line_index_if_y_inside(v15, *(_DWORD *)(this + 712) + v6 - 1) + 1)
               + v15[4];
          }
          else
          {
            v5 = height_select_current + v15[4];
          }
          result = (_DWORD *)rf_text_list_inner_height((_DWORD *)this);
          *(_DWORD *)(this + 712) = v5 - (_DWORD)result;
        }
        else
        {
          if ( *(_DWORD *)(this + 712) >= *(_DWORD *)(this + 684) )
            *(_DWORD *)(this + 712) = *(_DWORD *)(this + 684) - 1;
          v16 = rf_text_list_find_block_at_content_position((_DWORD *)this, 0, *(_DWORD *)(this + 712), 1);
          v22 = rf_font_get_height_select_current(v16[10]);
          if ( *(_DWORD *)(this + 712) > v16[4] )
            result = (_DWORD *)(v16[4] + v22 * rf_text_block_line_index_if_y_inside(v16, *(_DWORD *)(this + 712)));
          else
            result = (_DWORD *)v16[4];
          *(_DWORD *)(this + 712) = result;
        }
      }
    }
  }
  return result;
}

