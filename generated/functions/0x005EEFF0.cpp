// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EEFF0 rf_ui_button_emit_click
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Argument0 emits virtual+4 event12,arg-99999 then stores state632=6;nonzero emits13 then stores7. State write occurs AFTER callback,overwriting any callback state change. Right branch returns this;left returns incidental callback result. No eligibility or owner checks.
_DWORD *__thiscall rf_ui_button_emit_click(_DWORD *this, int a2)
{
  _DWORD *result; // eax

  if ( a2 )
  {
    (*(void (__thiscall **)(_DWORD *, int, int))(*this + 4))(this, 13, -99999);
    *(this + 158) = 7;
    return this;
  }
  else
  {
    result = (_DWORD *)(*(int (__thiscall **)(_DWORD *, int, int))(*this + 4))(this, 12, -99999);
    *(this + 158) = 6;
  }
  return result;
}

