// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00422270 rf_entity_weapon_firing_byte_is_set
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Cdecl(full entity HANDLE,signed weaponIndex), explicit AL0/1; upper EAX incidental. Native signed comparisons require0<=index<64 BEFORE
// handle resolution. ENTITY resolver433EE0 must return nonnull. Then returnsAL1 iff BYTE[entity+1132+index] is ANY nonzero, elseAL0. Does not require byte exactly1, ownership, ammo,
// weapon-definition validity, active body action, health or runtime mode. No writes. Saved unsigned index type yields same admitted bit patterns; retain literal signed checks in
// contract.
bool __cdecl rf_entity_weapon_firing_byte_is_set(int a1, unsigned int a2)
{
  int v3; // [esp+0h] [ebp-4h]

  if ( a2 >= 0x40 )
    return 0;
  v3 = rf_entity_resolve_handle(a1);
  return v3 && *(_BYTE *)(a2 + v3 + 1132) != 0;
}

