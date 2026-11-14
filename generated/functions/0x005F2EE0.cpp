// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F2EE0 rf_ui_container_process_input
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): If blocked or hidden returns incoming code. Otherwise calls gadget children-input traversal0x5AB750 but DISCARDS its returned code and returns ORIGINAL input. Child side effects occur;consumption by child is not propagated from this wrapper. Does not process own hotkeys.
int __thiscall rf_ui_container_process_input(_DWORD *this, int a2)
{
  if ( rf_ui_gadget_is_interaction_blocked(this) || (*(unsigned __int8 (__thiscall **)(_DWORD *))(*this + 16))(this) )
    return a2;
  rf_ui_gadget_process_children_input(this, a2);
  return a2;
}

