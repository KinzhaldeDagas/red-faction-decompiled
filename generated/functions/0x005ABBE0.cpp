// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABBE0 rf_ui_gadget_is_owner_navigation_target
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Returns bool(owner pointer+604 field+1228==this). Window input handler0x5B0CA0 updates this target on motion/release and emits events8/7 on changes. Distinct from global keyboard-focus pointer0x1CF75D8 and owner hover+1224. No owner-null guard.
bool __thiscall rf_ui_gadget_is_owner_navigation_target(_DWORD *this)
{
  return *(_DWORD *)(*(this + 151) + 1228) == (_DWORD)this;
}

