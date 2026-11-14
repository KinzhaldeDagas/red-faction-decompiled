// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593D00 rf_thread_sleep_milliseconds
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl(unsigned32 milliseconds). Pushes caller argument unchanged into imported KERNEL32 Sleep stdcall atIAT630100,then plainRET. No event/message pumping,delay normalization,conversion from seconds,loop or semantic success value. Negative signed caller values are passed as their unsigned bit pattern. Original PE import descriptor and caller56D098 verify millisecond API; IDA IAT FF placeholders are loader metadata,not executable patches.
void __cdecl rf_thread_sleep_milliseconds(DWORD dwMilliseconds)
{
  Sleep(dwMilliseconds);
}

