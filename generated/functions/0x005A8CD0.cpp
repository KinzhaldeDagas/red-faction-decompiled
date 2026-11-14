// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A8CD0 rf_text_list_set_scroll_y_fraction_aligned
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Recovered code0x5A8CD0..0x5A906A. Thiscall list,float fraction,unused DWORD;ret8. Ordered fraction clamps0..1,clears BYTE+688. Computes endpoints: empty list both0;bottom mode flags0x80 minimum=(first block height if0x10,else first fontHeight)-innerHeight,maximum=last.top+last.height-innerHeight;normal minimum0,maximum=last.top if0x10 else last.top+fontHeight*(lineCount-1). Interpolates float,rounds half away from0 via add/sub0.5 then truncation,stores scrollY+712. Bottom mode ALWAYS aligns to block/line bottom at viewport bottom-1;normal mode aligns to top only when fraction<1. Line coordinates use fontHeight without lineGap. No scrollbar synchronization or final generic Y clamp. Empty-list endpoint case does NOT return early: subsequent alignment can dereferenceNULL (normal fraction1 skips it,bottom mode never skips). Zero content width
// can also invalidate X0 gap lookup. Second stack DWORD ignored;NaN/lookup/pointer validity not checked.
void __thiscall rf_text_list_set_scroll_y_fraction_aligned(void *list, float fraction, int unused)
{
  int v3; // esi
  int v4; // eax
  int v5; // esi
  int v6; // eax
  int v7; // esi
  int v9; // [esp+Ch] [ebp-1Ch]
  _DWORD *v10; // [esp+Ch] [ebp-1Ch]
  int *block_at_content_position; // [esp+Ch] [ebp-1Ch]
  _DWORD *v12; // [esp+Ch] [ebp-1Ch]
  int height_select_current; // [esp+10h] [ebp-18h]
  int v14; // [esp+10h] [ebp-18h]
  float v15; // [esp+14h] [ebp-14h]
  int v16; // [esp+18h] [ebp-10h]
  int v17; // [esp+1Ch] [ebp-Ch]
  int v18; // [esp+20h] [ebp-8h]
  int i; // [esp+24h] [ebp-4h]

  if ( fraction >= 0.0 )
  {
    if ( fraction > 1.0 )
      fraction = 1.0;
  }
  else
  {
    fraction = 0.0;
  }
  *((_BYTE *)list + 688) = 0;
  if ( *((void **)list + 183) == (char *)list + 724 )
  {
    v18 = 0;
    v17 = 0;
  }
  else if ( (*((_DWORD *)list + 157) & 0x80) != 0 )
  {
    v9 = *((_DWORD *)list + 183);
    if ( (*((_DWORD *)list + 157) & 0x10) != 0 )
    {
      v18 = *(_DWORD *)(v9 + 24) - rf_text_list_inner_height(list);
    }
    else
    {
      height_select_current = rf_font_get_height_select_current(*(_DWORD *)(v9 + 40));
      v18 = height_select_current - rf_text_list_inner_height(list);
    }
    v3 = *(_DWORD *)(*((_DWORD *)list + 184) + 24) + *(_DWORD *)(*((_DWORD *)list + 184) + 16);
    v17 = v3 - rf_text_list_inner_height(list);
  }
  else
  {
    v18 = 0;
    v10 = *((_DWORD **)list + 184);
    if ( (*((_DWORD *)list + 157) & 0x10) != 0 )
      v17 = v10[4];
    else
      v17 = v10[4] + rf_font_get_height_select_current(v10[10]) * (v10[11] - 1);
  }
  v15 = (double)(v17 - v18) * fraction + (double)v18;
  if ( v15 < 0.0 )
    *((_DWORD *)list + 178) = (int)(v15 - 0.5);
  else
    *((_DWORD *)list + 178) = (int)(v15 + 0.5);
  if ( (*((_DWORD *)list + 157) & 0x80) != 0 )
  {
    v4 = rf_text_list_inner_height(list);
    block_at_content_position = rf_text_list_find_block_at_content_position(
                                  list,
                                  0,
                                  *((_DWORD *)list + 178) + v4 - 1,
                                  1);
    if ( (*((_DWORD *)list + 157) & 0x10) != 0 )
    {
      v7 = block_at_content_position[6] + block_at_content_position[4];
      *((_DWORD *)list + 178) = v7 - rf_text_list_inner_height(list);
    }
    else
    {
      if ( *((_DWORD *)list + 178) > block_at_content_position[4] - rf_text_list_inner_height(list) )
      {
        v6 = rf_text_list_inner_height(list);
        v16 = rf_text_block_line_index_if_y_inside(block_at_content_position, *((_DWORD *)list + 178) + v6 - 1);
        v5 = rf_font_get_height_select_current(block_at_content_position[10]) * (v16 + 1) + block_at_content_position[4];
      }
      else
      {
        v5 = *(_DWORD *)(block_at_content_position[3] + 24) + *(_DWORD *)(block_at_content_position[3] + 16);
      }
      *((_DWORD *)list + 178) = v5 - rf_text_list_inner_height(list);
    }
  }
  else if ( fraction < 1.0 )
  {
    v12 = rf_text_list_find_block_at_content_position(list, 0, *((_DWORD *)list + 178), 1);
    if ( (*((_DWORD *)list + 157) & 0x10) != 0 )
    {
      *((_DWORD *)list + 178) = v12[4];
    }
    else
    {
      v14 = rf_font_get_height_select_current(v12[10]);
      if ( *((_DWORD *)list + 178) > v12[4] )
      {
        for ( i = 0;
              i < v12[11]
           && (*((_DWORD *)list + 178) < v12[4] + v14 * i || *((_DWORD *)list + 178) >= v12[4] + v14 * (i + 1));
              ++i )
        {
          ;
        }
        *((_DWORD *)list + 178) = v12[4] + v14 * i;
      }
      else
      {
        *((_DWORD *)list + 178) = v12[4];
      }
    }
  }
}

