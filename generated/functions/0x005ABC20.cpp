// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABC20 rf_ui_gadget_get_type
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Thiscall returns DWORD+596,gadget type supplied at initialization (list-box creation uses8). No base-kind read,RTTI or normalization.
int __thiscall rf_ui_gadget_get_type(_DWORD *this)
{
  return *(this + 149);
}

