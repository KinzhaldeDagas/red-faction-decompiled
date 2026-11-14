// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004460E0 rf_ui_panel_stack_reset_depth_and_flags
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments, void. In order write global signed stack depth6615F8=-1, push BYTE6E6DDE=0, pop BYTE6E6DDF=0. Leaves pending
// DWORD6E6DE0, close-issued latch6E6E28, stack contents, per-panel flags and raw mode byte untouched. No panel close/init/frame callback, allocation or input reset.
void rf_ui_panel_stack_reset_depth_and_flags()
{
  dword_6615F8 = -1;
  unk_6E6DDE = 0;
  unk_6E6DDF = 0;
}

