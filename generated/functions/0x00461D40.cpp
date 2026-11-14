// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00461D40 rf_browser_cancel_discovery_and_queries
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg. If pending IPv4 set,clear it. Set cancel/suppress-sendBYTE6F51A1=1,tracker-activeBYTE6F51A2=0,next query-order cursor6F51B0=-1. Does not clear per-row queued/awaiting
// flags,retry bytes,counts,rows,timers or tracker pool. Scheduler later consumes queued flags without sending and still processes outstanding timeouts;this body does not immediately
// erase all query state. EAX incidental.
void rf_browser_cancel_discovery_and_queries()
{
  if ( rf_join_pending_ipv4_is_set() )
    rf_join_pending_ipv4_clear();
  unk_6F51A1 = 1;
  unk_6F51A2 = 0;
  unk_6F51B0 = -1;
}

