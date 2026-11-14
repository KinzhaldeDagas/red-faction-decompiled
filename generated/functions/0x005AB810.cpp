// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AB810 rf_ui_gadget_destruct_base_chain
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thiscall: installs ui_gadget vtable then calls ui_base destructor0x5F1010. No owner-registration unlink here; distinct from full gadget destruction0x5AB7B0. No explicit meaningful return.
int __thiscall rf_ui_gadget_destruct_base_chain(_DWORD *this)
{
  *this = &ui_gadget::`vftable';
  return rf_ui_base_destruct(this);
}

