// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040A020 rf_ai_secondary6_to7_and_reset_route
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Secondary DWORD+692==EXACT6 calls secondary-state writer(block,7), then resets route at block+744. Other states
// untouched. No primary mode/target mutation or result boolean; EAX input block on bypass, route-reset result otherwise.
int __cdecl rf_ai_secondary6_to7_and_reset_route(int a1)
{
  int result; // eax

  result = a1;
  if ( *(_DWORD *)(a1 + 692) == 6 )
  {
    rf_ai_secondary_state_write(a1, 7);
    return rf_ai_route_reset(a1 + 744);
  }
  return result;
}

