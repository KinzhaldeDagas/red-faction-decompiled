// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046E920 rf_ui_modal_clear_active
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): Writes only BYTE6F8C84=0. Does not reset focus, edit text, widget state or user callbacks, and does not invoke a user callback. No defined result.
void rf_ui_modal_clear_active()
{
  unk_6F8C84 = 0;
}

