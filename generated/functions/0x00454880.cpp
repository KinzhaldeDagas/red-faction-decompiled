// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00454880 rf_frontend_panel_pop_adapter_454880
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No consumed arguments, plain RET. Calls4464A0 once, then returns without own state stores or guards. Existing verified helper requests deferred panel-stack
// pop; wrapper does not itself remove/destroy a panel or check empty-stack state. EAX is delegate residue, not independently normalized.
void rf_frontend_panel_pop_adapter_454880()
{
  rf_ui_request_panel_stack_pop();
}

