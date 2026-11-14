// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004564B0 rf_frontend_panel_pop_adapter_4564b0
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No consumed arguments, plain RET. Calls4464A0 once and returns; no own validation, state stores or immediate panel destruction. Helper owns deferred
// panel-stack-pop request and commit policy. Identical native control flow to454880; EAX not independently defined.
void rf_frontend_panel_pop_adapter_4564b0()
{
  rf_ui_request_panel_stack_pop();
}

