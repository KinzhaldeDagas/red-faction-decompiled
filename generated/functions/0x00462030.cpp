// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00462030 rf_join_sender_ipv4_matches_pending
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl(endpoint pointer), returns AL BOOL comparing ONLY endpoint DWORD0 with pending DWORD6F52DC. No pointer/pending-nonzero/port check or mutation; by itself0 equals0 succeeds.
// Client join-accept separately checks pending!=0 first.
bool __cdecl rf_join_sender_ipv4_matches_pending(_DWORD *a1)
{
  return *a1 == unk_6F52DC;
}

