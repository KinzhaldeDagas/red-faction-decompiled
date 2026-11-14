// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABB50 rf_ui_gadget_take_keyboard_focus
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: If any current global focus0x1CF75D8,emits its virtual event4,-99999 EVEN when it already equals this. Then stores this as global focus and emits own event3,-99999,returns result. No enabled/hidden/owner/membership guard;notifications synchronous. Does not update owner navigation target+1228.
int __thiscall rf_ui_gadget_take_keyboard_focus(_DWORD *this)
{
  if ( dword_1CF75D8 )
    (*(void (__thiscall **)(_DWORD *, int, int))(*dword_1CF75D8 + 4))(dword_1CF75D8, 4, -99999);
  dword_1CF75D8 = this;
  return (*(int (__thiscall **)(_DWORD *, int, int))(*this + 4))(this, 3, -99999);
}

