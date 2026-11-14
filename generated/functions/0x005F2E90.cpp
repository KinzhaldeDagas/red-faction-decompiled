// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F2E90 rf_ui_checkbox_is_navigation_eligible
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): True exactly gadget enabled hierarchy and virtual hidden+16 false. No checked/state/label tests. Vtable eligibility predicate;no side effects.
bool __thiscall rf_ui_checkbox_is_navigation_eligible(unsigned __int8 *this)
{
  return rf_ui_gadget_is_enabled_hierarchy(this)
      && !(*(unsigned __int8 (__thiscall **)(unsigned __int8 *))(*(_DWORD *)this + 16))(this);
}

