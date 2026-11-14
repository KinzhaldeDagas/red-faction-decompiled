// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1210 rf_ui_base_set_disabled_raw
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall object,disabled BYTE. Stores value RAW at+28. If object currently global focus0x1CF75D8 AND new value EXACTLY1,clears focus and emits virtual+4(event4,arg-99999). Values2..255 remain nonzero blocked but do NOT trigger that exact1 focus-release condition. Return this or callback result. Does NOT hide/show object or clear child focus recursively.
_BYTE *__thiscall rf_ui_base_set_disabled_raw(_BYTE *this, char a2)
{
  _BYTE *result; // eax

  result = this;
  *(this + 28) = a2;
  if ( dword_1CF75D8 == (_DWORD *)this )
  {
    result = this;
    if ( *(this + 28) == 1 )
    {
      dword_1CF75D8 = nullptr;
      return (_BYTE *)(*(int (__thiscall **)(_BYTE *, int, int))(*(_DWORD *)this + 4))(this, 4, -99999);
    }
  }
  return result;
}

