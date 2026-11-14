// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00431740 rf_entity_reload_in_progress
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(required entity), canonical BOOL in AL only. If entity player pointer5168 nonnull, call4EBC30(player,semantic action index8); ANY nonzero AL
// immediately returnsAL1 without reading entity reload flag. Missing player or action AL0 then test entity DWORD2064 mask100: nonzero returnsAL1, clear returnsAL0. Upper EAX
// incidental. No own entity-null guard (dereferences before predicate), weapon/primary/authority/death tests, ammo mutation, action start/cancel, timer reset or secondary-action
// query. This OR predicate combines FPGun semantic reload activity with entity reload bit; it does not require both and does not update either source.
bool __cdecl rf_entity_reload_in_progress(int a1)
{
  return *(_DWORD *)(a1 + 5168) && rf_fpgun_action_is_active(*(_DWORD *)(a1 + 5168), 8u)
      || (*(_DWORD *)(a1 + 2064) & 0x100) != 0;
}

