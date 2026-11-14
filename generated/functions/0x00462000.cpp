// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00462000 rf_join_pending_ipv4_clear
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// No-argument helper. Stores DWORD6F52DC=0, with no mode/authority check or endpoint/transport cleanup. Does not clear adjacent fields or show modal. Used by pre-session join
// rejection.
void rf_join_pending_ipv4_clear()
{
  unk_6F52DC = 0;
}

