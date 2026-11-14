// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00462010 rf_join_pending_ipv4_is_set
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// No arguments, returns canonical BOOL in AL from whether DWORD6F52DC!=0. No runtime/authority check or mutation; raw pending target is an IPv4 DWORD rather than a complete endpoint.
bool rf_join_pending_ipv4_is_set()
{
  return unk_6F52DC != 0;
}

