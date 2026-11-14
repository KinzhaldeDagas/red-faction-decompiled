// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B10B0 rf_ui_window_is_interaction_blocked
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall window. Traverses later windows through pointer+1252 until global sentinel0x1CF7678. If a later window virtual predicate+16 is false AND its flags DWORD+584 mask0x20 set,returns1 (modal-style blocking). Otherwise returns own base disabled BYTE+28. Does not mutate visibility,focus or window order;no cycle/null checks.
char __thiscall rf_ui_window_is_interaction_blocked(_DWORD *this)
{
  _BYTE *v2; // [esp+0h] [ebp-8h]
  _DWORD *i; // [esp+4h] [ebp-4h]

  v2 = this;
  for ( i = (_DWORD *)*(this + 313); i != dword_1CF7678; i = (_DWORD *)i[313] )
  {
    if ( !(*(unsigned __int8 (__thiscall **)(_DWORD *, _BYTE *))(*i + 16))(i, v2) && (i[146] & 0x20) != 0 )
      return 1;
  }
  return rf_ui_base_get_disabled_byte(v2);
}

