// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00401300 rf_ai_consume_deferred_multiplayer_context
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One cdecl context pointer/value. Only when runtime BYTE or splitscreen BYTE is nonzero AND global pending pointer6663D4==input:
// calls401260(pending,global DWORD6663C0,ADDRESS6663E8), then clears pending pointer6663D4=0 regardless of delegate result. No own nonnull admission (pending0/input0 can match).
// Single-player path leaves pending untouched; no queue traversal or retry. AL/EAX incidental delegate/runtime value. Called by403350 before its route-request flag handling.
char __cdecl rf_ai_consume_deferred_multiplayer_context(int a1)
{
  char result; // al

  result = rf_multiplayer_runtime_mode;
  if ( (rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active) && dword_6663D4 == a1 )
  {
    result = rf_ai_try_deferred_nearby_route((int *)dword_6663D4, dword_6663C0, flt_6663E8);
    dword_6663D4 = 0;
  }
  return result;
}

