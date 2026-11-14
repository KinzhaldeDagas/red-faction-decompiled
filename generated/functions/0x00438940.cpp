// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00438940 rf_entity_set_custom_weapon_masks_and_begin_actions
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(entity,index), void. NULL or index outside SIGNED0..31 returns. TWO independent branch groups, not
// generic bit enable. First requires split BYTE==0 AND multiplayer BYTE==0, plus index==global911CBC OR911C6C. Sets SECOND mask5164 bit FIRST, then FIRST mask5160 bit.438AC0 any
// nonzero calls4EBF20 begin-custom(player,index), ignored result, then arms player4152 at1350 wrapped milliseconds. Second group RE-READS multiplayer and requires only BYTE0 (split
// can be any value) plus input==global911CC4: set input bit in first5160;438AC0 any nonzero then grant403AB0(entity AI+672,global911C98,raw quantity-1), ignore result; RE-READ
// global911C98 to set its bit in first5160, then store primary676=that global and begin-custom(player,global911C98). No second5164 mapped-bit write or explicit extra timer in this
// group. Grant can mutate inventory/loaded/reserve/selection via its own rules before outer primary assignment overrides it; local-only begin helper does not guard earlier
// mask/grant/primary stores. Remapped globals are NOT index-validated: shifts use index&31 while grant/primary/delegate consume raw values. No bit-clear prerequisite,
// ownership/result/model validation, own authority check, restoration or rollback; repeated calls can reissue actions and deadline arms.
void __cdecl rf_entity_set_custom_weapon_masks_and_begin_actions(_DWORD *a1, unsigned int a2)
{
  if ( a1 && a2 < 0x20 )
  {
    if ( !rf_splitscreen_runtime_active && !rf_multiplayer_runtime_mode && (a2 == dword_911CBC || a2 == unk_911C6C) )
    {
      a1[1291] |= 1 << a2;
      a1[1290] |= 1 << a2;
      if ( sub_438AC0((int)a1) )
      {
        rf_player_begin_custom_fpgun_action((_DWORD *)a1[1292], a2);
        rf_replicator_arm_milliseconds((int *)(a1[1292] + 4152), 1350);
      }
    }
    if ( !rf_multiplayer_runtime_mode && a2 == dword_911CC4 )
    {
      a1[1290] |= 1 << a2;
      if ( sub_438AC0((int)a1) )
      {
        rf_entity_inventory_grant_weapon(a1 + 168, unk_911C98, -1);
        a1[1290] |= 1 << unk_911C98;
        a1[169] = unk_911C98;
        rf_player_begin_custom_fpgun_action((_DWORD *)a1[1292], unk_911C98);
      }
    }
  }
}

