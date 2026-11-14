// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1420 rf_ui_base_is_enabled
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Thiscall returns bool(BYTE+28==0). No hidden flag,parent/modal blocking or focus traversal. Positive counterpart to raw disabled-byte getter.
BOOL __thiscall rf_ui_base_is_enabled(unsigned __int8 *this)
{
  return *(this + 28) == 0;
}

