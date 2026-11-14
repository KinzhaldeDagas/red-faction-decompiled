// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F12C0 rf_ui_base_set_hidden_raw
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Unsigned BYTE argument; changes only when stored hidden BYTE+29 differs,then stores raw input without normalization. If global keyboard focus0x1CF75D8==this and new hidden BYTE exactly1,clears focus and emits virtual+4 event4,arg-99999. Emits event9 for any nonzero new hidden byte,or10 for zero. Raw value2 hides but does not satisfy focus-release condition. Unchanged byte emits nothing. Return incidental this/event result.
_BYTE *__thiscall rf_ui_base_set_hidden_raw(_BYTE *this, unsigned __int8 a2)
{
  _BYTE *result; // eax

  result = this;
  if ( (unsigned __int8)*(this + 29) != a2 )
  {
    *(this + 29) = a2;
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

