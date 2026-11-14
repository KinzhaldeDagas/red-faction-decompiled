// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AEFE0 rf_splitscreen_query_zero_stub
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Noarg exact EAX0 return. No global reads or writes, guards, cleanup, allocation or delegated behavior. Wider intended query semantics are not established by
// this stub.
int rf_splitscreen_query_zero_stub()
{
  return 0;
}

