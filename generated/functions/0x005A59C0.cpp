// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A59C0 rf_text_block_line_index_from_y_with_gap_bias
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall block,Y. Signed quotient=(gap+Y-top)/pitch,where top=DWORD+16,gap=DWORD+36,pitch=gap+fontHeight(font DWORD+40); clamps quotient<0 to0,quotient>=lineCount+44 to lineCount-1. No zero-pitch or empty-count guard; empty block may return-1 or0 depending quotient. Bias assigns gap area toward following line; not generic floating ceil.
int __thiscall rf_text_block_line_index_from_y_with_gap_bias(int *this, int a2)
{
  int v2; // esi
  int v5; // [esp+8h] [ebp-4h]

  v2 = *(this + 9) + a2 - *(this + 4);
  v5 = v2 / (*(this + 9) + rf_font_get_height_select_current(*(this + 10)));
  if ( v5 < 0 )
    return 0;
  if ( v5 < *(this + 11) )
    return v5;
  return *(this + 11) - 1;
}

