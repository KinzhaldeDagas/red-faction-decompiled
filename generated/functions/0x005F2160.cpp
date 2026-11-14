// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F2160 rf_ui_checkbox_destroy
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Direct thiscall forwarding wrapper to full gadget destroy0x5AB7B0. Does not release any of four bitmap handles or delete allocation itself;return forwarded/incidental.
int __thiscall rf_ui_checkbox_destroy(_DWORD *this)
{
  return rf_ui_gadget_destroy(this);
}

