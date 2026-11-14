// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00415A50 rf_clutter_cleanup_resources_and_unlink
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter runtime teardown/render admission, DWORD-category glass callback, cached model binding and signed-counter clock-hand geometry): Cdecl clutter,returns0. Stops voices672 and720 when EACH!=integer-1,sets stopped field-1;destroys secondarymodel696 whennonNULL thenzeroes it. If global local-player nonNULL AND player180==ownUID44,exits monitor view. SignedSHORT724>=0 clears that unchecked bit in HEADER666FF0;does not setSHORT724=-1. Only exact multiplayerRuntime1 AND serverAuthority1 emits removal through4AB880. Releases array704 backing WITHOUT per-pointee destruction. Unlinks intrusive object652next/656prev by writing neighbors,then zeroesownlinks;decrements global666B6C without underflow/idempotence guard. Does NOT free containing allocation,destroy primary128,remove clock UID entries or clear all other state
// here. No NULL/list/class validation;repeated invocation can fault on zeroedlinks.
int __cdecl rf_clutter_cleanup_resources_and_unlink(int a1)
{
  if ( *(_DWORD *)(a1 + 672) != -1 )
  {
    rf_gamesound_stop_voice_handle(*(_DWORD *)(a1 + 672));
    *(_DWORD *)(a1 + 672) = -1;
  }
  if ( *(_DWORD *)(a1 + 720) != -1 )
  {
    rf_gamesound_stop_voice_handle(*(_DWORD *)(a1 + 720));
    *(_DWORD *)(a1 + 720) = -1;
  }
  if ( *(_DWORD *)(a1 + 696) )
  {
    rf_model_handle_destroy_cdecl_adapter(*(_DWORD **)(a1 + 696));
    *(_DWORD *)(a1 + 696) = 0;
  }
  if ( rf_local_fpgun_player && *(_DWORD *)(rf_local_fpgun_player + 180) == *(_DWORD *)(a1 + 44) )
    rf_player_exit_monitor_view(rf_local_fpgun_player);
  if ( *(__int16 *)(a1 + 724) >= 0 )
    rf_bitset_set_bit_unchecked(dword_666FF0, *(__int16 *)(a1 + 724), 0);
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
    rf_network_broadcast_clutter_removal_type30(a1);
  rf_pointer_array_release_storage((void **)(a1 + 704));
  *(_DWORD *)(*(_DWORD *)(a1 + 656) + 652) = *(_DWORD *)(a1 + 652);
  *(_DWORD *)(*(_DWORD *)(a1 + 652) + 656) = *(_DWORD *)(a1 + 656);
  *(_DWORD *)(a1 + 652) = 0;
  *(_DWORD *)(a1 + 656) = 0;
  --unk_666B6C;
  return 0;
}

