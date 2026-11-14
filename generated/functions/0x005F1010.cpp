// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1010 rf_ui_base_destruct
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Installs ui_base vtable; calls0x5F0F30 auxiliary-record cleanup then unknown_libname_64. Does not operator delete this or unlink owner gadget registration. Incidental return; preserves existing auxiliary cleanup semantics.
void __thiscall rf_ui_base_destruct(_DWORD *this)
{
  *this = &ui_base::`vftable';
  rf_ui_base_destroy_auxiliary_records((int)this);
  rf_saved_receiver_noop_5F1DF0();
}

