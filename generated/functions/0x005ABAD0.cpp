// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABAD0 rf_ui_gadget_get_owner_window
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Thiscall returns borrowed owner-window pointer DWORD+604. Inferred int return does not imply ID. No validation,reference counting or parent traversal.
int __thiscall rf_ui_gadget_get_owner_window(_DWORD *this)
{
  return *(this + 151);
}

