// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A90D0 rf_text_list_get_content_height
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall returns DWORD+684 (computed content height),not viewport height. No reflow or clamping; empty-list layout may leave negative gap value.
int __thiscall rf_text_list_get_content_height(_DWORD *this)
{
  return *(this + 171);
}

