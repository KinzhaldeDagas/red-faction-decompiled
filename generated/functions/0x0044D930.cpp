// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044D930 rf_hud_zero_local_player_fields11E0_through11EC
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Iterate signed index0 while index<live global DWORD87C638 (reloaded each condition). For each current
// local-player entry from array87C5B0, store positive FLOAT32 zero at offsets4576(+11E0),4580(+11E4),4584(+11E8),4588(+11EC), in that order. Entry pointer is re-read separately for
// all four stores; no whole-player snapshot or callback. No NULL/count-upper-bound/player-equality/field-meaning admission and no allocation or timer query. Count<=0 performs no
// entry access or stores and leaves incoming EAX unchanged. After one or more iterations EAX is final signed loop index from wrapped increment, not a normalized success or guaranteed
// snapshot of current count. No other player fields reset or return-value initialization on empty loop.
int rf_hud_zero_local_player_fields11E0_through11EC()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_local_player_entry_count; ++i )
  {
    *(float *)(rf_local_player_entries[i] + 4576) = 0.0;
    *(float *)(rf_local_player_entries[i] + 4580) = 0.0;
    *(float *)(rf_local_player_entries[i] + 4584) = 0.0;
    *(float *)(rf_local_player_entries[i] + 4588) = 0.0;
    result = i + 1;
  }
  return result;
}

