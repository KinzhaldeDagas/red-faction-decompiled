// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00438820 rf_entity_clear_custom_weapon_masks_and_leave_actions
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(entity,index), void. NULL or index outside SIGNED0..31 returns without writes. ALWAYS clear input bit in
// first mask5160(+1428), regardless prior bit. First independent special branch: index==global911CBC OR911C6C clears same bit in second mask5164, then438AC0 any nonzero AL (nonnull
// entity,direct player flag,nonnull player5168) calls4EBF70 leave-custom(player,index), ignores result, and arms player deadline4152 for500 wrapped-clock milliseconds. Local-only
// leave delegate can do nothing while outer mask/deadline mutations still occur; no own multiplayer/split restriction. Second independent branch: index==global911C98 AND438AC0 any
// nonzero writes primary676=global911CC4, then clears mapped global911CC4 bit from first mask5160, then leave-custom(player,mappedIndex). Mapped index is NOT revalidated: hardware
// shift uses low5 bits but stored primary/delegate index retains full raw DWORD. No grant of mapped weapon, mapped second-mask clear, own action-table refresh, result test or
// additional deadline arm in this second branch. Branches are not mutually exclusive if globals alias, and predicates/globals/player pointer re-read after delegates. No
// bit-already-set gate, restoration or rollback; earlier writes survive later failures. EAX incidental.
void __cdecl rf_entity_clear_custom_weapon_masks_and_leave_actions(_DWORD *a1, unsigned int a2)
{
  if ( a1 && a2 < 0x20 )
  {
    a1[1290] &= ~(1 << a2);
    if ( a2 == dword_911CBC || a2 == unk_911C6C )
    {
      a1[1291] &= ~(1 << a2);
      if ( sub_438AC0((int)a1) )
      {
        rf_player_leave_custom_fpgun_action((_DWORD *)a1[1292], a2);
        rf_replicator_arm_milliseconds((int *)(a1[1292] + 4152), 500);
      }
    }
    if ( a2 == unk_911C98 && sub_438AC0((int)a1) )
    {
      a1[169] = dword_911CC4;
      a1[1290] &= ~(1 << dword_911CC4);
      rf_player_leave_custom_fpgun_action((_DWORD *)a1[1292], dword_911CC4);
    }
  }
}

