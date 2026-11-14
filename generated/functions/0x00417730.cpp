// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417730 rf_monitor_reset_global_dword_6807E0
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Only writes zero to global DWORD 0x6807E0. No list traversal, bitmap release or record/timer reset. Global meaning is not established by this routine.
void rf_monitor_reset_global_dword_6807E0()
{
  unk_6807E0 = 0;
}

