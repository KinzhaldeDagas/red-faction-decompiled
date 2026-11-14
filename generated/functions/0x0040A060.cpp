// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040A060 rf_ai_rebuild_route_to_retained_target
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Common target handle+704 missing ->40A2A0(block), no additional explicit target clear here. Valid target: if secondary
// state+692==11 first invokes4083A0(block), then no-write vector constructor and401000(block,&temporaryDestination), ignoring its return. Calls route builder(owner
// handle+44,&destination); zero AL resets embedded route+744, any nonzero leaves installed route. No own destination preinitialization/fallback, numeric mode write, rearm or
// authority test; body return incidental despite stored char declaration.
void __cdecl rf_ai_rebuild_route_to_retained_target(int *a1)
{
  float v1[3]; // [esp+0h] [ebp-10h] BYREF

  if ( rf_object_resolve_handle(a1[176]) )
  {
    if ( a1[173] == 11 )
      rf_ai_select_secondary2_with_timing(a1);
    rf_vector3_default_construct_noop(v1);
    rf_ai_copy_route_target_position((int)a1, v1);
    if ( !rf_ai_route_build(*(_DWORD *)(*a1 + 44), (int)v1) )
      rf_ai_route_reset((int)(a1 + 186));
  }
  else
  {
    sub_40A2A0(a1);
  }
}

