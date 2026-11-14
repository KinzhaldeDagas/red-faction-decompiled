// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00496130 rf_player_string_record28_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Verified application28-byte inline-record constructor callback,previously false SDK Concurrency::details::SchedulerCore symbol/FUNC_LIB. Native body only constructs empty RFString
// atreceiver12,returns receiver. EH iterator4960D0 uses count128,stride28; matching destructor496150 releases same field; live/snapshot Player owns array. No scheduler or concurrency
// API here. Cleared false library classification and replaced misleading SchedulerCore pointer prototype with rawDWORD receiver/return; existing local types retained. Numeric
// WORDs0/2/4/20/22/24,DWORD8,padding untouched.
_DWORD *__thiscall rf_player_string_record28_construct(_DWORD *this)
{
  rf_string_construct_empty(this + 3);
  return this;
}

