// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ACE00 rf_powerup_nodes_expire_elapsed
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Noarg. Traverse circular root7B2548 saving next and root-wrap termination BEFORE callbacks. For each node deadline at+8, if replicator_has_elapsed returns any nonzero
// AL, call remove_player_kind(node.player0,node.kind4). That helper re-finds first matching node and clears associated entity kind0/1 flags even if lookup misses; under normal
// unique-key insertion it removes current node. Disarmed/nonelapsed nodes untouched. No runtime/authority/player-validity guard, no direct time subtraction, no bitmap work.
void rf_powerup_nodes_expire_elapsed()
{
  int *v0; // [esp+0h] [ebp-Ch]
  int *i; // [esp+8h] [ebp-4h]

  for ( i = (int *)unk_7B2548; i; i = v0 )
  {
    if ( i[3] == unk_7B2548 )
      v0 = nullptr;
    else
      v0 = (int *)i[3];
    if ( rf_replicator_has_elapsed(i + 2) )
      rf_powerup_remove_player_kind_and_clear_entity(*i, i[1]);
  }
}

