// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABB30 rf_ui_gadget_get_next_sibling
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Thiscall returns pointer DWORD+624. Does not advance an iterator state or validate pointer;borrowed sibling link.
int __thiscall rf_ui_gadget_get_next_sibling(_DWORD *this)
{
  return *(this + 156);
}

