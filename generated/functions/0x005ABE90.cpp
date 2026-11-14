// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABE90 rf_ui_gadget_set_region_id
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Thiscall gadget,region. Values<1 become0,then stores DWORD+600,returns this. No upper bound,mask allocation/validation or hit-test call.
_DWORD *__thiscall rf_ui_gadget_set_region_id(_DWORD *this, int a2)
{
  if ( a2 < 1 )
    a2 = 0;
  *(this + 150) = a2;
  return this;
}

