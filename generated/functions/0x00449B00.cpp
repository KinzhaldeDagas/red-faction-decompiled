// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449B00 rf_ui_button_set_focus
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Thiscall required record POINTER inECX, no stack arguments. Store BYTE[this+8]=EXACT1, return original this POINTER inEAX. No
// NULL guard, previous-focus lookup/clear, sibling traversal, callback, byte toggle or other field mutation. Existing focus-byte comment retained; this body does not enforce
// exclusive focus.
_BYTE *__thiscall rf_ui_button_set_focus(_BYTE *this)
{
  *(this + 8) = 1;
  return this;
}

