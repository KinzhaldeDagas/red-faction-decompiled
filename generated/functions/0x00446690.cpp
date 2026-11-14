// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446690 rf_ui_clear_pending_panel_transition
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments, void. In order clear pending DWORD6E6DE0,push BYTE6E6DDE,pop BYTE6E6DDF to0. Leaves global depth, stack/per-panel
// contents and close-issued latch6E6E28 unchanged. No pop request (unlike4464A0), close/init/frame callback, validation, input reset or allocation.
void rf_ui_clear_pending_panel_transition()
{
  dword_6E6DE0 = 0;
  unk_6E6DDE = 0;
  unk_6E6DDF = 0;
}

