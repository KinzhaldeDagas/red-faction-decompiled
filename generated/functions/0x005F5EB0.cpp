// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F5EB0 rf_ui_inputbox_is_navigation_eligible
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): True iff gadget enabled hierarchy and virtual hidden+16 false. No focus,text-length or cursor tests;vtable eligibility slot+32.
bool __thiscall rf_ui_inputbox_is_navigation_eligible(unsigned __int8 *this)
{
  return rf_ui_gadget_is_enabled_hierarchy(this)
      && !(*(unsigned __int8 (__thiscall **)(unsigned __int8 *))(*(_DWORD *)this + 16))(this);
}

