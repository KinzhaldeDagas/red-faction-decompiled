// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004464A0 rf_ui_request_panel_stack_pop
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments, void. Store push6E6DDE=0,pop6E6DDF=1,pending6E6DE0=0. This ARMS a stack-pop request consumed by4461C0/4462F0, not
// a full pending-transition clear. Does not test depth, decrement stack, clear close-issued latch/per-panel flags, or call close/init/frame. Actual empty-stack underflow is not
// prevented here. Corrected false previous clear-state label/comment;446690 performs the all-zero pending reset.
void rf_ui_request_panel_stack_pop()
{
  unk_6E6DDE = 0;
  unk_6E6DDF = 1;
  dword_6E6DE0 = 0;
}

