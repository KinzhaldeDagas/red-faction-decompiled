// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A5950 rf_text_block_line_top_y
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall block,signed line index. Returns top + index*pitch,where top=block DWORD+16,pitch=gap DWORD+36 + fontHeight(font DWORD+40). No line-count/index bound or overflow handling. Font-height lookup changes global current-font pointer.
int __thiscall rf_text_block_line_top_y(int *this, int a2)
{
  return *(this + 4) + a2 * (*(this + 9) + rf_font_get_height_select_current(*(this + 10)));
}

