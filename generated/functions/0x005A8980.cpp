// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A8980 rf_text_list_snap_scroll_to_line_top
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall list,requested Y. Empty returns input. Finds first block.top>=Y;past end returns LAST block top via sentinel.prev. Flag+628 bit0x10 or first-block match returns that block top. Otherwise examines PREVIOUS block lines using font height+gap,returns first line top>=Y;after all its lines returns next block top. Does not mutate list or clamp to viewport bounds. Uses linked prev+12,next+8; no pitch/count validation.
int __thiscall rf_text_list_snap_scroll_to_line_top(_DWORD *this, int a2)
{
  _DWORD *i; // [esp+4h] [ebp-10h]
  _DWORD *v4; // [esp+4h] [ebp-10h]
  int v5; // [esp+8h] [ebp-Ch]
  int height_select_current; // [esp+Ch] [ebp-8h]
  int j; // [esp+10h] [ebp-4h]

  v5 = a2;
  if ( (_DWORD *)*(this + 183) == this + 181 )
    return a2;
  for ( i = (_DWORD *)*(this + 183); i != this + 181 && i[4] < a2; i = (_DWORD *)i[2] )
    ;
  if ( i == this + 181 )
    return *(_DWORD *)(*(this + 184) + 16);
  if ( (*(this + 157) & 0x10) != 0 )
    return i[4];
  if ( i == (_DWORD *)*(this + 183) )
    return i[4];
  v4 = (_DWORD *)i[3];
  height_select_current = rf_font_get_height_select_current(v4[10]);
  for ( j = 0; j < v4[11]; ++j )
  {
    v5 = v4[4] + j * (v4[9] + height_select_current);
    if ( v5 >= a2 )
      break;
  }
  if ( j == v4[11] )
    return *(_DWORD *)(v4[2] + 16);
  else
    return v5;
}

