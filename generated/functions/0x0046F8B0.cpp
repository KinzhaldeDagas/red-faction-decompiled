// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046F8B0 rf_ui_modal_cancel
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): Calls46E920 to clear active BYTE6F8C84 only; does not invoke action/user callbacks or clear editable text/focus. Used by Escape while edit control BYTE9 is nonzero.
void rf_ui_modal_cancel()
{
  rf_ui_modal_clear_active();
}

