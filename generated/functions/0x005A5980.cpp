// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A5980 rf_text_block_line_bottom_y
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall block,signed line index. Returns top + index*pitch + fontHeight,where top=block DWORD+16,pitch=gap DWORD+36 + fontHeight(font DWORD+40). Excludes trailing gap from line bottom. No index bound or overflow check; queries current font height once.
int __thiscall rf_text_block_line_bottom_y(int *this, int a2)
{
  int height_select_current; // [esp+4h] [ebp-4h]

  height_select_current = rf_font_get_height_select_current(*(this + 10));
  return height_select_current + a2 * (*(this + 9) + height_select_current) + *(this + 4);
}

