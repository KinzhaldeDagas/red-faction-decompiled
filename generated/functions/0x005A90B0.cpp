// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A90B0 rf_text_list_get_content_width
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall returns DWORD+680 (computed content width),not inner/outer viewport width. No layout or scroll side effect.
int __thiscall rf_text_list_get_content_width(_DWORD *this)
{
  return *(this + 170);
}

