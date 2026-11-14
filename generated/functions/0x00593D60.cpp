// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593D60 rf_window_enter_message_critical_section
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tokenizer ownership/quote rules, native hook contracts, observer registration, startup signaling and thread-exit/calling-convention paths): Cdecl no-argument adapter. Calls EnterCriticalSection on shared global1BC2110. Prior _cleanup name did not describe body: no teardown, heap free, message pumping or LeaveCriticalSection here. Same lock surrounds worker queue drain/dispatch594130.
void rf_window_enter_message_critical_section()
{
  EnterCriticalSection(&unk_1BC2110);
}

