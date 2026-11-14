// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABF80 rf_ui_gadget_set_hidden_raw_and_clear_owner_targets
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Calls base raw hidden setter0x5F12C0 with supplied BYTE. Then calls virtual hidden predicate+16; if true calls0x5AC000 to clear this gadget from owner hover/navigation targets. Does this check even when raw value was unchanged. Does not recursively clear children or explicitly emit hover/target-loss events; return incidental.
int __thiscall rf_ui_gadget_set_hidden_raw_and_clear_owner_targets(_DWORD *this, unsigned __int8 a2)
{
  int result; // eax

  rf_ui_base_set_hidden_raw(this, a2);
  result = (*(int (__thiscall **)(_DWORD *))(*this + 16))(this);
  if ( (_BYTE)result )
    return rf_ui_gadget_clear_matching_owner_targets(this);
  return result;
}

