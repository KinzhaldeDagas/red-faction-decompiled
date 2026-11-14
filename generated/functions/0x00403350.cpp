// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00403350 rf_ai_consume_route_refresh_request
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Always invokes401300(block) first. If flags+1328 mask0x08000000 clear returns incidental delegate result. Otherwise
// clears mask BEFORE calling402D70(block,LOWBYTE1). Any nonzero AL from that helper invokes40ECE0 with native stack(route=block+744,extra0), then caller cleans8bytes; existing route
// helper contract consumes route pointer. No request restoration after failure, no own target/owner validation, mode change or repeated route attempt. Return AL/EAX is
// delegate-dependent, not uniform status.
char __cdecl rf_ai_consume_route_refresh_request(int *a1)
{
  char result; // al

  result = rf_ai_consume_deferred_multiplayer_context((int)a1);
  if ( (a1[332] & 0x8000000) != 0 )
  {
    a1[332] &= ~0x8000000u;
    result = rf_ai_build_alternative_route_from_global_points(a1, 1);
    if ( result )
      return rf_ai_route_update((int)(a1 + 186));
  }
  return result;
}

