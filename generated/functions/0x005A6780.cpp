// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A6780 rf_text_block_line_index_if_y_inside
// UNREALRED VERIFIED [list-selection-20261029]: Thiscall block,Y. Outside half-open interval[topY,topY+height) returns-1;inside returns signed(Y-topY)/(lineGap+fontHeight). Top=DWORD+16,height+24,gap+36,font+40. No zero-pitch,count or overflow guard. Unlike neighboring clamped index helpers,it rejects outside Y.
int __thiscall rf_text_block_line_index_if_y_inside(int *this, int a2)
{
  int v2; // esi

  if ( a2 < *(this + 4) || a2 >= *(this + 6) + *(this + 4) )
    return -1;
  v2 = a2 - *(this + 4);
  return v2 / (*(this + 9) + rf_font_get_height_select_current(*(this + 10)));
}

