// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B1110 rf_ui_window_is_enabled_with_modal_blocking
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall returns bool. Walks subsequent global windows via next1252 until sentinel1CF7678. If any scanned window virtual slot16 returnsAL0 AND flags584 has20h(modal),returnsfalse immediately; hidden/inactive windows whose slot16 nonzero do not block. If none blocks,returns base enabled predicate(BYTE28==0) on receiver. No local receiver hidden check,child-state check,NULL/cycle guard or stack args; extra decompiler indirect-call argument is not pushed by raw code.
bool __thiscall rf_ui_window_is_enabled_with_modal_blocking(unsigned __int8 *this)
{
  unsigned __int8 *v2; // [esp+0h] [ebp-8h]
  _DWORD *i; // [esp+4h] [ebp-4h]

  v2 = this;
  for ( i = *((_DWORD **)this + 313); i != dword_1CF7678; i = (_DWORD *)i[313] )
  {
    if ( !(*(unsigned __int8 (__thiscall **)(_DWORD *, unsigned __int8 *))(*i + 16))(i, v2) && (i[146] & 0x20) != 0 )
      return 0;
  }
  return rf_ui_base_is_enabled(v2);
}

