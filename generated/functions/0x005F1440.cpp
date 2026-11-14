// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1440 rf_ui_base_get_hidden_byte
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Thiscall returns raw BYTE+29. Separate from disabled BYTE+28;no normalization,parent/window traversal or state mutation.
char __thiscall rf_ui_base_get_hidden_byte(_BYTE *this)
{
  return *(this + 29);
}

