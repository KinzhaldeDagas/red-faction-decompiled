// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004352A0 rf_entity_request_forced_body_action_by_handle
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(full entity handle,signed action index), void. Resolve ENTITY FIRST even for negative action. Missing
// entity OR signed action<0 exits. Otherwise request five slots(entity,action,FLOAT1,LOWBYTE1,LOWBYTE1), ignore result. No own upper bound, existing-action/health/authority/ownership
// check, timer or status result; underlying action dispatcher enforces its own record range. Does not interpret input as entity pointer.
void __cdecl rf_entity_request_forced_body_action_by_handle(int a1, signed int a2)
{
  int v2; // [esp+Ch] [ebp-4h]

  v2 = rf_entity_resolve_handle(a1);
  if ( v2 )
  {
    if ( a2 >= 0 )
      rf_entity_request_body_action(v2, a2, 1.0, 1, 1);
  }
}

