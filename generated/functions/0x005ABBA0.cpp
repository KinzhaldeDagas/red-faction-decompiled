// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABBA0 rf_ui_gadget_release_keyboard_focus
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Only when global focus0x1CF75D8 equals nonnull this,clears it and emits own event4,-99999. Otherwise returns current global focus pointer. Return path-dependent pointer/callback result;not success boolean. No owner navigation/hover change.
_DWORD *__thiscall rf_ui_gadget_release_keyboard_focus(_DWORD *this)
{
  _DWORD *result; // eax

  result = dword_1CF75D8;
  if ( dword_1CF75D8 == this )
  {
    if ( this )
    {
      dword_1CF75D8 = nullptr;
      return (_DWORD *)(*(int (__thiscall **)(_DWORD *, int, int))(*this + 4))(this, 4, -99999);
    }
  }
  return result;
}

