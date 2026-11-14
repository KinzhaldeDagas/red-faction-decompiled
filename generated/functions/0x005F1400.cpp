// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1400 rf_ui_base_get_disabled_byte
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall returns raw BYTE+28. Nonzero is used as interaction-blocked state. No normalization,visibility test,parent/window traversal or state mutation.
char __thiscall rf_ui_base_get_disabled_byte(_BYTE *this)
{
  return *(this + 28);
}

