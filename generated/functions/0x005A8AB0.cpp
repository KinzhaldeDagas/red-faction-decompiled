// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A8AB0 rf_text_list_snap_scroll_to_line_bottom
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall list,requested top Y. Empty returns input. Bottom edge=Y+innerHeight;finds first block.bottom>edge. If first block: flag0x10 uses block bottom,else first line bottom,then subtracts viewport height. Other blocks: flag0x10 returns previous block bottom-height. Otherwise scans candidate line bottoms,uses last line bottom<=edge;if none,previous block bottom. Returns chosen bottom-innerHeight. No mutation,final nonnegative clamp or explicit end-sentinel guard before accessing candidate font/line fields. Used for flags0x80 bottom-oriented snapping.
int __thiscall rf_text_list_snap_scroll_to_line_bottom(_DWORD *this, int a2)
{
  int v3; // esi
  int v4; // esi
  _DWORD *i; // [esp+8h] [ebp-14h]
  int v7; // [esp+Ch] [ebp-10h]
  int height_select_current; // [esp+10h] [ebp-Ch]
  int j; // [esp+14h] [ebp-8h]
  int v10; // [esp+18h] [ebp-4h]
  int v11; // [esp+24h] [ebp+8h]

  v7 = a2;
  if ( (_DWORD *)*(this + 183) == this + 181 )
    return a2;
  v10 = a2 + rf_text_list_inner_height(this);
  for ( i = (_DWORD *)*(this + 183); i != this + 181 && i[6] + i[4] <= v10; i = (_DWORD *)i[2] )
    ;
  if ( i == (_DWORD *)*(this + 183) )
  {
    if ( (*(this + 157) & 0x10) != 0 )
      v3 = i[6] + i[4];
    else
      v3 = rf_font_get_height_select_current(i[10]) + i[4];
    return v3 - rf_text_list_inner_height(this);
  }
  else
  {
    if ( (*(this + 157) & 0x10) != 0 )
      goto LABEL_13;
    height_select_current = rf_font_get_height_select_current(i[10]);
    for ( j = 0; j < i[11]; ++j )
    {
      v11 = i[4] + j * (i[9] + height_select_current);
      if ( height_select_current + v11 > v10 )
        break;
      v7 = height_select_current + v11;
    }
    if ( !j )
    {
LABEL_13:
      v4 = *(_DWORD *)(i[3] + 24) + *(_DWORD *)(i[3] + 16);
      return v4 - rf_text_list_inner_height(this);
    }
    else
    {
      return v7 - rf_text_list_inner_height(this);
    }
  }
}

