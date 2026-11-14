// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00505360 rf_trigger_commit_activation
// UNREALRED VERIFIED [mission-startup-20261020] Direct startup commit with entity -1 can pass a named key because a missing player resolution does not reject the transaction. It dispatches links before count increment even for empty lists or a zero finite limit. Flag8 suppresses deferred deletion after exhaustion. Button cooldown uses stored integer milliseconds; clutter reset arming in0x5054C0 truncates seconds*1000.
// UNREALRED VERIFIED [trigger-inside-time-20261021] Commit count/cooldown/same-frame lifecycle runs after runtime_activate even with an empty link list; no target-count requirement. Retail L11S2 uid10410 has InsideTime30s and no links. UnrealRed now permits this empty-link spatial commit; unsupported nonempty target families retain explicit implementation limits.
// UNREALRED VERIFIED [trigger-airlock-20261022] Delayed airlock caller504350 invokes this directly after pressure change. Its third argument is mover suppression; admission504B30/5059A0 is not repeated here. Trigger count/cooldown and same-frame activation state still belong to commit. UnrealRed retains its bounded mission graph prevalidation, which can reject effects beyond its supported runtime scope.
// UNREALRED VERIFIED [trigger-lifecycle-20261026] Writes same-frame activation bit0x40 after dispatch;504350 clears it on each trigger lifecycle visit, not globally at the start of the loop. UnrealRed clears its per-trigger activation-frame marker at this visit, preserving a new delayed activation later in the same visit.
char rf_trigger_commit_activation(int a1, int a2, char a3, ...)
{
  _DWORD *v4; // [esp+0h] [ebp-4h]

  if ( unk_90B508 == 1 )
    return 0;
  if ( *(_DWORD *)(a1 + 684) != -1 )
  {
    v4 = sub_4DD720(a2);
    if ( v4 )
    {
      if ( !*((_BYTE *)v4 + *(_DWORD *)(a1 + 684) + 80) )
        return 0;
    }
  }
  rf_trigger_runtime_activate(a1, a2, a3);
  ++*(_DWORD *)(a1 + 672);
  if ( (rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority)
    && *(_DWORD *)(a1 + 672) >= *(_DWORD *)(a1 + 676)
    && *(_DWORD *)(a1 + 676) != -1
    && (*(_DWORD *)(a1 + 688) & 8) == 0 )
  {
    rf_object_mark_for_deferred_delete(a1);
  }
  if ( *(int *)(a1 + 668) > 0 )
    rf_replicator_arm_milliseconds((int *)(a1 + 664), *(_DWORD *)(a1 + 668));
  *(float *)(a1 + 680) = *(float *)&dword_6FC428;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 && (*(_DWORD *)(a1 + 688) & 8) == 0 )
    rf_multiplayer_broadcast_trigger_activate_packet15(*(_DWORD *)(a1 + 32), a2);
  *(_DWORD *)(a1 + 688) |= 0x40u;
  return 1;
}

