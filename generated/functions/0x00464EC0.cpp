// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00464EC0 rf_browser_main_x_is_open
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg,boolAL. Truncate float mainX6F5194 via ftol2_sse;returnAL1 iff integer equals openXDWORD661E58. No exact-float/zero-velocity/input/active test or mutation;upper EAX not
// promised normalized.
bool rf_browser_main_x_is_open()
{
  return (int)unk_6F5194 == dword_661E58;
}

