// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F6290 rf_ui_staticbox_process_input
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Hidden or blocked returns original key code. Otherwise hovered primary press emits virtual+4 event18,arg-99999. Always returns original code;no key binding match,focus acquisition,children traversal or mouse flag consumption here.
int __thiscall rf_ui_staticbox_process_input(_DWORD *this, int a2)
{
  if ( (*(unsigned __int8 (__thiscall **)(_DWORD *))(*this + 16))(this) || rf_ui_gadget_is_interaction_blocked(this) )
    return a2;
  if ( unk_1CF7593 )
  {
    if ( rf_ui_gadget_is_owner_hover_target(this) )
      (*(void (__thiscall **)(_DWORD *, int, int))(*this + 4))(this, 18, -99999);
  }
  return a2;
}

