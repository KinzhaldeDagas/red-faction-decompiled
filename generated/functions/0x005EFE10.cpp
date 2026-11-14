// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EFE10 rf_ui_button_is_primary_activation_state
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Returns false if virtual hidden+16 or gadget blocked. Otherwise true exactly state DWORD+632==6 or8 (primary click/repeat activation or primary double click). Right-click states7/9 return false.
bool __thiscall rf_ui_button_is_primary_activation_state(_DWORD *this)
{
  if ( (*(unsigned __int8 (__thiscall **)(_DWORD *))(*this + 16))(this) || rf_ui_gadget_is_interaction_blocked(this) )
    return 0;
  return *(this + 158) == 6 || *(this + 158) == 8;
}

