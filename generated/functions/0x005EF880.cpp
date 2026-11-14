// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EF880 rf_ui_button_destroy
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Resets state-image records at+916(normal),+1012(disabled),+948(highlighted),+980(pressed),then full gadget destructor0x5AB7B0. Does NOT reset drag image+1044,so any owned drag animation is omitted here. Does not itself delete button allocation;return gadget destructor result.
int __thiscall rf_ui_button_destroy(_DWORD *this)
{
  rf_ui_state_image_reset(this + 229);
  rf_ui_state_image_reset(this + 253);
  rf_ui_state_image_reset(this + 237);
  rf_ui_state_image_reset(this + 245);
  return rf_ui_gadget_destroy(this);
}

