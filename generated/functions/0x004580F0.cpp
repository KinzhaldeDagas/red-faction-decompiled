// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004580F0 rf_frontend_help_close_noop
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Only frame prologue/epilogue and RET. No input reads, state changes, callbacks, cleanup or EAX normalization; preserves incoming EAX. Does not reset help
// selection or issue panel pop.
void rf_frontend_help_close_noop()
{
  ;
}

