// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F6260 rf_ui_staticbox_destroy
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Resets two32-byte state images at908(normal),940(disabled),then full gadget destructor0x5AB7B0. Owned animations released by reset;bitmap assets/rings not released here. Does not delete this allocation;return forwarded.
int __thiscall rf_ui_staticbox_destroy(_DWORD *this)
{
  rf_ui_state_image_reset(this + 227);
  rf_ui_state_image_reset(this + 235);
  return rf_ui_gadget_destroy(this);
}

