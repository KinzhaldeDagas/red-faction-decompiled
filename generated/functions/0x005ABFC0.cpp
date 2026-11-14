// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABFC0 rf_ui_gadget_set_visible_and_clear_owner_targets
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Calls base visible setter0x5F1360, then virtual hidden predicate+16; if true clears matching owner hover/navigation targets via0x5AC000. Base setter has raw-byte equality gate; callers should supply Boolean0/1. Even unchanged input runs postcheck; no child recursion; incidental return.
int __thiscall rf_ui_gadget_set_visible_and_clear_owner_targets(_DWORD *this, unsigned __int8 a2)
{
  int result; // eax

  rf_ui_base_set_visible_raw_equality_gated(this, a2);
  result = (*(int (__thiscall **)(_DWORD *))(*this + 16))(this);
  if ( (_BYTE)result )
    return rf_ui_gadget_clear_matching_owner_targets(this);
  return result;
}

