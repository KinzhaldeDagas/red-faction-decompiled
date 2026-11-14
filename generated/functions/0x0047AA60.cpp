// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047AA60 rf_level_browser_text_list_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, liquid transition lifecycle, native x87 unordered comparisons, stable pointer erase, static runtime ownership and level-browser flow): 
// Thiscall destructor of global text-list object6FC978, verified static exit wrapper62EFC0. Destroys embedded text entry at724, then invokes UI gadget base-chain destruction. Unwind
// also destroys base chain. No explicit receiver free, pack-name enumeration or liquid-transition cleanup in this body.
int __thiscall rf_level_browser_text_list_destroy(char *this)
{
  rf_text_entry_destroy((_DWORD *)this + 181);
  return rf_ui_gadget_destruct_base_chain(this);
}

