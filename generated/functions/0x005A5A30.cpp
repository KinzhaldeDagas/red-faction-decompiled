// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A5A30 rf_text_block_line_index_from_y
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall block,Y. Signed quotient=(Y-top)/pitch,where top=DWORD+16,gap=DWORD+36,pitch=gap+fontHeight(font DWORD+40);integer division truncates toward0. Clamps negative to0,at/above count to count-1. No zero-pitch,count>0 or coordinate overflow guard; empty block can return-1.
int __thiscall rf_text_block_line_index_from_y(int *this, int a2)
{
  int v2; // esi
  int v5; // [esp+8h] [ebp-4h]

  v2 = a2 - *(this + 4);
  v5 = v2 / (*(this + 9) + rf_font_get_height_select_current(*(this + 10)));
  if ( v5 < 0 )
    return 0;
  if ( v5 < *(this + 11) )
    return v5;
  return *(this + 11) - 1;
}

