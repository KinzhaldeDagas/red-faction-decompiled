// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00436800 rf_entity_try_set_holster_and_stop_primary
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(entity), void. NULL, already-set raw2064 mask0x800, or primary676==EXACT-1 exits. There is NO other
// weapon-index sign/range/ownership test before writes.438AC0 ANY nonzero then tests is-armed40D0F0 at(entity Player5168+184); ANY nonzero armed byte blocks, regardless whether
// deadline elapsed.438AC0 zero skips that test; nonzero with disarmed deadline admits. First OR raw holsterbit0x800; REPEAT438AC0 and, if any nonzero, request4E71E0(Player5168)
// holster action. Then422A40(RE-READ entity full handle44,RE-READ primary676) stops weapon firing; callback/stop result not inspected. Finally loop i0,1 calls55F020 on RAW DWORD
// entity1216+4*i, disarming both by writing-1. Other negative/out-of-range primaries can therefore commit holster/callback/resets even though stop delegate rejects them. No own
// turret exclusion, inventory/ammo/dead/authority gate, elapsed-deadline check, status result or rollback; bit commit precedes callback and stop side effects.
void __cdecl rf_entity_try_set_holster_and_stop_primary(_DWORD *a1)
{
  int i; // [esp+0h] [ebp-4h]

  if ( a1
    && (a1[516] & 0x800) == 0
    && a1[169] != -1
    && (!sub_438AC0((int)a1) || !rf_replicator_is_armed((_DWORD *)(a1[1292] + 184))) )
  {
    a1[516] |= 0x800u;
    if ( sub_438AC0((int)a1) )
      rf_fpgun_request_holster_action(a1[1292]);
    rf_entity_stop_weapon_firing(a1[11], a1[169]);
    for ( i = 0; i < 2; ++i )
      rf_replicator_reset(&a1[i + 304]);
  }
}

