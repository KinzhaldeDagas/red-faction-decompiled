// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABB10 rf_ui_gadget_get_first_child
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Thiscall returns pointer DWORD+620,head of child/sibling tree. No ownership transfer,cycle check or input/draw processing.
int __thiscall rf_ui_gadget_get_first_child(_DWORD *this)
{
  return *(this + 155);
}

