// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046E0E0 rf_persona_history_request_close
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): No-argument body, used as Close callback with ignored supplied x/y. Calls rf_ui_clear_panel_request only; does not free panel resources or reset history/capture globals.
// Incidental delegate return.
void rf_persona_history_request_close()
{
  rf_ui_request_panel_stack_pop();
}

