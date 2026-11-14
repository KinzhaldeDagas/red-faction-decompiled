// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABC00 rf_ui_gadget_is_owner_hover_target
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Returns bool(owner pointer+604 field+1224==this). Window input sets field to current gadget hit result. Does not perform new hit test,check focus or traverse parents;no owner-null guard.
bool __thiscall rf_ui_gadget_is_owner_hover_target(_DWORD *this)
{
  return *(_DWORD *)(*(this + 151) + 1224) == (_DWORD)this;
}

