// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1360 rf_ui_base_set_visible_raw_equality_gated
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Unsigned BYTE argument. EXACT gate: modifies only if current hidden BYTE+29 EQUALS argument; stores(arg==0). With normalized current/argument0/1 this implements visible flag; arbitrary raw values do not implement general Boolean assignment. When changed to hidden1 and globally focused,clears focus and emits4; emits9 when hidden,10 when visible,arg-99999. Nonmatching input does nothing; return incidental. Verified cmp/jz at0x5F1372..1374.
_BYTE *__thiscall rf_ui_base_set_visible_raw_equality_gated(_BYTE *this, unsigned __int8 a2)
{
  _BYTE *result; // eax

  result = this;
  if ( (unsigned __int8)*(this + 29) == a2 )
  {
    *(this + 29) = a2 == 0;
    if ( dword_1CF75D8 == (_DWORD *)this && *(this + 29) == 1 )
    {
      dword_1CF75D8 = nullptr;
      (*(void (__thiscall **)(_BYTE *, int, int))(*(_DWORD *)this + 4))(this, 4, -99999);
    }
    if ( *(this + 29) )
      return (_BYTE *)(*(int (__thiscall **)(_BYTE *, int, int))(*(_DWORD *)this + 4))(this, 9, -99999);
    else
      return (_BYTE *)(*(int (__thiscall **)(_BYTE *, int, int))(*(_DWORD *)this + 4))(this, 10, -99999);
  }
  return result;
}

