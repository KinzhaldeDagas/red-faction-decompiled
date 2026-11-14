// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593D70 rf_window_leave_message_critical_section
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tokenizer ownership/quote rules, native hook contracts, observer registration, startup signaling and thread-exit/calling-convention paths): Cdecl no-argument adapter. Calls LeaveCriticalSection on shared global1BC2110. Prior _cleanup_0 name did not describe body: no deletion of critical-section object, message dispatch or EnterCriticalSection here. Assumes caller owns valid initialized lock.
void rf_window_leave_message_critical_section()
{
  LeaveCriticalSection(&unk_1BC2110);
}

